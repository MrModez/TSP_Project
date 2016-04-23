#include "TSP_MainWindow.h"
#include <QtCore>
#include <QFileDialog>
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_SolverCollection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pSolvers = new TSP_SolverCollection(m_pMap);
    m_pCanvas = new TSP_Canvas(ui->centralWidget, m_pMap);

    connect(m_pCanvas, &TSP_Canvas::addCity, m_pMap, &TSP_Map::addCity);
    connect(m_pCanvas, &TSP_Canvas::moveCity, m_pMap, &TSP_Map::moveCity);
    connect(m_pCanvas, &TSP_Canvas::removeCity, m_pMap, &TSP_Map::removeCity);

    ui->verticalLayout->addWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
}

void MainWindow::on_actionStartGA_toggled(bool arg1)
{
    if (arg1)
    {
        if (m_pSolvers->IsWorking(Solver_GA))
            m_pSolvers->Continue(Solver_GA);
        else
        {
            std::vector<float>arg{(float)ui->spinBox->value(), (float)ui->spinBox_2->value()/100.0f,
                        (float)ui->spinBox_3->value()/100.0f, (float)ui->spinBox_4->value()/100.0f, (float)ui->spinBox_5->value()/100.0f};
            m_pSolvers->Solve(Solver_GA, arg);
        }
        ui->StartGABut->setText("II");
    }
    else
    {
        m_pSolvers->Pause(Solver_GA);
        ui->StartGABut->setText(">");
    }
}

void MainWindow::on_actionStopGA_triggered()
{
    m_pSolvers->Continue(Solver_GA);
    m_pSolvers->Stop(Solver_GA);
    ui->StartGABut->setText(">");
}

void MainWindow::on_actionStopBB_triggered()
{
    m_pSolvers->Continue(Solver_BB);
    m_pSolvers->Stop(Solver_BB);
    ui->StartBBBut->setText(">");
}


void MainWindow::on_actionStartBB_toggled(bool arg1)
{
    if (arg1)
    {
        std::vector<float>arg;
        m_pSolvers->Solve(Solver_BB, arg);
        ui->actionStartBB->setText("StopBB");
    }
    else
    {
        m_pSolvers->Stop(Solver_BB);
        ui->actionStartBB->setText("StartBB");
    }

}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open TSP","",
             "Data file (*.dat);;TSP data (*.tsp)");
    QFileInfo fi(fileName);

    if(QFile(fileName).exists())
    {
        m_pMap->Erase();
        if (fi.suffix() == "dat")
        {
            QSettings settings(fileName, QSettings::IniFormat);
            settings.sync();
            foreach(auto child, settings.childGroups())
            {
                settings.beginGroup(child);
                float x = settings.value("x",0).toFloat();
                float y = settings.value("y",0).toFloat();
                settings.endGroup();
                m_pMap->addCity(x, y);
            }
        }
        else if (fi.suffix() == "tsp")
        {
            QFile inputFile(fileName);
            bool flag = false;
            if (inputFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&inputFile);
               while (!in.atEnd())
               {
                  QString line = in.readLine();
                  if (line == "NODE_COORD_SECTION")
                  {
                      flag = true;
                      continue;
                  }
                  if (line == "EOF")
                      break;
                  if (!flag)
                      continue;
                  QStringList lines = line.split(" ");
                  std::vector<float>coords;
                  for (auto &str : lines)
                  {
                      if (str == "")
                          continue;
                      float num = str.toFloat();
                      coords.push_back(num);
                  }
                  //qDebug() << coords[1] << coords[2];
                  m_pMap->addCity(coords[1], coords[2]);
               }
               inputFile.close();
            }
        }
        m_pCanvas->repaint();
    }
    else
        qDebug() << "not exist";
}

void MainWindow::on_actionShowBestResult_toggled(bool arg1)
{
    m_pCanvas->ShowBest(arg1);
}

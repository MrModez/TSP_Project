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
    //connect(m_pMap, &TSP_Map::MatrixUpdated, this, &MainWindow::MatrixUpdated);

    setFileName("");
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
        ui->StartGABut->setText("Пауза");
    }
    else
    {
        m_pSolvers->Pause(Solver_GA);
        ui->StartGABut->setText("Старт");
    }
    setWorking(arg1);
}

void MainWindow::on_actionStopGA_triggered()
{
    m_pSolvers->Continue(Solver_GA);
    m_pSolvers->Stop(Solver_GA);
    ui->StartGABut->setChecked(false);
}


void MainWindow::on_actionStartBB_toggled(bool arg1)
{
    if (arg1)
    {
        if (m_pSolvers->IsWorking(Solver_BB))
            m_pSolvers->Continue(Solver_BB);
        else
        {
            std::vector<float>arg;
            m_pSolvers->Solve(Solver_BB, arg);
        }
        ui->StartBBBut->setText("Пауза");
    }
    else
    {
        m_pSolvers->Pause(Solver_BB);
        ui->StartBBBut->setText("Старт");
    }
    setWorking(arg1);
}

void MainWindow::on_actionStopBB_triggered()
{
    m_pSolvers->Continue(Solver_BB);
    m_pSolvers->Stop(Solver_BB);
    ui->StartBBBut->setChecked(false);
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
            for (auto &child : settings.childGroups())
            {
                settings.beginGroup(child);
                float x = settings.value("x",0).toFloat();
                float y = settings.value("y",0).toFloat();
                settings.endGroup();
                m_pMap->addCity(x, y);
            }
            setFileName(fileName);
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

void MainWindow::setFileName(QString name)
{
    if (!name.isEmpty())
    {
        QFileInfo fi(name);
        this->setWindowTitle("TSP_Project - " + fi.fileName());
    }
    else
    {
        this->setWindowTitle("TSP_Project");
    }
    Filename = name;
}

void MainWindow::setWorking(bool flag)
{
    working = flag;
    menuBar()->setEnabled(!flag);
    m_pCanvas->setEnabled(!flag);
}


void MainWindow::on_actionNew_triggered()
{
    m_pMap->Clear();
    setFileName("");
    setWorking(false);
}

void MainWindow::saveTSP(QString fileName)
{
    if (!fileName.isEmpty())
    {
        QSettings settings(fileName, QSettings::IniFormat);
        settings.clear();
        int count = 0;
        for (auto &city : m_pMap->GetArray())
        {
            settings.beginGroup("Point" + QString::number(count++));
            settings.setValue("x", (int)city.x);
            settings.setValue("y", (int)city.y);
            settings.endGroup();
        }
        settings.sync();
        setFileName(fileName);
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (Filename.isEmpty())
    {
        on_actionSaveAs_triggered();
        return;
    }
    else
        saveTSP(Filename);
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save TSP","",
             "Data (*.dat)");
    saveTSP(fileName);
}

void MainWindow::on_actionClear_triggered()
{
    m_pMap->Clear();
    setWorking(false);
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::MatrixUpdated()
{
    auto matrix = m_pMap->GetMatrix();
    QString str = "<table border=\"1\" cellpadding=\"2\" cellspacing=\"2\">";
    str += "<tr>";
    str += "<th>/</th>";
    for (int i = 0; i < matrix.size(); i++)
    {
        str += "<th>" + QString::number(i) + "</th>";
    }
    str += "</tr>";
    int a = 0;
    for (auto &vec : matrix)
    {
        str += "<tr>";
        str += "<th>" + QString::number(a++) + "</th>";
        for (auto &num : vec)
        {
            float fnum = floor(num * 5 + 0.5) / 5;
            str += "<td>" + QString::number(fnum) + "</td>";
        }
        str += "</tr>";
    }
    str += "</table>";
    ui->textEdit->setHtml(str);
}


void MainWindow::on_UpdateBut_clicked()
{
    MatrixUpdated();
}

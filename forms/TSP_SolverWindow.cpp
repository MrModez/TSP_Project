// ===== Copyright © 2015-2016, MrModez (Zagir Fabarisov), Flatag (Tagir Fabarisov), All rights reserved. =====
//
// Purpose: Widget-window for single solving
// Назначение: Виджет для решения одного случая
//
// ============================================================================================================
#include "TSP_SolverWindow.h"
#include "ui_TSP_SolverWindow.h"
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_SolverCollection.h"

TSP_SolverWindow::TSP_SolverWindow(QWidget *parent) :
    TSP_BaseWindow(parent),
    ui(new Ui::TSP_SolverWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pSolvers = new TSP_SolverCollection(m_pMap, this);
    m_pCanvas = new TSP_Canvas(ui->centralWidget, m_pMap);
    connect(m_pCanvas, &TSP_Canvas::addCity, m_pMap, &TSP_Map::addCity);
    connect(m_pCanvas, &TSP_Canvas::moveCity, m_pMap, &TSP_Map::moveCity);
    connect(m_pCanvas, &TSP_Canvas::removeCity, m_pMap, &TSP_Map::removeCity);
    connect(m_pSolvers, &TSP_SolverCollection::onFinish, this, &TSP_SolverWindow::onFinish);
    //connect(m_pMap, &TSP_Map::MatrixUpdated, this, &TSP_SolverWindow::MatrixUpdated);

    ui->verticalLayout->addWidget(m_pCanvas);
}

TSP_SolverWindow::~TSP_SolverWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pSolvers;
    delete m_pCanvas;
}


void TSP_SolverWindow::onFinish(int ID)
{
    qDebug() << "FINISH LOL " << ID;
    if (ID == Solver_GA)
    {
        ui->StartGABut->setChecked(false);
        on_actionStartGA_toggled(false);
    }
    else if (ID == Solver_BB)
    {
        ui->StartBBBut->setChecked(false);
        on_actionStartBB_toggled(false);
    }
}

void TSP_SolverWindow::on_actionNew_triggered()
{
    m_pMap->Clear();
    setWorking(false);
}

void TSP_SolverWindow::on_actionOpen_triggered()
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
            emit newFileName(fileName);
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

void TSP_SolverWindow::on_actionSave_triggered(QString Filename)
{
    saveTSP(Filename);
}

void TSP_SolverWindow::on_actionSaveAs_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save TSP","",
             "Data (*.dat)");
   saveTSP(fileName);
}

void TSP_SolverWindow::on_actionStartGA_toggled(bool arg1)
{
    if (arg1)
    {
        if (m_pMap->GetArray().size() < 4)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Количество городов должно быть больше трех.");
            msgBox.exec();
            ui->StartGABut->setChecked(false);
            return;
        }
        if (m_pSolvers->IsWorking(Solver_GA))
        {
            m_pSolvers->Continue(Solver_GA);
            ui->StartGABut->setText("Пауза");
        }
        else
        {
            QVector<float>arg{(float)ui->spinBox->value(), (float)ui->spinBox_2->value()/100.0f,
                        (float)ui->spinBox_3->value()/100.0f, (float)ui->spinBox_4->value()/100.0f, (float)ui->spinBox_5->value()/100.0f};
            m_pSolvers->Solve(Solver_GA, arg);
            ui->StartGABut->setText("Пауза");
        }
    }
    else
    {
        if (m_pSolvers->IsWorking(Solver_GA))
        {
            m_pSolvers->Pause(Solver_GA);
            ui->StartGABut->setText("Приостановленно");
        }
        else
        {
            ui->StartGABut->setText("Старт");
        }
    }
    setWorking(m_pSolvers->IsWorking(Solver_GA));
}

void TSP_SolverWindow::on_actionStopGA_triggered()
{
    m_pSolvers->Stop(Solver_GA);
}


void TSP_SolverWindow::on_actionStartBB_toggled(bool arg1)
{
    if (arg1)
    {
        if (m_pMap->GetArray().size() < 4)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Количество городов должно быть больше трех.");
            msgBox.exec();
            ui->StartBBBut->setChecked(false);
            return;
        }
        if (m_pSolvers->IsWorking(Solver_BB))
        {
            m_pSolvers->Continue(Solver_BB);
            ui->StartBBBut->setText("Пауза");
        }
        else
        {
            QVector<float>arg;
            m_pSolvers->Solve(Solver_BB, arg);
            ui->StartBBBut->setText("Пауза");
        }
    }
    else
    {
        if (m_pSolvers->IsWorking(Solver_BB))
        {
            m_pSolvers->Pause(Solver_BB);
            ui->StartBBBut->setText("Приостановленно");
        }
        else
        {
            ui->StartBBBut->setText("Старт");
        }
    }
    setWorking(m_pSolvers->IsWorking(Solver_BB));
}

void TSP_SolverWindow::on_actionStopBB_triggered()
{
    m_pSolvers->Stop(Solver_BB);
}


void TSP_SolverWindow::on_actionShowBestResult_toggled(bool arg1)
{
    m_pCanvas->ShowBest(arg1);
}

void TSP_SolverWindow::setWorking(bool flag)
{
    working = flag;
    emit onWorking(flag);
    m_pCanvas->setEnabled(!flag);
}

void TSP_SolverWindow::on_actionClear_triggered()
{
    m_pMap->Clear();
    setWorking(false);
}

void TSP_SolverWindow::on_actionGenerate_triggered()
{
    m_pMap->Clear();
    m_pMap->GenerateRandom(51);
}

void TSP_SolverWindow::saveTSP(QString fileName)
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
        emit newFileName(fileName);
    }
}


void TSP_SolverWindow::MatrixUpdated()
{
    auto matrix = m_pMap->GetMatrix();
    QString str = "<table border=\"1\" cellpadding=\"2\" cellspacing=\"2\">";
    str += "<tr>";
    str += "<th>/</th>";
    for (size_t i = 0; i < matrix.size(); i++)
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


void TSP_SolverWindow::on_UpdateBut_clicked()
{
    MatrixUpdated();
}

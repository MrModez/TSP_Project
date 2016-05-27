// ===== Copyright © 2015-2016, MrModez (Zagir Fabarisov), Flatag (Tagir Fabarisov), All rights reserved. =====
//
// Purpose: Widget-window for experimental solving
// Назначение: Виджет для решения экспериментов
//
// ============================================================================================================
#include "TSP_ExpertWindow.h"
#include "ui_TSP_ExpertWindow.h"
#include <QtCore>
#include <QFileDialog>
#include <QMessageBox>
#include "TSP_Map.h"
#include "TSP_ExpertManager.h"

TSP_ExpertWindow::TSP_ExpertWindow(QWidget *parent) :
    TSP_BaseWindow(parent),
    ui(new Ui::TSP_ExpertWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pExpert = new TSP_ExpertManager(m_pMap, this);
    connect(m_pExpert, &TSP_ExpertManager::updateTable, this, &TSP_ExpertWindow::UpdateTable);
    connect(m_pExpert, &TSP_ExpertManager::finishedWorking, this, &TSP_ExpertWindow::Finished);
}

TSP_ExpertWindow::~TSP_ExpertWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pExpert;
}

void TSP_ExpertWindow::on_actionOpen_triggered()
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
    }
    else
        qDebug() << "not exist";
}

void TSP_ExpertWindow::on_StartBut_clicked()
{
    int iSize = ui->spinBox->value();
    int iCities = ui->spinBox_2->value();
    int iTries = ui->spinBox_3->value();

    QVector<int>args = {iSize, iCities, iTries};
    results.resize(iTries);
    for (auto &res : results)
        res.resize(iSize);
    m_pExpert->Init(args);

    emit onWorking(true);
    PrintTable();
}

void TSP_ExpertWindow::UpdateTable(int ID, int iter, float fit)
{
    results[iter][ID] = fit;
    PrintTable();
}

void TSP_ExpertWindow::Finished()
{
    emit onWorking(false);
}

void TSP_ExpertWindow::PrintTable()
{
    QString str = "<table border=\"1\" width=\"100%\" cellpadding=\"2\" cellspacing=\"2\">";
    str += "<tr>";
    str += "<th>/</th>";
    /*
    for (int i = 0; i < results[0].size(); i++)
    {
        str += "<th>" + QString::number(i) + "</th>";
    }*/
    str += "<th>Без мутации</th>";
    str += "<th>SWAP</th>";
    str += "<th>MOVE</th>";
    str += "<th>REVERSE</th>";
    str += "<th>SWAP MOVE</th>";
    str += "<th>MOVE REVERSE</th>";
    str += "<th>SWAP REVERSE</th>";
    str += "<th>SWAP MOVE REVERSE</th>";
    str += "</tr>";
    int a = 0;
    for (auto &res : results)
    {
        str += "<tr>";
        str += "<th>" + QString::number(a++) + "</th>";
        for (auto &val : res)
        {
            str += "<td>" + QString::number(val) + "</td>";
        }
        str += "</tr>";
    }
    str += "</table>";
    ui->textEdit->setHtml(str);
}

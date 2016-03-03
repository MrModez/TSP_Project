#include "TSP_MainWindow.h"
#include <QtCore>
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_SolverCollection.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pSolvers = new TSP_SolverCollection(m_pMap);
    m_pCanvas = new TSP_Canvas(this, m_pMap);

    connect(m_pCanvas, &TSP_Canvas::addCity, m_pMap, &TSP_Map::addCity);
    connect(m_pCanvas, &TSP_Canvas::moveCity, m_pMap, &TSP_Map::moveCity);
    connect(m_pCanvas, &TSP_Canvas::removeCity, m_pMap, &TSP_Map::removeCity);

    setCentralWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
}

void MainWindow::on_actionStartGA_triggered()
{
    m_pSolvers->Solve(Solver_GA);
}

void MainWindow::on_actionStopGA_triggered()
{
    m_pSolvers->Stop(Solver_GA);
}

void MainWindow::on_actionStartBB_triggered()
{
    m_pSolvers->Solve(Solver_BB);
}

void MainWindow::on_actionStopBB_triggered()
{
    m_pSolvers->Stop(Solver_BB);
}

void MainWindow::on_actionOpen_triggered()
{
    if(QFile(QDir::currentPath() + "/../test.dat").exists())
    {
        QSettings settings(QDir::currentPath() + "/../test.dat", QSettings::IniFormat);
        settings.sync();
        foreach(auto child, settings.childGroups())
        {
            settings.beginGroup(child);
            float x = settings.value("x",0).toFloat();
            float y = settings.value("y",0).toFloat();
            settings.endGroup();
            //qDebug() << child;
            //qDebug() << x << y;
            //emit addCity(x, y);
            m_pMap->addCity(x, y);
        }
        m_pCanvas->repaint();
    }
    else
        qDebug() << "not exist";
}

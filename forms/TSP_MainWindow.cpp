#include "TSP_MainWindow.h"
#include <QtCore>
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_SolverGA.h"
#include "TSP_SolverBB.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pCanvas = new TSP_Canvas(this, m_pMap);
    m_pSolverGA = NULL;
    m_pSolverBB = NULL;

    connect(m_pCanvas, &TSP_Canvas::addCity, m_pMap, &TSP_Map::addCity);
    connect(m_pCanvas, &TSP_Canvas::moveCity, m_pMap, &TSP_Map::moveCity);
    connect(m_pCanvas, &TSP_Canvas::removeCity, m_pMap, &TSP_Map::removeCity);
    //connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::StartGA);
    //connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::StopGA);

    setCentralWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
}

void MainWindow::StartGA()
{
    qDebug("MainWindow::StartGA");

    QThread *pGAThread = new QThread;
    m_pSolverGA = new TSP_SolverGA(new TSP_GA(), m_pMap);
    m_pSolverGA->moveToThread(pGAThread);

    qRegisterMetaType<vectorint>("vectorint");
    connect(m_pSolverGA, &TSP_SolverGA::updateWay,  m_pMap, &TSP_Map::SetWay);
    connect(pGAThread, &QThread::started, m_pSolverGA, &TSP_SolverGA::StartAlgorithm);
    connect(m_pSolverGA, &TSP_SolverGA::finished, pGAThread, &QThread::quit);
    connect(m_pSolverGA, &TSP_SolverGA::finished, m_pSolverGA, &TSP_SolverGA::deleteLater);
    connect(pGAThread, &QThread::finished, pGAThread, &QThread::deleteLater);

    int pop = 100000;
    float elit = 0.001f;
    float mut = 0.55f;
    float supmut = 0.75f;
    m_pSolverGA->SetSettings(pop, elit, mut, supmut);

    pGAThread->start();
}

void MainWindow::StopGA()
{
    qDebug("MainWindow::StopGA");
    m_pSolverGA->StopAlgorithm();
}

void MainWindow::StartBB()
{
    qDebug("MainWindow::StartBB");

    QThread *pBBThread = new QThread;
    m_pSolverBB = new TSP_SolverBB(new TSP_BB(), m_pMap);
    m_pSolverBB->moveToThread(pBBThread);

    qRegisterMetaType<vectorint>("vectorint");
    connect(m_pSolverBB, &TSP_SolverBB::updateWay,  m_pMap, &TSP_Map::SetWay);
    connect(pBBThread, &QThread::started, m_pSolverBB, &TSP_SolverBB::StartAlgorithm);
    connect(m_pSolverBB, &TSP_SolverBB::finished, pBBThread, &QThread::quit);
    connect(m_pSolverBB, &TSP_SolverBB::finished, m_pSolverBB, &TSP_SolverBB::deleteLater);
    connect(pBBThread, &QThread::finished, pBBThread, &QThread::deleteLater);

   // int pop = 100000;
   // float elit = 0.001f;
   // float mut = 0.55f;
   // float supmut = 0.75f;
   // m_pSolverBB->SetSettings(pop, elit, mut, supmut);

    pBBThread->start();
}

void MainWindow::StopBB()
{
    qDebug("MainWindow::StopBB");
    m_pSolverBB->StopAlgorithm();
}

void MainWindow::on_actionStartGA_triggered()
{
    StartGA();
}

void MainWindow::on_actionStopGA_triggered()
{
    StopGA();
}

void MainWindow::on_actionStartBB_triggered()
{
    StartBB();
}

void MainWindow::on_actionStopBB_triggered()
{
    StopBB();
}

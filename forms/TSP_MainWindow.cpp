#include "TSP_MainWindow.h"
#include <QtCore>
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_SolverGA.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pCanvas = new TSP_Canvas(this, m_pMap);
    m_pSolverGA = NULL;

    connect(m_pCanvas, &TSP_Canvas::addCity, m_pMap, &TSP_Map::addCity);
    connect(m_pCanvas, &TSP_Canvas::moveCity, m_pMap, &TSP_Map::moveCity);
    connect(m_pCanvas, &TSP_Canvas::removeCity, m_pMap, &TSP_Map::removeCity);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::StartGA);

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
    if (m_pSolverGA)
        return;

    QThread *pGAThread = new QThread(this);
    m_pSolverGA = new TSP_SolverGA(new TSP_GA(), m_pMap);

    connect(m_pSolverGA, &TSP_SolverGA::updateWay,  m_pMap, &TSP_Map::SetWay);
    connect(pGAThread, &QThread::started, m_pSolverGA, &TSP_SolverGA::StartAlgorithm);
    connect(m_pSolverGA, &TSP_SolverGA::finished, pGAThread, &QThread::quit);
    connect(m_pSolverGA, &TSP_SolverGA::finished, m_pSolverGA, &TSP_SolverGA::deleteLater);
    connect(pGAThread, &QThread::finished, pGAThread, &QThread::deleteLater);
    connect(ui->pushButton_2, &QPushButton::clicked, m_pSolverGA, &TSP_SolverGA::StopAlgorithm);

    int pop = 20000;
    float elit = 0.05f;
    float mut = 0.8f;
    float supmut = 0.6f;
    m_pSolverGA->SetSettings(pop, elit, mut, supmut);
    m_pSolverGA->moveToThread(pGAThread);

    pGAThread->start();
}

#include "TSP_MainWindow.h"
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

    QObject::connect(m_pCanvas, SIGNAL(addCity(int, int)),
                     m_pMap, SLOT(addCity(int, int)));
    QObject::connect(m_pCanvas, SIGNAL(moveCity(int, int, int)),
                     m_pMap, SLOT(moveCity(int, int, int)));
    QObject::connect(m_pCanvas, SIGNAL(removeCity(int)),
                     m_pMap, SLOT(removeCity(int)));
    QObject::connect(ui->pushButton, SIGNAL(clicked()),
                     this, SLOT(StartGA()));

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

    QThread *pGAThread = new QThread;
    m_pSolverGA = new TSP_SolverGA(new TSP_GA(), m_pMap);
    m_pSolverGA->moveToThread(pGAThread);

    QObject::connect(pGAThread, SIGNAL(started()),
                     m_pSolverGA, SLOT(StartAlgorithm()));
    QObject::connect(m_pSolverGA, SIGNAL(finished()),
                     pGAThread, SLOT(quit()));
    QObject::connect(m_pSolverGA, SIGNAL(finished()),
                     m_pSolverGA, SLOT(deleteLater()));
    QObject::connect(pGAThread, SIGNAL(finished()),
                     pGAThread, SLOT(deleteLater()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()),
                     m_pSolverGA, SLOT(StopAlgorithm()));

    int pop = 1000;
    float elit = 0.2f;
    float mut = 0.2f;
    float supmut = 0.5f;
    m_pSolverGA->SetSettings(pop, elit, mut, supmut);

    pGAThread->start();
}

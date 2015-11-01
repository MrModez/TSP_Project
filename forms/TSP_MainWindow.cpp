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
    m_pSolverGA = new TSP_SolverGA(new TSP_GA(), m_pMap);

    //m_pSolvers = new TSP_SolverCollection();
    //m_pSolvers->AddSolver(Prob_GA);

    QObject::connect(m_pCanvas, SIGNAL(addCity(int, int)),
                     m_pMap, SLOT(addCity(int, int)));
    QObject::connect(m_pCanvas, SIGNAL(moveCity(int, int, int)),
                     m_pMap, SLOT(moveCity(int, int, int)));
    QObject::connect(m_pCanvas, SIGNAL(removeCity(int)),
                     m_pMap, SLOT(removeCity(int)));

    QObject::connect(this, SIGNAL(StartGA()),
                     m_pSolverGA, SLOT(StartAlgorithm()));
    QObject::connect(this, SIGNAL(StopGA()),
                     m_pSolverGA, SLOT(StopAlgorithm()));

    setCentralWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
    delete m_pSolverGA;
}

void MainWindow::on_pushButton_clicked()
{
    int pop = 1000;
    float elit = 0.2f;
    float mut = 0.2f;
    float supmut = 0.5f;
    m_pSolverGA->SetSettings(pop, elit, mut, supmut);
    emit StartGA();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit StopGA();
}

#include "TSP_MainWindow.h"
#include "TSP_Map.h"
#include "TSP_Canvas.h"
#include "TSP_GA.h"
#include "TSP_BB.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pMap = new TSP_Map();
    m_pCanvas = new TSP_Canvas(this, m_pMap);
    m_pGA = new TSP_GA(m_pMap);
    m_pBB = new TSP_BB(m_pMap);

    QObject::connect(m_pCanvas, SIGNAL(addCity(int, int)),
                     m_pMap, SLOT(addCity(int, int)));
    QObject::connect(m_pCanvas, SIGNAL(moveCity(int, int, int)),
                     m_pMap, SLOT(moveCity(int, int, int)));
    QObject::connect(m_pCanvas, SIGNAL(removeCity(int)),
                     m_pMap, SLOT(removeCity(int)));

    QObject::connect(this, SIGNAL(StartGA()),
                     m_pGA, SLOT(StartAlgorithm()));
    QObject::connect(this, SIGNAL(StopGA()),
                     m_pGA, SLOT(StopAlgorithm()));

    setCentralWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
    delete m_pGA;
    delete m_pBB;
}

void MainWindow::on_pushButton_clicked()
{
    int pop = 1000;
    float elit = 0.2f;
    float mut = 0.2f;
    float supmut = 0.5f;
    m_pGA->SetSettings(pop, elit, mut, supmut);
    emit StartGA();
    start();
}

void MainWindow::on_pushButton_2_clicked()
{
    emit StopGA();
}

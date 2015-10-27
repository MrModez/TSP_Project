#include "tsp_mainwindow.h"
#include "ui_tsp_mainwindow.h"
#include "tsp_map.h"
#include "tsp_canvas.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pMap = new TSP_Map();
    m_pCanvas = new Canvas(this, m_pMap);
    QObject::connect(m_pCanvas, SIGNAL(addCity(int, int)),
                     m_pMap, SLOT(addCity(int, int)));
    QObject::connect(m_pCanvas, SIGNAL(moveCity(int, int, int)),
                     m_pMap, SLOT(moveCity(int, int, int)));
    QObject::connect(m_pCanvas, SIGNAL(removeCity(int)),
                     m_pMap, SLOT(removeCity(int)));
    setCentralWidget(m_pCanvas);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pMap;
    delete m_pCanvas;
}

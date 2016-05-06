#include "TSP_MainWindow.h"
#include <QtCore>
#include <QFileDialog>
#include "TSP_SolverWindow.h"
#include "TSP_ExpertWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFileName("");
    m_pWindow = nullptr;
    m_Mode = TSP_NONE;
    setMode(TSP_SOLVER);

    QActionGroup* group = new QActionGroup(this);
    ui->actionSolver->setActionGroup(group);
    ui->actionExpert->setActionGroup(group);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::setMode(TSP_Mode mode)
{
    if (m_Mode == mode)
        return;
    if (m_pWindow != nullptr)
    {
        disconnect(m_pWindow, 0, 0, 0);
        m_pWindow->deleteLater();
        m_pWindow = nullptr;
    }
    if (mode == TSP_SOLVER)
    {
        m_pWindow = new TSP_SolverWindow(this);
        ui->actionClear->setEnabled(true);
        ui->actionGenerate->setEnabled(true);
    }
    else if (mode == TSP_EXPERT)
    {
        m_pWindow = new TSP_ExpertWindow(this);
        ui->actionClear->setEnabled(false);
        ui->actionGenerate->setEnabled(false);
    }
    connect(m_pWindow, &TSP_BaseWindow::newFileName, this, &MainWindow::setFileName);
    connect(m_pWindow, &TSP_BaseWindow::onWorking, this, &MainWindow::onWorking);
    setCentralWidget(m_pWindow);
    m_Mode = mode;
    on_actionNew_triggered();
}

void MainWindow::onWorking(bool flag)
{
    menuBar()->setEnabled(!flag);
}

void MainWindow::on_actionNew_triggered()
{
    setFileName("");
    m_pWindow->on_actionNew_triggered();
}

void MainWindow::on_actionOpen_triggered()
{
    m_pWindow->on_actionOpen_triggered();
}

void MainWindow::on_actionSave_triggered()
{
    if (Filename.isEmpty())
    {
        m_pWindow->on_actionSaveAs_triggered();
        return;
    }
    else
        m_pWindow->on_actionSave_triggered(Filename);
}

void MainWindow::on_actionSaveAs_triggered()
{
    m_pWindow->on_actionSaveAs_triggered();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionSolver_triggered()
{
    setMode(TSP_SOLVER);
}

void MainWindow::on_actionExpert_triggered()
{
    setMode(TSP_EXPERT);
}

void MainWindow::on_actionGenerate_triggered()
{
    m_pWindow->on_actionGenerate_triggered();
}

void MainWindow::on_actionClear_triggered()
{
    m_pWindow->on_actionClear_triggered();
}

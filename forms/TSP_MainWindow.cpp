#include "TSP_MainWindow.h"
#include <QtCore>
#include <QFileDialog>
#include "TSP_SolverWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFileName("");

    m_pWindow = new TSP_SolverWindow(this);
    connect(m_pWindow, &TSP_BaseWindow::newFileName, this, &MainWindow::setFileName);

    this->setCentralWidget(m_pWindow);
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

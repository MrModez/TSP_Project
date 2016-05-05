#include "TSP_ExpertWindow.h"
#include "ui_TSP_ExpertWindow.h"
#include "TSP_ExpertManager.h"

TSP_ExpertWindow::TSP_ExpertWindow(QWidget *parent) :
    TSP_BaseWindow(parent),
    ui(new Ui::TSP_ExpertWindow)
{
    ui->setupUi(this);

    m_pExpert = new TSP_ExpertManager(this);
}

TSP_ExpertWindow::~TSP_ExpertWindow()
{
    delete ui;
}

void TSP_ExpertWindow::on_StartBut_clicked()
{
    QVector<float>args = {20, 10, 5};
    m_pExpert->Init(args);
}

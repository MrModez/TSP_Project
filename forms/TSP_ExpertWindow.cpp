#include "TSP_ExpertWindow.h"
#include "ui_TSP_ExpertWindow.h"

TSP_ExpertWindow::TSP_ExpertWindow(QWidget *parent) :
    TSP_BaseWindow(parent),
    ui(new Ui::TSP_ExpertWindow)
{
    ui->setupUi(this);
}

TSP_ExpertWindow::~TSP_ExpertWindow()
{
    delete ui;
}

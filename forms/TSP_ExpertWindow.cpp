#include "TSP_ExpertWindow.h"
#include "ui_TSP_ExpertWindow.h"
#include "TSP_ExpertManager.h"

TSP_ExpertWindow::TSP_ExpertWindow(QWidget *parent) :
    TSP_BaseWindow(parent),
    ui(new Ui::TSP_ExpertWindow)
{
    ui->setupUi(this);

    m_pExpert = new TSP_ExpertManager(this);
    connect(m_pExpert, &TSP_ExpertManager::UpdateTable, this, &TSP_ExpertWindow::updateTable);
}

TSP_ExpertWindow::~TSP_ExpertWindow()
{
    delete ui;
}

void TSP_ExpertWindow::on_StartBut_clicked()
{
    int iSize = ui->spinBox->value();
    int iCities = ui->spinBox_2->value();
    int iTries = ui->spinBox_3->value();

    QVector<float>args = {iSize, iCities, iTries};
    results.resize(iSize);
    for (auto &res : results)
        res.resize(iTries);
    m_pExpert->Init(args);
    printTable();
}

void TSP_ExpertWindow::updateTable(int ID, int iter, float fit)
{
    results[ID][iter] = fit;
    printTable();
}

void TSP_ExpertWindow::printTable()
{
    QString str = "<table border=\"1\" cellpadding=\"2\" cellspacing=\"2\">";
    str += "<tr>";
    str += "<th>/</th>";
    for (int i = 0; i < results[0].size(); i++)
    {
        str += "<th>" + QString::number(i) + "</th>";
    }
    str += "</tr>";
    int a = 0;
    for (auto &res : results)
    {
        str += "<tr>";
        str += "<th>" + QString::number(a++) + "</th>";
        for (auto &val : res)
        {
            str += "<td>" + QString::number(val) + "</td>";
        }
        str += "</tr>";
    }
    str += "</table>";
    ui->textEdit->setHtml(str);
}

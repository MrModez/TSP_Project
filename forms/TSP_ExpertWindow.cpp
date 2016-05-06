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
    QVector<float>args = {20, 20, 5};
    results.resize(20);
    for (auto &res : results)
        res.resize(5);
    m_pExpert->Init(args);
}

void TSP_ExpertWindow::updateTable(int ID, int iter, float fit)
{
    results[ID][5-iter] = fit;

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
            //float fnum = floor(num * 5 + 0.5) / 5;
            str += "<td>" + QString::number(val) + "</td>";
        }
        str += "</tr>";
    }
    str += "</table>";
    ui->textEdit->setHtml(str);
}

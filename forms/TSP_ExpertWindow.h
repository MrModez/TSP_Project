#ifndef TSP_EXPERTWINDOW_H
#define TSP_EXPERTWINDOW_H

#include <TSP_BaseWindow.h>
#include <QWidget>
#include <QVector>

class TSP_ExpertManager;

namespace Ui {
class TSP_ExpertWindow;
}

class TSP_ExpertWindow : public TSP_BaseWindow
{
    Q_OBJECT

public:
    explicit TSP_ExpertWindow(QWidget *parent = 0);
    ~TSP_ExpertWindow();
    void PrintTable();
    void Finished();

private slots:
    void on_StartBut_clicked();
    void UpdateTable(int ID, int iter, float fit);

private:
    Ui::TSP_ExpertWindow *ui;
    TSP_ExpertManager   *m_pExpert;
    QVector<QVector<float>> results;
};

#endif // TSP_EXPERTWINDOW_H

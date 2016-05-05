#ifndef TSP_EXPERTWINDOW_H
#define TSP_EXPERTWINDOW_H

#include <TSP_BaseWindow.h>
#include <QWidget>

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

private slots:
    void on_StartBut_clicked();

private:
    Ui::TSP_ExpertWindow *ui;
    TSP_ExpertManager   *m_pExpert;
};

#endif // TSP_EXPERTWINDOW_H

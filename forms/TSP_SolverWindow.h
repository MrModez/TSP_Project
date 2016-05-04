#ifndef TSP_SOLVERWINDOW_H
#define TSP_SOLVERWINDOW_H

#include <TSP_BaseWindow.h>
#include <QWidget>

class TSP_Canvas;
class TSP_Map;
class TSP_SolverCollection;

namespace Ui {
class TSP_SolverWindow;
}

class TSP_SolverWindow : public TSP_BaseWindow
{
    Q_OBJECT

public:
    explicit TSP_SolverWindow(QWidget *parent = 0);
    ~TSP_SolverWindow();

    void saveTSP(QString filename);
    void setWorking(bool flag);

public slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered(QString Filename);
    void on_actionSaveAs_triggered();

private slots:
    void on_actionStartGA_toggled(bool arg1);
    void on_actionStartBB_toggled(bool arg1);
    void on_actionStopGA_triggered();
    void on_actionStopBB_triggered();
    void on_actionShowBestResult_toggled(bool arg1);
    void on_actionClear_triggered();
    void on_UpdateBut_clicked();
    void MatrixUpdated();

private:
    Ui::TSP_SolverWindow *ui;
    TSP_Canvas          *m_pCanvas;
    TSP_Map             *m_pMap;
    TSP_SolverCollection *m_pSolvers;
    bool            working;
};

#endif // TSP_SOLVERWINDOW_H

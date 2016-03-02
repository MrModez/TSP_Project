#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_TSP_MainWindow.h"
#include <QMainWindow>

class TSP_Canvas;
class TSP_Map;
class TSP_SolverCollection;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionStartGA_triggered();
    void on_actionStopGA_triggered();
    void on_actionStartBB_triggered();
    void on_actionStopBB_triggered();

private:
    Ui::MainWindow      *ui;
    TSP_Canvas          *m_pCanvas;
    TSP_Map             *m_pMap;
    TSP_SolverCollection *m_pSolvers;
};

#endif // MAINWINDOW_H

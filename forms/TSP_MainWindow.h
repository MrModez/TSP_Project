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

    void setFileName(QString name);
    void saveTSP(QString filename);
    void setWorking(bool flag);

private slots:
    void on_actionStartGA_toggled(bool arg1);
    void on_actionStartBB_toggled(bool arg1);
    void on_actionStopGA_triggered();
    void on_actionStopBB_triggered();
    void on_actionOpen_triggered();
    void on_actionShowBestResult_toggled(bool arg1);
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClear_triggered();
    void on_actionExit_triggered();
    void on_UpdateBut_clicked();
    void MatrixUpdated();

private:
    Ui::MainWindow      *ui;
    TSP_Canvas          *m_pCanvas;
    TSP_Map             *m_pMap;
    TSP_SolverCollection *m_pSolvers;
    QString         Filename;
    bool            working;
};

#endif // MAINWINDOW_H

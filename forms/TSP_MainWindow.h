#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_TSP_MainWindow.h"
#include <QMainWindow>

class TSP_BaseWindow;

namespace Ui {
class MainWindow;
}

enum TSP_Mode
{
    TSP_NONE = -1,
    TSP_SOLVER = 0,
    TSP_EXPERT
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFileName(QString name);
    void setMode(TSP_Mode mode);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();
    void on_actionSolver_triggered();
    void on_actionExpert_triggered();

private:
    Ui::MainWindow      *ui;
    TSP_BaseWindow      *m_pWindow;
    QString             Filename;
    TSP_Mode            m_Mode;
};

#endif // MAINWINDOW_H

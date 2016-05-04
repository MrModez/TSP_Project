#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_TSP_MainWindow.h"
#include <QMainWindow>

class TSP_SolverWindow;
class TSP_BaseWindow;

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

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionNew_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow      *ui;
    TSP_BaseWindow      *m_pWindow;
    QString         Filename;
};

#endif // MAINWINDOW_H

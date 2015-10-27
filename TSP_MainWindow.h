#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TSP_Map;
class Canvas;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TSP_Map* m_pMap;
    Canvas *m_pCanvas;
};

#endif // MAINWINDOW_H

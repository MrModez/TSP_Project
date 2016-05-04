#ifndef TSP_BASEWINDOW_H
#define TSP_BASEWINDOW_H

#include <QWidget>

class TSP_BaseWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TSP_BaseWindow(QWidget *parent = 0);

public slots:
    virtual void on_actionNew_triggered(){}
    virtual void on_actionOpen_triggered(){}
    virtual void on_actionSave_triggered(QString){}
    virtual void on_actionSaveAs_triggered(){}

signals:
    void newFileName(QString Filename);
};

#endif // TSP_BASEWINDOW_H

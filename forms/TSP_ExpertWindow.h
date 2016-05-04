#ifndef TSP_EXPERTWINDOW_H
#define TSP_EXPERTWINDOW_H

#include <TSP_BaseWindow.h>
#include <QWidget>

namespace Ui {
class TSP_ExpertWindow;
}

class TSP_ExpertWindow : public TSP_BaseWindow
{
    Q_OBJECT

public:
    explicit TSP_ExpertWindow(QWidget *parent = 0);
    ~TSP_ExpertWindow();

private:
    Ui::TSP_ExpertWindow *ui;
};

#endif // TSP_EXPERTWINDOW_H

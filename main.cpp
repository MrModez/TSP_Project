#include "TSP_MainWindow.h"
#include <QApplication>
#include "omp.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();

    return app.exec();
}

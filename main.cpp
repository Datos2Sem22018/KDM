#include "mainwindow.h"
#include <QApplication>
#include <thread>

int run(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    run(argc, argv);
    return 0;
}

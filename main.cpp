#include "mainwindow.h"
#include "client.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
//w.createChart();
//QTimer timer;//定时器
//QObject::connect(&timer,&QTimer::timeout,&w,&MainWindow::creat);
//timer.start(300);

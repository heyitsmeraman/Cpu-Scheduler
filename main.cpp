#include "mainwindow.h"
#include <QApplication>

process p[10],p1[10],temp;
queue<int>q1;
int num;
int ch;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

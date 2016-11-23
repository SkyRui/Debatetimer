#include "mainview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;

    w.setWindowTitle("辩论计时 1.0");

    return a.exec();
}

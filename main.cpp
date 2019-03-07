#include "mainwindow.h"
#include <QApplication>
#include <mosquitto.h>

int main(int argc, char *argv[])
{
    mosquitto_lib_init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    mosquitto_lib_cleanup();
    return a.exec();
}

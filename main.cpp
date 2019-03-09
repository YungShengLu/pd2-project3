#include "mainwindow.h"

#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    srand(time(NULL));

    MainWindow w;
    w.show();

    return app.exec();
}

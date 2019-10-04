//=============================================================================
#include "mainwindow.h"
//=============================================================================
#include <QApplication>
//=============================================================================

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mainwindow w;
    w.setWindowTitle("Weather");
    w.show();

    return a.exec();
}

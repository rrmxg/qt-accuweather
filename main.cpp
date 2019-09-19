#include "gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GUI gui;
    gui.setWindowTitle("Weather");
    gui.show();

    return a.exec();
}

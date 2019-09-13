#ifndef GUI_H
#define GUI_H

#include <QWidget>

#include "accuweather.h"

namespace Ui
{
class GUI;
}

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:
    void on_pushButton_show_clicked();

private:
    Ui::GUI *ui;
};
#endif // GUI_H

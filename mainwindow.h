#ifndef GUI_H
#define GUI_H
//=============================================================================
#include <QWidget>
#include <QMap>
//=============================================================================
#include "accuweather.h"
//=============================================================================

namespace Ui
{
class Mainwindow;
}

class Mainwindow : public QWidget
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

private slots:
    void on_pushButton_search_clicked();
    void on_pushButton_show_clicked  ();

private:
    Ui::Mainwindow *ui;

    AccuWeather g_accuweather;
    QMap<QString, int> g_countries;
};
#endif // GUI_H

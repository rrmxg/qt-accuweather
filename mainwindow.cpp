//=============================================================================
#include "mainwindow.h"
#include "ui_mainwindow.h"
//=============================================================================
#include <QDebug>
//=============================================================================
const QString APIKEY       = ;
const QString CITY_NAME    = "moscow";
const QString COUNTRY_NAME = "Russia(Moscow)";
//=============================================================================

Mainwindow::Mainwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainwindow)
{
    ui->setupUi(this);

    g_accuweather.setApiKey(APIKEY);

    ui->comboBox_typeForecasts->addItems(FORECASTS_HOURS);
    ui->comboBox_typeForecasts->addItems(FORECASTS_DAYS );

    ui->lineEdit_cityName
            ->setPlaceholderText("example: moscow");
}

Mainwindow::~Mainwindow()
{
    g_countries.clear();

    delete ui;
}

void Mainwindow::on_pushButton_search_clicked()
{
    if (ui->lineEdit_cityName->text().isEmpty())
        return;

    g_countries.clear();

    if (g_accuweather.getCountriesList(ui->lineEdit_cityName->text(),
                                       g_countries))
    {
        ui->comboBox_countries->addItems(g_countries.keys());
    }
}

void Mainwindow::on_pushButton_show_clicked()
{
    if (g_countries.isEmpty())
        return;

    int locationKey = g_countries.find
            (ui->comboBox_countries->currentText()).value();

    if (g_accuweather.getForecast(locationKey,
                                  ui->comboBox_typeForecasts->currentText()))
    {
        for (ForecastData fd : g_accuweather.forecastData)
        {
            ui->textEdit->append(fd.showData());
        }
    }
    else
    {
        ui->textEdit->append("error --- getForecast");
    }
}

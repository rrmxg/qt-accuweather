#include "gui.h"
#include "ui_gui.h"

#include <QDebug>

GUI::GUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
}

GUI::~GUI()
{
    delete ui;
}

// --- SERVICE IN TRIAL MODE HAS A LIMITED NUMBER OF REQUESTS TO THE APPLICATION ---

const QString APIKEY = ;
const QString CITY   = ;

void GUI::on_pushButton_show_clicked()
{
    // STEP ONE ///////////////////////////////////////////////////////////////////
    QString cityName = CITY;

    // STEP TWO ///////////////////////////////////////////////////////////////////
    QString forecastType = FORECASTS_DAYS[];

    // STEP THREE /////////////////////////////////////////////////////////////////
    QMap<QDate, WeatherDay> weatherDays;

    // STEP FOUR //////////////////////////////////////////////////////////////////
    AccuWeather accuWeather(APIKEY);

    // STEP FIVE //////////////////////////////////////////////////////////////////
    if (!accuWeather.getLocationKey(cityName))
    {
        ui->textEdit->append("error --- getLocationKey = " + cityName);
        return;
    }

    // STEP SIX ///////////////////////////////////////////////////////////////////
    if (accuWeather.getForecast(forecastType, weatherDays))
    {
        QMap<QDate, WeatherDay>::const_iterator it = weatherDays.constBegin();
        while (it != weatherDays.constEnd())
        {
            ui->textEdit->append("date            --- " +                 it.key  ().toString()      );
            ui->textEdit->append("dayOfWeek       --- " +                 it.value().dayOfWeek       );
            ui->textEdit->append("temperatureMinF --- " + QString::number(it.value().temperatureMinF));
            ui->textEdit->append("temperatureMinC --- " + QString::number(it.value().temperatureMinC));
            ui->textEdit->append("temperatureMaxF --- " + QString::number(it.value().temperatureMaxF));
            ui->textEdit->append("temperatureMaxC --- " + QString::number(it.value().temperatureMaxC));
            ui->textEdit->append("iconDayNo       --- " + QString::number(it.value().iconDayNo      ));
            ui->textEdit->append("iconPhraseDay   --- " +                 it.value().iconPhraseDay   );
            ui->textEdit->append("iconNightNo     --- " + QString::number(it.value().iconNightNo    ));
            ui->textEdit->append("iconPhraseNight --- " +                 it.value().iconPhraseNight );

            ui->textEdit->append("\n\n");

            ++it;
        }
        weatherDays.clear();
    }
    else
    {
        ui->textEdit->append("error --- getForecast = " + forecastType);
    }
}

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

/*
    --- SERVICE IN TRIAL MODE HAS A LIMITED NUMBER OF REQUESTS TO THE APPLICATION ---
*/

const QString APIKEY = ;
const QString CITY   = ;

void GUI::on_pushButton_show_clicked()
{
    QMap<QDate, WeatherDay>  weatherDays;
    QMap<QTime, WeatherHour> weatherHours;

    AccuWeather accuWeather;

    accuWeather.setData(CITY, APIKEY, FORECASTS_DAYS[]);
    {
        accuWeather.getData(weatherDays);

        QMap<QDate, WeatherDay>::const_iterator it = weatherDays.constBegin();
        while (it != weatherDays.constEnd())
        {
            ui->textEdit->append("date            --- " +                 it.key  ().toString()     );
            ui->textEdit->append("dayOfWeek       --- " +                 it.value().dayOfWeek      );
            ui->textEdit->append("temperatureMin  --- " + QString::number(it.value().temperatureMin));
            ui->textEdit->append("temperatureMax  --- " + QString::number(it.value().temperatureMax));
            ui->textEdit->append("iconDayNo       --- " + QString::number(it.value().iconDayNo     ));
            ui->textEdit->append("iconPhraseDay   --- " +                 it.value().iconPhraseDay  );
            ui->textEdit->append("iconNightNo     --- " + QString::number(it.value().iconNightNo   ));
            ui->textEdit->append("iconPhraseNight --- " +                 it.value().iconPhraseNight);

            ui->textEdit->append("\n\n");

             ++it;
        }
        if (!weatherDays.isEmpty())
            weatherDays.clear();
    }

    accuWeather.setData(CITY, APIKEY, FORECASTS_HOURS[]);
    {
        accuWeather.getData(weatherHours);

        QMap<QTime, WeatherHour>::const_iterator it = weatherHours.constBegin();
        while (it != weatherHours.constEnd())
        {
            ui->textEdit->append("times       --- " +                 it.key  ().toString()     );
            ui->textEdit->append("date        --- " +                 it.value().date.toString());
            ui->textEdit->append("dayOfWeek   --- " +                 it.value().dayOfWeek      );
            ui->textEdit->append("isDayNight  --- " + QString::number(it.value().isDayNight    ));
            ui->textEdit->append("tenperature --- " + QString::number(it.value().temperature   ));
            ui->textEdit->append("iconNo      --- " + QString::number(it.value().iconNo        ));
            ui->textEdit->append("iconPhrase  --- " +                 it.value().iconPhrase     );

            ui->textEdit->append("\n\n");

             ++it;
        }
        if (!weatherHours.isEmpty())
            weatherHours.clear();
    }
}

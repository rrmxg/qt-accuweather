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
    --- THE SERVICE HAS A LIMITED NUMBER OF REQUESTS FOR THE APPLICATION ---
    --- IN CASE OF FREQUENT ERRORS, YOU NEED TO DELETE THE APPLICATION AND CREATE A NEW ONE ---
*/

const QString APIKEY = ;
const QString CITY   = ;

void GUI::on_pushButton_show_clicked()
{
    qDebug() << "click --- on_pushButton_show_clicked";

    QMap<QDate, WeatherDay>  weatherDay;
    QMap<QTime, WeatherHour> weatherHour;

    AccuWeather w;

    w.SetApiInfo(CITY, APIKEY, FORECASTS_DAY[]);
    {
        w.GetWeatherDay(weatherDay);

        QMap<QDate, WeatherDay>::const_iterator it = weatherDay.constBegin();
        while (it != weatherDay.constEnd())
        {
            ui->textEdit->append("date            --- " +                 it.key  ().toString()     );
            ui->textEdit->append("dayOfWeek       --- " +                 it.value().dayOfWeek      );
            ui->textEdit->append("temperatureMin  --- " + QString::number(it.value().temperatureMin));
            ui->textEdit->append("temperatureMax  --- " + QString::number(it.value().temperatureMax));
            ui->textEdit->append("iconDay         --- " + QString::number(it.value().iconDay       ));
            ui->textEdit->append("iconPhraseDay   --- " +                 it.value().iconPhraseDay  );
            ui->textEdit->append("iconNight       --- " + QString::number(it.value().iconNight     ));
            ui->textEdit->append("iconPhraseNight --- " +                 it.value().iconPhraseNight);

            ui->textEdit->append("\n\n");

             ++it;
        }
        qDebug() << weatherDay.size();
    }
    {
        qDebug() << "start clear --- weatherDay";

        if (!weatherDay.isEmpty()) weatherDay.clear();
    }

    w.SetApiInfo(CITY, APIKEY, FORECASTS_HOUR[]);
    {
        w.GetWeatherHour(weatherHour);

        QMap<QTime, WeatherHour>::const_iterator it = weatherHour.constBegin();
        while (it != weatherHour.constEnd())
        {
            ui->textEdit->append("times       --- " +                 it.key  ().toString()     );
            ui->textEdit->append("date        --- " +                 it.value().date.toString());
            ui->textEdit->append("dayOfWeek   --- " +                 it.value().dayOfWeek      );
            ui->textEdit->append("isDayNight  --- " + QString::number(it.value().isDayNight    ));
            ui->textEdit->append("tenperature --- " + QString::number(it.value().temperature   ));
            ui->textEdit->append("weatherIcon --- " + QString::number(it.value().weatherIcon   ));
            ui->textEdit->append("iconPhrase  --- " +                 it.value().iconPhrase     );

            ui->textEdit->append("\n\n");

             ++it;
        }
        qDebug() << weatherHour.size();
    }
    {
        qDebug() << "start clear --- weatherHour";

        if (!weatherHour.isEmpty()) weatherHour.clear();
    }
}

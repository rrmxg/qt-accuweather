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

//const QString APIKEY = "";
//const QString CITY   = "";

void GUI::on_pushButton_show_clicked()
{
    qDebug() << "click --- on_pushButton_show_clicked";

    //    GetWeatherDay
    QVector<QDate> dates;
    QVector<int>   temperatureMinimum;
    QVector<int>   temperatureMaximum;
    QVector<int>   dayIconNumber;
    QStringList    dayIconNumberPhrase;
    QVector<int>   nigntIconNumber;
    QStringList    nightIconNumberPhrase;

    //    GetWeatherHour
    QVector<QTime> times;
    //    QVector<QDate> dates;
    QVector<bool>  isDayNight;
    QVector<int>   temperature;
    QVector<int>   iconNumber;
    QStringList    iconNumberPhrase;

    AccuWeather w;

    w.SetApiInfo(CITY, APIKEY, AccuWeatherAPI::FORECASTS_DAY[]);
    {
        w.GetWeatherDay(dates,
                        temperatureMinimum,
                        temperatureMaximum,
                        dayIconNumber,
                        dayIconNumberPhrase,
                        nigntIconNumber,
                        nightIconNumberPhrase);

        for (int i = 0; i < dates.size(); i++)
        {
            ui->textEdit->append("date            --- " +                 dates                [i].toString());
            ui->textEdit->append("temperatureMin  --- " + QString::number(temperatureMinimum   [i]          ));
            ui->textEdit->append("temperatureMax  --- " + QString::number(temperatureMaximum   [i]          ));
            ui->textEdit->append("iconDay         --- " + QString::number(dayIconNumber        [i]          ));
            ui->textEdit->append("iconPhraseDay   --- " +                 dayIconNumberPhrase  [i]           );
            ui->textEdit->append("iconNight       --- " + QString::number(nigntIconNumber      [i]          ));
            ui->textEdit->append("iconPhraseNight --- " +                 nightIconNumberPhrase[i]           );

            ui->textEdit->append("\n\n");
        }
        qDebug() << dates.size();
    }
    {
        qDebug() << "start clear";

        if (!dates                .isEmpty()) dates                .clear();
        if (!temperatureMinimum   .isEmpty()) temperatureMinimum   .clear();
        if (!temperatureMaximum   .isEmpty()) temperatureMaximum   .clear();
        if (!dayIconNumber        .isEmpty()) dayIconNumber        .clear();
        if (!dayIconNumberPhrase  .isEmpty()) dayIconNumberPhrase  .clear();
        if (!nigntIconNumber      .isEmpty()) nigntIconNumber      .clear();
        if (!nightIconNumberPhrase.isEmpty()) nightIconNumberPhrase.clear();
        if (!times                .isEmpty()) times                .clear();
        if (!isDayNight           .isEmpty()) isDayNight           .clear();
        if (!temperature          .isEmpty()) temperature          .clear();
        if (!iconNumber           .isEmpty()) iconNumber           .clear();
        if (!iconNumberPhrase     .isEmpty()) iconNumberPhrase     .clear();
    }

    w.SetApiInfo(CITY, APIKEY, AccuWeatherAPI::FORECASTS_HOUR[]);
    {
        w.GetWeatherHour(times,
                         dates,
                         isDayNight,
                         temperature,
                         iconNumber,
                         iconNumberPhrase);

        for (int i = 0; i < dates.size(); i++)
        {
            ui->textEdit->append("times            --- " +                 times           [i].toString());
            ui->textEdit->append("date             --- " +                 dates           [i].toString());
            ui->textEdit->append("isDayNight       --- " + QString::number(isDayNight      [i]          ));
            ui->textEdit->append("tenperature      --- " + QString::number(temperature     [i]          ));
            ui->textEdit->append("iconNumber       --- " + QString::number(iconNumber      [i]          ));
            ui->textEdit->append("iconNumberPhrase --- " +                 iconNumberPhrase[i]           );

            ui->textEdit->append("\n\n");
        }
        qDebug() << dates.size();
    }
    {
        qDebug() << "start clear";

        if (!dates                .isEmpty()) dates                .clear();
        if (!temperatureMinimum   .isEmpty()) temperatureMinimum   .clear();
        if (!temperatureMaximum   .isEmpty()) temperatureMaximum   .clear();
        if (!dayIconNumber        .isEmpty()) dayIconNumber        .clear();
        if (!dayIconNumberPhrase  .isEmpty()) dayIconNumberPhrase  .clear();
        if (!nigntIconNumber      .isEmpty()) nigntIconNumber      .clear();
        if (!nightIconNumberPhrase.isEmpty()) nightIconNumberPhrase.clear();
        if (!times                .isEmpty()) times                .clear();
        if (!isDayNight           .isEmpty()) isDayNight           .clear();
        if (!temperature          .isEmpty()) temperature          .clear();
        if (!iconNumber           .isEmpty()) iconNumber           .clear();
        if (!iconNumberPhrase     .isEmpty()) iconNumberPhrase     .clear();
    }
}

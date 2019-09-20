///////////////////////////////////////////////////////////////////////////////
#include "accuweather.h"
///////////////////////////////////////////////////////////////////////////////
#include <QDebug>
///////////////////////////////////////////////////////////////////////////////
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QEventLoop>
///////////////////////////////////////////////////////////////////////////////
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
///////////////////////////////////////////////////////////////////////////////
bool AccuWeather::getForecast(const QString forecastType,
                                    QMap<QDate, WeatherDay> &weatherDays)
{
    if (aw_locationKey == 0)
    {
        qDebug() << "error --- aw_locationKey = 0";
        return false;
    }
    {
        QString url
                = "http://dataservice.accuweather.com/forecasts/v1/daily/"
                + forecastType
                + "/"
                + QString::number(aw_locationKey)
                + "?apikey="
                + aw_apiKey;

        getData(url);

        if (url == "error")
        {
            qDebug() << "error --- getForecast <Days>";
            return false;
        }
    }
    {
        QJsonObject obj = doc.object();
        QJsonArray  arr = obj.value("DailyForecasts").toArray();

        for (const QJsonValue value : arr)
        {
            WeatherDay weatherDay;

            getDateTime(value.toObject().value("Date").toString());

            weatherDay.dayOfWeek       = QLocale().dayName(aw_date.dayOfWeek());
            weatherDay.temperatureMinF = value.toObject().value("Temperature")
                                              .toObject().value("Minimum")
                                              .toObject().value("Value").toInt();
            weatherDay.temperatureMinC = fToC(weatherDay.temperatureMinF);
            weatherDay.temperatureMaxF = value.toObject().value("Temperature")
                                              .toObject().value("Maximum")
                                              .toObject().value("Value").toInt();
            weatherDay.temperatureMaxC = fToC(weatherDay.temperatureMaxF);
            weatherDay.iconDayNo       = value.toObject().value("Day")
                                              .toObject().value("Icon").toInt();
            weatherDay.iconPhraseDay   = value.toObject().value("Day")
                                              .toObject().value("IconPhrase").toString();
            weatherDay.iconNightNo     = value.toObject().value("Night")
                                              .toObject().value("Icon").toInt();
            weatherDay.iconPhraseNight = value.toObject().value("Night")
                                              .toObject().value("IconPhrase").toString();

            weatherDays[aw_date] = weatherDay;
        }
    }
    return true;
}

bool AccuWeather::getForecast(const QString forecastType,
                                    QMap<QTime, WeatherHour> &weatherHours)
{
    if (aw_locationKey == 0)
    {
        qDebug() << "error --- aw_locationKey = 0";
        return false;
    }
    {
        QString url
                = "http://dataservice.accuweather.com/forecasts/v1/hourly/"
                + forecastType
                + "/"
                + QString::number(aw_locationKey)
                + "?apikey="
                + aw_apiKey;

        getData(url);

        if (url == "error")
        {
            qDebug() << "error --- getForecast <Hours>";
            return false;
        }
    }
    {
        QJsonArray arr = doc.array();

        for (const QJsonValue value : arr)
        {
            WeatherHour weatherHour;

            getDateTime(value.toObject().value("DateTime").toString());

            weatherHour.date         = aw_date;
            weatherHour.dayOfWeek    = QLocale().dayName(aw_date.dayOfWeek());
            weatherHour.iconNo       = value.toObject().value("WeatherIcon").toInt();
            weatherHour.iconPhrase   = value.toObject().value("IconPhrase").toString();
            weatherHour.isDayNight   = value.toObject().value("IsDaylight").toBool();
            weatherHour.temperatureF = value.toObject().value("Temperature")
                                            .toObject().value("Value").toInt();
            weatherHour.temperatureC = fToC(weatherHour.temperatureF);

            weatherHours[aw_time] = weatherHour;
        }
    }
    return true;
}

bool AccuWeather::getLocationKey(const QString cityName)
{
    {
        aw_locationKey = 0;

        QString url
                = "http://dataservice.accuweather.com/locations/v1/cities/autocomplete?apikey="
                + aw_apiKey
                + "&q="
                + cityName;

        getData(url);

        if (url == "error")
        {
            qDebug() << "error --- getLocationKey";
            return false;
        }
    }
    {
        QJsonArray arr = doc.array();
        {
            dialog = new QDialog();

            dialog->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
            dialog->setWindowTitle(cityName);

            QVBoxLayout *verticalLayout = new QVBoxLayout(dialog);
            dialog->setLayout(verticalLayout);

            QLabel *label = new QLabel(cityName, dialog);
            {
                label->setFixedHeight(20);
                label->setAlignment(Qt::AlignHCenter);
            }
            verticalLayout->addWidget(label);

            for (const QJsonValue value : arr)
            {
                QString key     = value.toObject().value("Key").toString();
                QString country = value.toObject().value("Country")
                                       .toObject().value("LocalizedName").toString();
                QString administrativeArea
                                = value.toObject().value("AdministrativeArea")
                                       .toObject().value("LocalizedName").toString();

                aw_countries[country + "(" + administrativeArea + ")"] = key.toInt();
                {
                    QPushButton *button = new QPushButton(dialog);
                    {
                        button->setText(country + "(" + administrativeArea + ")");
                        connect(button, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
                    }
                    verticalLayout->addWidget(button);
                }
            }
            dialog->exec();
            dialog->deleteLater();
        }
    }
    return true;
}

void AccuWeather::on_pushButton_clicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());

    aw_locationKey = aw_countries.find(button->text()).value();
    button->deleteLater();

    aw_countries.clear();

    dialog->close();
}

void AccuWeather::getData(QString &url)
{
    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
        url = "error";
    else
        doc = QJsonDocument::fromJson(reply->readAll());

    reply->deleteLater();
}

void AccuWeather::getDateTime(const QString s)
{
    // yyyy-mm-ddThh:mm:ss+hh:mm;

    aw_date = QDate::fromString(s.left(10), "yyyy-MM-dd");
    aw_time = QTime::fromString(s.mid(11, 8), "HH:mm:ss");
}

int AccuWeather::fToC(const int t)
{
    return (t - 32) * 5 / 9;
}

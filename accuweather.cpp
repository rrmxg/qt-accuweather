#include "accuweather.h"

void AccuWeather::getData(QMap<QDate, WeatherDay> &_weatherDays)
{
    getLocationKey();

    QString url
            = "http://dataservice.accuweather.com/forecasts/v1/daily/"
            + aw_forecastType
            + "/"
            + QString::number(aw_locationKey)
            + "?apikey="
            + aw_apiKey;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error getData <Day>";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject   obj = doc.object();
        QJsonArray    arr = obj.value("DailyForecasts").toArray();

        for (const QJsonValue value : arr)
        {
            WeatherDay weatherDay;

            getDateTime(value.toObject().value("Date").toString());

            weatherDay.dayOfWeek       = QLocale().dayName(aw_date.dayOfWeek());
            weatherDay.temperatureMin  = value.toObject().value("Temperature")
                                              .toObject().value("Minimum")
                                              .toObject().value("Value").toInt();
            weatherDay.temperatureMax  = value.toObject().value("Temperature")
                                              .toObject().value("Maximum")
                                              .toObject().value("Value").toInt();
            weatherDay.iconDayNo       = value.toObject().value("Day")
                                              .toObject().value("Icon").toInt();
            weatherDay.iconPhraseDay   = value.toObject().value("Day")
                                              .toObject().value("IconPhrase").toString();
            weatherDay.iconNightNo     = value.toObject().value("Night")
                                              .toObject().value("Icon").toInt();
            weatherDay.iconPhraseNight = value.toObject().value("Night")
                                              .toObject().value("IconPhrase").toString();

            _weatherDays[aw_date] = weatherDay;
        }
    }
    reply->deleteLater();
}


void AccuWeather::getData(QMap<QTime, WeatherHour> &_weatherHours)
{
    getLocationKey();

    QString url
            = "http://dataservice.accuweather.com/forecasts/v1/hourly/"
            + aw_forecastType
            + "/"
            + QString::number(aw_locationKey)
            + "?apikey="
            + aw_apiKey;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error getData <Hour>";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray    arr = doc.array();

        for (const QJsonValue value : arr)
        {
            WeatherHour weatherHour;

            getDateTime(value.toObject().value("DateTime").toString());

            weatherHour.date        = aw_date;
            weatherHour.dayOfWeek   = QLocale().dayName(aw_date.dayOfWeek());
            weatherHour.iconNo      = value.toObject().value("WeatherIcon").toInt();
            weatherHour.iconPhrase  = value.toObject().value("IconPhrase").toString();
            weatherHour.isDayNight  = value.toObject().value("IsDaylight").toBool();
            weatherHour.temperature = value.toObject().value("Temperature")
                                              .toObject().value("Value").toInt();

            _weatherHours[aw_time] = weatherHour;
        }
    }
    reply->deleteLater();
}


void AccuWeather::getLocationKey()
{
    QString url
            =  "http://dataservice.accuweather.com/locations/v1/cities/autocomplete?apikey="
            + aw_apiKey
            + "&q="
            + aw_city;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error getLocationKey";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray    arr = doc.array();

        for (const QJsonValue value : arr)
        {
            QString key     = value.toObject().value("Key").toString();
            QString country = value.toObject().value("Country")
                                   .toObject().value("LocalizedName").toString();
            QString administrativeArea
                            = value.toObject().value("AdministrativeArea")
                                   .toObject().value("LocalizedName").toString();

            aw_countries[country + "(" + administrativeArea + ")"] = key.toInt();
        }
        {
            SelectCountry *selectCountry = new SelectCountry;

            selectCountry->setWindowTitle(aw_city);
            selectCountry->instButtons(aw_countries, aw_city);

            connect(selectCountry, SIGNAL(sendButtonText(const QString)), this, SLOT(getButtonText(const QString)));

            selectCountry->exec();

            delete selectCountry;
        }
    }
    reply->deleteLater();
}



void AccuWeather::getButtonText(const QString _s)
{
    aw_locationKey = aw_countries.find(_s).value();
    aw_countries.clear();
}

void AccuWeather::getDateTime(const QString _date)
{
    // yyyy-mm-ddThh:mm:ss+hh:mm;

    QString d{};
    for (int i =  0; i < 10; i++)
        d += _date[i];

    aw_date = QDate::fromString(d, "yyyy-MM-dd");

    QString t{};
    for (int i = 11; i < 19; i++)
        t += _date[i];

    aw_time = QTime::fromString(t, "HH:mm:ss");
}

#ifndef ACCUWEATHER_WEATHER_H
#define ACCUWEATHER_WEATHER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QVariant>
#include <QObject>

#include <QDebug>

#include "selectcountry.h"

const QString ACCUWEATHER = "AccuWeather";

const QStringList FORECASTS_DAYS =
{
    "1day",    // 0
    "5day",    // 1
    "10day",   // 2 -
    "15day"    // 3 -
};

const QStringList FORECASTS_HOURS =
{
    "1hour",   // 0
    "12hour",  // 1
    "24hour",  // 2 -
    "72hour",  // 3 -
    "120hour"  // 4 -
};


struct WeatherHour
{
    QDate   date       ;
    QString dayOfWeek  ;
    int     iconNo     ;
    QString iconPhrase ;
    bool    isDayNight ;
    int     temperature;
};

struct WeatherDay
{
    QString dayOfWeek      ;
    int     temperatureMin ;
    int     temperatureMax ;
    int     iconDayNo      ;
    QString iconPhraseDay  ;
    int     iconNightNo    ;
    QString iconPhraseNight;
};


class AccuWeather : public QObject
{
    Q_OBJECT

public:
    AccuWeather() {}

    AccuWeather(const QString _apiKey) :
        aw_apiKey(_apiKey) {}

    AccuWeather(const QString _apiKey,
                const QString _forecastType) :
        aw_apiKey      (_apiKey),
        aw_forecastType(_forecastType) {}

    AccuWeather(const QString _city,
                const QString _apiKey,
                const QString _forecastType) :
        aw_city        (_city),
        aw_apiKey      (_apiKey),
        aw_forecastType(_forecastType) {}

    ~AccuWeather() {}

    void setCity        (const QString _city)         { aw_city         = _city;         }
    void setApiKey      (const QString _apiKey)       { aw_apiKey       = _apiKey;       }
    void setForecastType(const QString _forecastType) { aw_forecastType = _forecastType; }

    void setData(const QString _city,
                 const QString _apiKey,
                 const QString _forecastType)
    {
        aw_city         = _city;
        aw_apiKey       = _apiKey;
        aw_forecastType = _forecastType;
    }


    void getData(QMap<QDate, WeatherDay> &_weatherDays);

    void getData(const QString _city,
                       QMap<QDate, WeatherDay> &_weatherDays)
    {
        aw_city = _city;

        getData(_weatherDays);
    }

    void getData(const QString _city,
                 const QString _forecastType,
                       QMap<QDate, WeatherDay> &_weatherDays)
    {
        aw_city         = _city;
        aw_forecastType = _forecastType;

        getData(_weatherDays);
    }

    void getData(const QString _city,
                 const QString _apiKey,
                 const QString _forecastType,
                       QMap<QDate, WeatherDay> &_weatherDays)
    {
        aw_city         = _city;
        aw_apiKey       = _apiKey;
        aw_forecastType = _forecastType;

        getData(_weatherDays);
    }



    void getData(QMap<QTime, WeatherHour> &_weatherHours);

    void getData(const QString _city,
                       QMap<QTime, WeatherHour> &_weatherHours)
    {
        aw_city = _city;

        getData(_weatherHours);
    }

    void getData(const QString _city,
                 const QString _forecastType,
                       QMap<QTime, WeatherHour> &weatherHours)
    {
        aw_city         = _city;
        aw_forecastType = _forecastType;

        getData(weatherHours);
    }

    void getData(const QString _city,
                 const QString _apiKey,
                 const QString _forecastType,
                       QMap<QTime, WeatherHour> &_weatherHours)
    {
        aw_city         = _city;
        aw_apiKey       = _apiKey;
        aw_forecastType = _forecastType;

        getData(_weatherHours);
    }

public slots:
    void getButtonText(const QString);

private:
    QString aw_city        {};
    QString aw_apiKey      {};
    QString aw_forecastType{};

    int aw_locationKey{};

    QMap<QString, int> aw_countries{};

    QDate aw_date{};
    QTime aw_time{};

    void getLocationKey();                   // LocationsAPI -> AutocompleteSearch
    void getDateTime   (const QString _date);
};

#endif // ACCUWEATHER_WEATHER_H

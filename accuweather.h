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
    QDate   date        ;
    QString dayOfWeek   ;
    int     iconNo      ;
    QString iconPhrase  ;
    bool    isDayNight  ;
    int     temperatureF;
    int     temperatureC;
};

struct WeatherDay
{
    QString dayOfWeek      ;
    int     temperatureMinF;
    int     temperatureMaxF;
    int     temperatureMinC;
    int     temperatureMaxC;
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

    AccuWeather(const QString apiKey) :
        aw_apiKey(apiKey) {}

    AccuWeather(const QString apiKey,
                const QString forecastType) :
        aw_apiKey      (apiKey),
        aw_forecastType(forecastType) {}

    AccuWeather(const QString city,
                const QString apiKey,
                const QString forecastType) :
        aw_city        (city),
        aw_apiKey      (apiKey),
        aw_forecastType(forecastType) {}

    ~AccuWeather() {}

    void setCity        (const QString city)         { aw_city         = city;         }
    void setApiKey      (const QString apiKey)       { aw_apiKey       = apiKey;       }
    void setForecastType(const QString forecastType) { aw_forecastType = forecastType; }

    void setData(const QString city,
                 const QString apiKey,
                 const QString forecastType)
    {
        aw_city         = city;
        aw_apiKey       = apiKey;
        aw_forecastType = forecastType;
    }


    void getData(QMap<QDate, WeatherDay> &weatherDays);

    void getData(const QString city,
                       QMap<QDate, WeatherDay> &weatherDays)
    {
        aw_city = city;

        getData(weatherDays);
    }

    void getData(const QString city,
                 const QString forecastType,
                       QMap<QDate, WeatherDay> &weatherDays)
    {
        aw_city         = city;
        aw_forecastType = forecastType;

        getData(weatherDays);
    }

    void getData(const QString city,
                 const QString apiKey,
                 const QString forecastType,
                       QMap<QDate, WeatherDay> &weatherDays)
    {
        aw_city         = city;
        aw_apiKey       = apiKey;
        aw_forecastType = forecastType;

        getData(weatherDays);
    }



    void getData(QMap<QTime, WeatherHour> &weatherHours);

    void getData(const QString city,
                       QMap<QTime, WeatherHour> &weatherHours)
    {
        aw_city = city;

        getData(weatherHours);
    }

    void getData(const QString city,
                 const QString forecastType,
                       QMap<QTime, WeatherHour> &weatherHours)
    {
        aw_city         = city;
        aw_forecastType = forecastType;

        getData(weatherHours);
    }

    void getData(const QString city,
                 const QString apiKey,
                 const QString forecastType,
                       QMap<QTime, WeatherHour> &weatherHours)
    {
        aw_city         = city;
        aw_apiKey       = apiKey;
        aw_forecastType = forecastType;

        getData(weatherHours);
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
    void getDateTime   (const QString);

    int fToC(const int t); // Fahrenheit to Celsius
};

#endif // ACCUWEATHER_WEATHER_H

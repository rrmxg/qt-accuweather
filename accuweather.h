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

const QStringList FORECASTS_DAY =
{
    "1day",    // 0
    "5day",    // 1
    "10day",   // 2
    "15day"    // 3
};

const QStringList FORECASTS_HOUR =
{
    "1hour",   // 0
    "12hour",  // 1
    "24hour",  // 2
    "72hour",  // 3
    "120hour"  // 4
};


struct WeatherHour
{
    QDate   date       ;
    QString dayOfWeek  ;
    int     weatherIcon;
    QString iconPhrase ;
    bool    isDayNight ;
    int     temperature;
};

struct WeatherDay
{
    QString dayOfWeek      ;
    int     temperatureMin ;
    int     temperatureMax ;
    int     iconDay        ;
    QString iconPhraseDay  ;
    int     iconNight      ;
    QString iconPhraseNight;
};


class AccuWeather : public QObject
{
    Q_OBJECT

public:
    AccuWeather() {}

    AccuWeather(const QString ApiKey) :
        apiKey(ApiKey) {}

    AccuWeather(const QString ApiKey,
                const QString ForecastType) :
        apiKey      (ApiKey),
        forecastType(ForecastType) {}

    AccuWeather(const QString City,
                const QString ApiKey,
                const QString ForecastType) :
        city        (City),
        apiKey      (ApiKey),
        forecastType(ForecastType) {}

    ~AccuWeather() {}

    void SetCity        (const QString City)         { city         = City;         }
    void SetApiKey      (const QString ApiKey)       { apiKey       = ApiKey;       }
    void SetForecastType(const QString ForecastType) { forecastType = ForecastType; }

    void SetApiInfo(const QString City,
                    const QString ApiKey,
                    const QString ForecastType)
    {
        city         = City;
        apiKey       = ApiKey;
        forecastType = ForecastType;
    }


    void GetWeatherDay(QMap<QDate, WeatherDay> &weatherDay);

    void GetWeatherDay(const QString City,
                             QMap<QDate, WeatherDay> &weatherDay)
    {
        city = City;

        GetWeatherDay(weatherDay);
    }

    void GetWeatherDay(const QString City,
                       const QString ForecastType,
                             QMap<QDate, WeatherDay> &weatherDay)
    {
        city         = City;
        forecastType = ForecastType;

        GetWeatherDay(weatherDay);
    }

    void GetWeatherDay(const QString City,
                       const QString ApiKey,
                       const QString ForecastType,
                             QMap<QDate, WeatherDay> &weatherDay)
    {
        city         = City;
        apiKey       = ApiKey;
        forecastType = ForecastType;

        GetWeatherDay(weatherDay);
    }



    void GetWeatherHour(QMap<QTime, WeatherHour> &weatherHour);

    void GetWeatherHour(const QString City,
                              QMap<QTime, WeatherHour> &weatherHour)
    {
        city = City;

        GetWeatherHour(weatherHour);
    }

    void GetWeatherHour(const QString City,
                        const QString ForecastType,
                              QMap<QTime, WeatherHour> &weatherHour)
    {
        city         = City;
        forecastType = ForecastType;

        GetWeatherHour(weatherHour);
    }

    void GetWeatherHour(const QString City,
                        const QString ApiKey,
                        const QString ForecastType,
                              QMap<QTime, WeatherHour> &weatherHour)
    {
        city         = City;
        apiKey       = ApiKey;
        forecastType = ForecastType;

        GetWeatherHour(weatherHour);
    }

public slots:
    void GetNumber(QString);

private:
    QString city;
    QString apiKey;
    QString forecastType;

    int key;

    QMap<QString, int> countries;

    void LocationsAPI_AutocompleteSearch();

    QDate date;
    QTime time;

    void GetDate(const QString d);

    SelectCountry *selectCountry;
};

#endif // ACCUWEATHER_WEATHER_H

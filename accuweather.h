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


    void GetWeatherDay(QVector<QDate> &dates,
                       QVector<int>   &temperatureMinimum,
                       QVector<int>   &temperatureMaximum,
                       QVector<int>   &dayIconNumber,
                       QStringList    &dayIconNumberPhrase,
                       QVector<int>   &nigntIconNumber,
                       QStringList    &nightIconNumberPhrase);

    void GetWeatherDay(const QString         City,
                             QVector<QDate> &dates,
                             QVector<int>   &temperatureMinimum,
                             QVector<int>   &temperatureMaximum,
                             QVector<int>   &dayIconNumber,
                             QStringList    &dayIconNumberPhrase,
                             QVector<int>   &nigntIconNumber,
                             QStringList    &nightIconNumberPhrase)
    {
        city = City;

        GetWeatherDay(dates,
                      temperatureMinimum,
                      temperatureMaximum,
                      dayIconNumber,
                      dayIconNumberPhrase,
                      nigntIconNumber,
                      nightIconNumberPhrase);
    }

    void GetWeatherDay(const QString         City,
                       const QString         ForecastType,
                             QVector<QDate> &dates,
                             QVector<int>   &temperatureMinimum,
                             QVector<int>   &temperatureMaximum,
                             QVector<int>   &dayIconNumber,
                             QStringList    &dayIconNumberPhrase,
                             QVector<int>   &nigntIconNumber,
                             QStringList    &nightIconNumberPhrase)
    {
        city         = City;
        forecastType = ForecastType;

        GetWeatherDay(dates,
                      temperatureMinimum,
                      temperatureMaximum,
                      dayIconNumber,
                      dayIconNumberPhrase,
                      nigntIconNumber,
                      nightIconNumberPhrase);
    }

    void GetWeatherDay(const QString         City,
                       const QString         ApiKey,
                       const QString         ForecastType,
                             QVector<QDate> &dates,
                             QVector<int>   &temperatureMinimum,
                             QVector<int>   &temperatureMaximum,
                             QVector<int>   &dayIconNumber,
                             QStringList    &dayIconNumberPhrase,
                             QVector<int>   &nigntIconNumber,
                             QStringList    &nightIconNumberPhrase)
    {
        city         = City;
        apiKey       = ApiKey;
        forecastType = ForecastType;

        GetWeatherDay(dates,
                      temperatureMinimum,
                      temperatureMaximum,
                      dayIconNumber,
                      dayIconNumberPhrase,
                      nigntIconNumber,
                      nightIconNumberPhrase);
    }



    void GetWeatherHour(QVector<QTime> &times,
                        QVector<QDate> &dates,
                        QVector<bool>  &isDayNight,
                        QVector<int>   &temperature,
                        QVector<int>   &weatherNumber,
                        QStringList    &iconNumberPhrase);

    void GetWeatherHour(const QString         City,
                              QVector<QTime> &times,
                              QVector<QDate> &dates,
                              QVector<bool>  &isDayNight,
                              QVector<int>   &temperature,
                              QVector<int>   &weatherNumber,
                              QStringList    &iconNumberPhrase)
    {
        city = City;

        GetWeatherHour(times,
                       dates,
                       isDayNight,
                       temperature,
                       weatherNumber,
                       iconNumberPhrase);
    }

    void GetWeatherHour(const QString         City,
                        const QString         ForecastType,
                              QVector<QTime> &times,
                              QVector<QDate> &dates,
                              QVector<bool>  &isDayNight,
                              QVector<int>   &temperature,
                              QVector<int>   &weatherNumber,
                              QStringList    &iconNumberPhrase)
    {
        city         = City;
        forecastType = ForecastType;

        GetWeatherHour(times,
                       dates,
                       isDayNight,
                       temperature,
                       weatherNumber,
                       iconNumberPhrase);
    }

    void GetWeatherHour(const QString         City,
                        const QString         ApiKey,
                        const QString         ForecastType,
                              QVector<QTime> &times,
                              QVector<QDate> &dates,
                              QVector<bool>  &isDayNight,
                              QVector<int>   &temperature,
                              QVector<int>   &weatherNumber,
                              QStringList    &iconNumberPhrase)
    {
        city         = City;
        apiKey       = ApiKey;
        forecastType = ForecastType;

        GetWeatherHour(times,
                       dates,
                       isDayNight,
                       temperature,
                       weatherNumber,
                       iconNumberPhrase);
    }

public slots:
    void GetNumber(QString);

private:
    QString city;
    QString apiKey;
    QString forecastType;

    int key;

    QMap<QString, int> map;

    void LocationsAPI_AutocompleteSearch();

    QDate date;
    QTime time;

    void GetDate(const QString d);

    SelectCountry selectCountry;
};

#endif // ACCUWEATHER_WEATHER_H

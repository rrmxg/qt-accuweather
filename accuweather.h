#ifndef ACCUWEATHER_WEATHER_H
#define ACCUWEATHER_WEATHER_H

#include <QJsonDocument>
#include <QDate>
#include <QObject>
#include <QDialog>
#include <QMap>

///////////////////////////////////////////////////////////////////////////////
const QString ACCUWEATHER = "AccuWeather";
///////////////////////////////////////////////////////////////////////////////

/// = "1day",
///   "5day",
///   "10day",
///   "15day"
const QStringList FORECASTS_DAYS =
{
    "1day",    // 0
    "5day",    // 1
    "10day",   // 2 -
    "15day"    // 3 -
};
///////////////////////////////////////////////////////////////////////////////

/// = "1hour",
///   "12hour",
///   "24hour",
///   "72hour",
///   "120hour"
const QStringList FORECASTS_HOURS =
{
    "1hour",   // 0
    "12hour",  // 1
    "24hour",  // 2 -
    "72hour",  // 3 -
    "120hour"  // 4 -
};
///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
class AccuWeather : public QObject
{
    Q_OBJECT

public:
    AccuWeather(const QString apiKey) : aw_apiKey(apiKey) {}
    ~AccuWeather() {}

    bool getForecast(const QString forecastType,
                           QMap<QDate, WeatherDay> &weatherDays);

    bool getForecast(const QString forecastType,
                           QMap<QTime, WeatherHour> &weatherHour);

    bool getLocationKey(const QString cityName);  // LocationsAPI -> AutocompleteSearch

private slots:
    void on_pushButton_clicked();

private:
    void getData       (      QString&);
    void getDateTime   (const QString );

    int fToC(const int t); // Fahrenheit to Celsius

    QDialog *dialog;

    QJsonDocument doc;

    QString aw_apiKey{};

    int aw_locationKey{};

    QDate aw_date{};
    QTime aw_time{};

    QMap<QString, int> aw_countries{};
};

#endif // ACCUWEATHER_WEATHER_H

#include "accuweather.h"

void AccuWeather::GetWeatherDay(QMap<QDate, WeatherDay> &weatherDay)
{
    LocationsAPI_AutocompleteSearch();

    QString url
            = "http://dataservice.accuweather.com/forecasts/v1/daily/"
            + forecastType
            + "/"
            + QString::number(key)
            + "?apikey="
            + apiKey;

    qDebug() << "url --- GetWeatherDay --- " << url;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error --- GetWeatherDay";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject   obj = doc.object();
        QJsonArray    arr = obj.value("DailyForecasts").toArray();

        for (const QJsonValue value : arr)
        {
            WeatherDay wd;

            GetDate(value.toObject().value("Date").toString());

            wd.dayOfWeek       = QLocale().dayName(date.dayOfWeek());
            wd.temperatureMin  = value.toObject().value("Temperature").toObject().value("Minimum").toObject().value("Value").toInt();
            wd.temperatureMax  = value.toObject().value("Temperature").toObject().value("Maximum").toObject().value("Value").toInt();
            wd.iconDay         = value.toObject().value("Day").toObject().value("Icon").toInt();
            wd.iconPhraseDay   = value.toObject().value("Day").toObject().value("IconPhrase").toString();
            wd.iconNight       = value.toObject().value("Night").toObject().value("Icon").toInt();
            wd.iconPhraseNight = value.toObject().value("Night").toObject().value("IconPhrase").toString();

            qDebug() << "date            --- " << date.toString()   ;
            qDebug() << "dateOfWeek      --- " << wd.dayOfWeek      ;
            qDebug() << "temperatureMin  --- " << wd.temperatureMin ;
            qDebug() << "temperatureMax  --- " << wd.temperatureMax ;
            qDebug() << "iconDay         --- " << wd.iconDay        ;
            qDebug() << "iconPhraseDay   --- " << wd.iconPhraseDay  ;
            qDebug() << "iconNight       --- " << wd.iconNight      ;
            qDebug() << "iconPhraseNight --- " << wd.iconPhraseNight;

            weatherDay[date] = wd;
        }
    }
    reply->deleteLater();
}


void AccuWeather::GetWeatherHour(QMap<QTime, WeatherHour> &weatherHour)
{
    LocationsAPI_AutocompleteSearch();

    QString url
            = "http://dataservice.accuweather.com/forecasts/v1/hourly/"
            + forecastType
            + "/"
            + QString::number(key)
            + "?apikey="
            + apiKey;

    qDebug() << "url --- GetWeatherHour --- " << url;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error --- GetWeatherHour";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray    arr = doc.array();

        for (const QJsonValue value : arr)
        {
            WeatherHour wh;

            GetDate(value.toObject().value("DateTime").toString());

            wh.date        = date;
            wh.dayOfWeek   = QLocale().dayName(date.dayOfWeek());
            wh.weatherIcon = value.toObject().value("WeatherIcon").toInt();
            wh.iconPhrase  = value.toObject().value("IconPhrase").toString();
            wh.isDayNight  = value.toObject().value("IsDaylight").toBool();
            wh.temperature = value.toObject().value("Temperature").toObject().value("Value").toInt();

            qDebug() << "time        --- " << time.toString();
            qDebug() << "date        --- " << wh.date        ;
            qDebug() << "dateOfWeek  --- " << wh.dayOfWeek   ;
            qDebug() << "weatherIcon --- " << wh.weatherIcon ;
            qDebug() << "iconPhrase  --- " << wh.iconPhrase  ;
            qDebug() << "isDayNight  --- " << wh.isDayNight  ;
            qDebug() << "temperature --- " << wh.temperature ;

            weatherHour[time] = wh;
        }
    }
    reply->deleteLater();
}


void AccuWeather::LocationsAPI_AutocompleteSearch()
{
    QString url
            =  "http://dataservice.accuweather.com/locations/v1/cities/autocomplete?apikey="
            + apiKey
            + "&q="
            + city;

    qDebug() << "url --- LocationsAPI_AutocompleteSearch --- " << url;

    QNetworkAccessManager networkAccessManager;
    QEventLoop            eventLoop;

    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkReply *reply = networkAccessManager.get(QNetworkRequest(QUrl(url)));

    eventLoop.exec();

    if (reply->error())
    {
        qDebug() << "error --- LocationsAPI_AutocompleteSearch";
    }
    else
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonArray    arr = doc.array();

        for (const QJsonValue value : arr)
        {
            QString country = value.toObject().value("Country").toObject().value("LocalizedName").toString();
            QString administrativeArea
                            = value.toObject().value("AdministrativeArea").toObject().value("LocalizedName").toString();
            QString key     = value.toObject().value("Key").toString();

            countries[country + "(" + administrativeArea + ")"] = key.toInt();

            qDebug() << country + "(" + administrativeArea + ") = " << key;
        }
        {
            selectCountry = new SelectCountry;

            selectCountry->setWindowTitle(city);
            selectCountry->SetButton(countries, city);

            connect(selectCountry, SIGNAL(SendButton(QString)), this, SLOT(GetNumber(QString)));

            selectCountry->exec();

            delete selectCountry;
        }
    }
    reply->deleteLater();
}



void AccuWeather::GetNumber(QString s)
{
    key = countries.find(s).value();
    countries.clear();
    qDebug() << "point --- GetNumber --- " << key;
}

void AccuWeather::GetDate(const QString s)
{
    qDebug() << "point --- GetDate";
    // yyyy-mm-ddThh:mm:ss+hh:mm;

    QString d = "";
    for (int i =  0; i < 10; i++)
        d += s[i];

    date = QDate::fromString(d, "yyyy-MM-dd");

    QString t = "";
    for (int i = 11; i < 19; i++)
        t += s[i];

    time = QTime::fromString(t, "HH:mm:ss");
}

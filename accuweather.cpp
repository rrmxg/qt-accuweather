#include "accuweather.h"

/*

QVector<QDate> dates;
QVector<int>   temperatureMinimum;
QVector<int>   temperatureMaximum;
QVector<int>   dayIconNumber;
QStringList    dayIconNumberPhrase;
QVector<int>   nigntIconNumber;
QStringList    nightIconNumberPhrase;

dates,
temperatureMinimum,
temperatureMaximum,
dayIconNumber,
dayIconNumberPhrase,
nigntIconNumber,
nightIconNumberPhrase

*/
void AccuWeather::GetWeatherDay(QVector<QDate> &dates,
                                QVector<int>   &temperatureMinimum,
                                QVector<int>   &temperatureMaximum,
                                QVector<int>   &dayIconNumber,
                                QStringList    &dayIconNumberPhrase,
                                QVector<int>   &nigntIconNumber,
                                QStringList    &nightIconNumberPhrase)
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
            QString _date            = value.toObject().value("Date").toString();
            int     _temperatureMin  = value.toObject().value("Temperature").toObject().value("Minimum").toObject().value("Value").toInt();
            int     _temperatureMax  = value.toObject().value("Temperature").toObject().value("Maximum").toObject().value("Value").toInt();
            int     _iconDay         = value.toObject().value("Day").toObject().value("Icon").toInt();
            QString _iconPhraseDay   = value.toObject().value("Day").toObject().value("IconPhrase").toString();
            int     _iconNight       = value.toObject().value("Night").toObject().value("Icon").toInt();
            QString _iconPhraseNight = value.toObject().value("Night").toObject().value("IconPhrase").toString();

            qDebug() << "date            --- " << _date           ;
            qDebug() << "temperatureMin  --- " << _temperatureMin ;
            qDebug() << "temperatureMax  --- " << _temperatureMax ;
            qDebug() << "iconDay         --- " << _iconDay        ;
            qDebug() << "iconPhraseDay   --- " << _iconPhraseDay  ;
            qDebug() << "iconNight       --- " << _iconNight      ;
            qDebug() << "iconPhraseNight --- " << _iconPhraseNight;

            GetDate(_date);

            dates                .push_back(date            );
            temperatureMinimum   .push_back(_temperatureMin );
            temperatureMaximum   .push_back(_temperatureMax );
            dayIconNumber        .push_back(_iconDay        );
            dayIconNumberPhrase  .push_back(_iconPhraseDay  );
            nigntIconNumber      .push_back(_iconNight      );
            nightIconNumberPhrase.push_back(_iconPhraseNight);
        }
    }
    reply->deleteLater();
}


/*

QVector<QTime> times;
QVector<QDate> dates;
QVector<bool>  isDayNight;
QVector<int>   temperature;
QVector<int>   weatherNumber;
QStringList    iconNumberPhrase;

times,
dates,
isDayNight,
temperature,
weatherNumber,
iconNumberPhrase

*/
void AccuWeather::GetWeatherHour(QVector<QTime> &times,
                                 QVector<QDate> &dates,
                                 QVector<bool>  &isDayNight,
                                 QVector<int>   &temperature,
                                 QVector<int>   &weatherNumber,
                                 QStringList    &iconNumberPhrase)
{
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
            QString _date        = value.toObject().value("DateTime").toString();
            int     _weatherIcon = value.toObject().value("WeatherIcon").toInt();
            QString _iconPhrase  = value.toObject().value("IconPhrase").toString();
            bool    _isDayNight  = value.toObject().value("IsDaylight").toBool();
            int     _temperature = value.toObject().value("Temperature").toObject().value("Value").toInt();

            qDebug() << "date        --- " << _date       ;
            qDebug() << "weatherIcon --- " << _weatherIcon;
            qDebug() << "iconPhrase  --- " << _iconPhrase ;
            qDebug() << "isDayNight  --- " << _isDayNight ;
            qDebug() << "temperature --- " << _temperature;

            GetDate(_date);

            qDebug() << "point --- 1";

            times           .push_back(time        );
            dates           .push_back(date        );
            isDayNight      .push_back(_isDayNight );
            temperature     .push_back(_temperature);
            weatherNumber   .push_back(_weatherIcon);
            iconNumberPhrase.push_back(_iconPhrase );
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

            map[country + "(" + administrativeArea + ")"] = key.toInt();

            qDebug() << country + "(" + administrativeArea + ") = " << key;
        }
        {
            selectCountry.setWindowTitle(city);
            selectCountry.SetButton(map, city);

            connect(&selectCountry, SIGNAL(SendButton(QString)), this, SLOT(GetNumber(QString)));

            selectCountry.exec();
        }
    }
    reply->deleteLater();
}

void AccuWeather::GetNumber(QString s)
{
    key = map.find(s).value();
    qDebug() << "point --- GetNumber --- " << key;
}

void AccuWeather::GetDate(QString s)
{
    qDebug() << "point --- GetDate";
    // yyyy-mm-ddThh:mm:ss+hh:mm;

    QString d = "";
    for (int i =  0; i < 10; i++) d += s[i];
    date = QDate::fromString(d, "yyyy-MM-dd");

    QString t = "";
    for (int i = 11; i < 19; i++) t += s[i];
    time = QTime::fromString(t, "HH:mm:ss");
}

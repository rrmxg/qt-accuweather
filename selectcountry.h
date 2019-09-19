#ifndef SELECTCOUNTRY_H
#define SELECTCOUNTRY_H

#include <QDialog>

class SelectCountry : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCountry(QWidget *parent = nullptr);
    ~SelectCountry() {}

    void SetButton(const QMap<QString, int> countries, const QString cityName);

signals:
    void SendButton(QString);

public slots:
    void GetButton();

private:
};

#endif // SELECTCOUNTRY_H

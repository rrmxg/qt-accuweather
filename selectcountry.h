#ifndef SELECTCOUNTRY_H
#define SELECTCOUNTRY_H

#include <QDialog>

class SelectCountry : public QDialog
{
    Q_OBJECT

signals:
    void sendButtonText(const QString);

public:
    explicit SelectCountry(QWidget *parent = nullptr);
    ~SelectCountry() {}

    void instButtons(const QMap<QString, int> countries,
                     const QString            cityName);

private slots:
    void on_pushButton_clicked();

private:
};

#endif // SELECTCOUNTRY_H

#ifndef SELECTCOUNTRY_H
#define SELECTCOUNTRY_H

#include <QDialog>

namespace Ui
{
class SelectCountry;
}

class SelectCountry : public QDialog
{
    Q_OBJECT

public:
    explicit SelectCountry(QWidget *parent = nullptr);
    ~SelectCountry();

    void SetButton(const QMap<QString, int> map, const QString cityName);

signals:
    void SendButton(QString);

public slots:
    void GetButton();

private:
    Ui::SelectCountry *ui;
};

#endif // SELECTCOUNTRY_H

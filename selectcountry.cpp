#include "selectcountry.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <QDebug>

SelectCountry::SelectCountry(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::FramelessWindowHint) { }


void SelectCountry::SetButton(const QMap<QString, int> countries, const QString cityName)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    setLayout(verticalLayout);

    QLabel *label = new QLabel(cityName, this);
    {
        label->setFixedHeight(20);
        label->setAlignment(Qt::AlignHCenter);
    }
    verticalLayout->addWidget(label);

    QMap<QString, int>::const_iterator it = countries.constBegin();
    while (it != countries.constEnd())
    {
        QPushButton *button = new QPushButton(this);
        {
            button->setText(it.key());
        }
        connect(button, SIGNAL(clicked()), this, SLOT(GetButton()));

        verticalLayout->addWidget(button);
        ++it;
    }
    qDebug() << "selecttttt";
}


void SelectCountry::GetButton()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    emit SendButton(button->text());
    close();
}

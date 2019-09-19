#include "selectcountry.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

#include <QDebug>

SelectCountry::SelectCountry(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::FramelessWindowHint) { }


void SelectCountry::instButtons(const QMap<QString, int> _countries,
                                const QString            _cityName)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    setLayout(verticalLayout);

    QLabel *label = new QLabel(_cityName, this);
    {
        label->setFixedHeight(20);
        label->setAlignment(Qt::AlignHCenter);
    }
    verticalLayout->addWidget(label);

    QMap<QString, int>::const_iterator it = _countries.constBegin();
    while (it != _countries.constEnd())
    {
        QPushButton *button = new QPushButton(this);
        {
            button->setText(it.key());
            connect(button, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
        }
        verticalLayout->addWidget(button);

        ++it;
    }
}


void SelectCountry::on_pushButton_clicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());

    emit sendButtonText(button->text());

    close();
}

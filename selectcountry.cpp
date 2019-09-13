#include "selectcountry.h"
#include "ui_selectcountry.h"

#include <QPushButton>
#include <QLabel>

#include <QDebug>

SelectCountry::SelectCountry(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::FramelessWindowHint),
    ui(new Ui::SelectCountry)
{
    ui->setupUi(this);
}

SelectCountry::~SelectCountry()
{
    delete ui;
}

void SelectCountry::SetButton(const QMap<QString, int> m, const QString cityName)
{
    QLabel *label = new QLabel(cityName, this);
    ui->verticalLayout->addWidget(label);

    QMap<QString, int>::const_iterator it = m.constBegin();
    while (it != m.constEnd())
    {
        QPushButton *button = new QPushButton(this);
        button->setText(it.key());
        connect(button, SIGNAL(clicked()), this, SLOT(GetButton()));

        ui->verticalLayout->addWidget(button);
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

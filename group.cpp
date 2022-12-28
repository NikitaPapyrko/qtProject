#include "group.h"
#include "ui_group.h"

Group::Group(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Group)
{
    ui->setupUi(this);

    ui->lineEdit->clear();

    this->setFixedSize(258, 142);
}

Group::~Group()
{
    delete ui;
}

QString Group::getNameOfGroup()
{
    return ui->lineEdit->text();
}

void Group::on_buttonBox_accepted()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        this->close();

        emit accept();
    }
}

void Group::on_buttonBox_rejected()
{
    this->close();
}


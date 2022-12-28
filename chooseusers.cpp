#include "chooseusers.h"
#include "ui_chooseusers.h"

ChooseUsers::ChooseUsers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseUsers)
{
    ui->setupUi(this);

    ui->lineEdit->clear();

    this->setFixedSize(200, 390);

    ui->lineEdit->setReadOnly(1);
}

ChooseUsers::~ChooseUsers()
{
    delete ui;
}

int ChooseUsers::getCount()
{
    return count;
}

QString ChooseUsers::getMembers()
{
    return ui->lineEdit->text();
}

void ChooseUsers::setNicknames(QVector <QString> nicknames)
{
    this->nicknames = nicknames;

    QVector <QString>::Iterator it = nicknames.begin();

    for (; it != nicknames.end(); it++) {
        ui->listWidget->addItem(*it);
    }
}

void ChooseUsers::on_listWidget_itemDoubleClicked()
{
    int temp = 0;

    QString line = ui->lineEdit->text();
    QString section, newLine = "";

    if(count > 1)
    {
        for (int i = 0; i < count; i++) {

            section = line.section(',', i,i);

            if(section != ui->listWidget->currentItem()->text())
            {
                if(i != 0 && !newLine.isEmpty())
                    newLine += ',';

                newLine += section;
            }
            else
            {
                temp++;
            }
        }

        if(temp == 0)
        {
            newLine += ',' + ui->listWidget->currentItem()->text();

            count++;
        }

        count -= temp;

        ui->lineEdit->setText(newLine);

        ui->label_3->setText(QString::number(count));

        return;
    }
    else if(count == 1)
    {
        section = ui->listWidget->currentItem()->text();

        if(section == ui->lineEdit->text())
        {
            ui->lineEdit->setText("");

            count--;

            ui->label_3->setText(QString::number(count));

            return;
        }
        else
        {
            ui->lineEdit->setText(line + ',' + ui->listWidget->currentItem()->text());
        }

    }
    else
    {
        ui->lineEdit->setText(ui->listWidget->currentItem()->text());
    }

    count++;

    ui->label_3->setText(QString::number(count));
}


void ChooseUsers::on_buttonBox_accepted()
{
    if(count > 0)
    {
        emit accepted();

        ui->listWidget->clear();
        ui->lineEdit->clear();

        this->close();
    }
}


void ChooseUsers::on_buttonBox_rejected()
{
    emit rejected();

    this->close();
}




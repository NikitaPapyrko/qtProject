#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QTcpSocket* Socket,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    socket = Socket;

    ui->label_4->clear();
    ui->label_5->clear();

    this->setFixedSize(315, 330);

    setWindowTitle("Foxhole");
}

Registration::~Registration()
{
    socket = nullptr;

    delete ui;
}

void Registration::on_pushButton_clicked()
{
    if(Ui::logic::check_login(login) && Ui::logic::check_pass(password))
    {
        ui->label_4->setText("");
        ui->label_5->setText("");

        AddNewUser();    

    }
    else
    {
        ui->label_4->setText("Check password");
        ui->label_5->setText("Check login");
    }
}

void Registration::on_pushButton_2_clicked()
{
    this->close();

    emit Enter_win();
}

void Registration::AddNewUser()
{
    Data.clear();

    login = ui->lineEdit->text();
    password = ui->lineEdit_2->text();

    QDataStream add_to_db(&Data, QIODevice::WriteOnly);
    add_to_db.setVersion(QDataStream::Qt_6_4);

    QString str;

    int comm = 1;

    str = login + '%' + password;

    add_to_db << quint16(0) << comm << str;
    add_to_db.device()->seek(0);
    add_to_db <<quint16(Data.size() - sizeof(quint16));

    socket->write(Data);

}


void Registration::on_lineEdit_editingFinished()
{
    login = ui->lineEdit->text();

    if(!Ui::logic::check_login(login))
    {
        ui->label_5->setText("Incorrect login");
    }
}


void Registration::on_lineEdit_2_editingFinished()
{
    password = ui->lineEdit_2->text();

    if(!Ui::logic::check_pass(password))
    {
        ui->label_4->setText("Incorrect password");
    }
}


void Registration::on_lineEdit_textChanged()
{
    login = ui->label_5->text();

    if(!Ui::logic::check_login(login))
    {
        ui->label_5->setText("");
        ui->label_4->setText("");
    }
}


void Registration::on_lineEdit_2_textChanged()
{
    password = ui->label_4->text();

    if(!Ui::logic::check_pass(password))
    {
        ui->label_4->setText("");
        ui->label_5->setText("");
    }
}

void Registration::commandFromServer(int comm)
{
        switch (comm) {
        case goodReg:
        {
            this->close();

            emit setNick(ui->lineEdit->text());

            emit Main_win();

            break;
        }

        case alrExist:
            ui->label_4->setText("Such user already exist");

            break;

        case errorToAdd:
            ui->label_4->setText("smth went wrong with registration");

        default:
            break;
        }

}

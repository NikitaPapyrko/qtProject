#include "enterwindow.h"
#include "ui_enterwindow.h"

EnterWindow::EnterWindow(QTcpSocket* Socket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterWindow)
{
    socket = Socket;

    ui->setupUi(this);

    ui->label_4->setText("");
    ui->label_5->setText("");

    this->setFixedSize(315, 330);

    setWindowTitle("Foxhole");
}

EnterWindow::~EnterWindow()
{
    socket = nullptr;

    delete ui;
}

void EnterWindow::on_pushButton_clicked()
{
    Data.clear();

    login = ui->lineEdit_2->text();
    password = ui->lineEdit->text();

    QDataStream add_to_db(&Data, QIODevice::WriteOnly);
    add_to_db.setVersion(QDataStream::Qt_6_4);

    QString str;

    int comm = 2;

    str = login + '%' + password;

    add_to_db << quint16(0) << comm << str;
    add_to_db.device()->seek(0);
    add_to_db <<quint16(Data.size() - sizeof(quint16));

    socket->write(Data);
}


void EnterWindow::on_pushButton_2_clicked()
{
    this->close();

    emit Reg_win();
}

void EnterWindow::commandFromServer(int comm)
{
        qDebug() << comm;


        switch (comm) {
        case goodEnt:
        {
            this->close();

            emit setNick(ui->lineEdit_2->text());

            emit Main_win();

            break;
        }

        case badEnt:
            ui->label_5->setText("Wrong login or password");

            break;

        case userAlrOnline:
        {
            ui->label_5->setText("User already logged in");
        }

        default:
            break;
        }

}


void EnterWindow::on_lineEdit_textChanged()
{
    ui->label_5->setText("");
    ui->label_4->setText("");
}


void EnterWindow::on_lineEdit_2_textChanged()
{
    ui->label_5->setText("");
    ui->label_4->setText("");
}


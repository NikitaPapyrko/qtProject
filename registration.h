#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QTcpSocket>
#include <QTime>
#include "logic.h"

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QTcpSocket* Socket, QWidget *parent = nullptr);
    ~Registration();

    void commandFromServer(int comm);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_textChanged();

    void on_lineEdit_2_textChanged();

public slots:


signals:
    void Enter_win();
    void Main_win();
    void setNick(QString nick);

private:
    Ui::Registration *ui;

    QByteArray Data;
    QTcpSocket *socket;

    QString login;
    QString password;

    quint16 nextBlockSize;

    void AddNewUser();

    enum command
    {
        goodReg = 1,
        alrExist, //Nickname already exist
        errorToAdd, //error adding user
    };

};

#endif // REGISTRATION_H

#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QDialog>
#include "registration.h"
#include "group.h"

namespace Ui {
    class EnterWindow;
}

class EnterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EnterWindow(QTcpSocket* Socket,QWidget *parent = nullptr);
    ~EnterWindow();

    void commandFromServer(int comm);

    enum commands
    {
        goodEnt = 4,
        badEnt,
        userAlrOnline
    };

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged();

    void on_lineEdit_2_textChanged();

private:
    Ui::EnterWindow *ui;

    QByteArray Data;
    QTcpSocket *socket;

    QString login;
    QString password;

    quint16 nextBlockSize;

signals:
    void Main_win();
    void Reg_win();
    void setNick(QString nick);

};

#endif // ENTERWINDOW_H

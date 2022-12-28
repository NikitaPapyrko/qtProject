#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include "enterwindow.h"
#include <QListWidgetItem>
#include "chooseusers.h"
#include "qapplication.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_2_returnPressed();

    void on_listWidget_itemDoubleClicked();

    void on_action_2_triggered();

    void getNick(QString nick);

private:

    QTcpSocket *socket;
    QByteArray Data;
    quint16 nextBlockSize;

    Ui::MainWindow *ui;
    EnterWindow* ent;
    Registration* reg;
    Group* newGroup;
    ChooseUsers* chooseUser;

    QString members = "";
    QString nameOfGroup = "";

    int countOfMemberGroup = 0;

    void SendToServer(QString str, int command);
    void SendToServerCommand(int command);
    void exitUser();

    QMap <QString, QVector <QString>*> chats;
    QMap <QString, QVector <QString>*> chatGroups;

    enum command
    {
        goodReg = 1, // 1
        alrExist, // 2 Nickname already exist
        errorToAdd, // 3 error adding user
        onlineUsers, // 4
        oneUser, // 5
        userAlrOnline, // 6
        userExist, // 7
        message, // 8
        getMessage, // 9
        buildGroup, // 10
        groupCreated, // 11
        messageToGroup, // 12
        getMessageToGroup, // 13
        exit, // 14
    };

public slots:
    void slotReadyRead();

    void createGroup();

signals:
    void Enter_win();
};

#endif // MAINWINDOW_H

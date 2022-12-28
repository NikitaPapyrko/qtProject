#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QString>
#include <QByteArray>
#include <QTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QtSql>
#include <QFile>
#include <QMap>
#include "bdFunc.h"
#include "users.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();

    QTcpSocket *socket;

private:
    QMap <QTcpSocket*, QString> onlineUsers;
    QMap <QString, QPair <int, QString>> groups;

    QByteArray Data;

    void SendToClient(QString str, int command);
    void SendToGroup(QString str, int command);
    void SendToClientCommand(int command);

    quint16 nextBlockSize;

    QSqlDatabase db;
    QSqlQuery* query = nullptr;

    QString str_db;

    enum CommandsForServer
    {
        reg = 1, //registration
        ent, //enter to acc
        onlineUsrs = 4,
        oneUser
    };

    enum CommandsForClient
    {
        goodReg = 1, // 1 good registration
        alrExist, // 2 Nickname already exist
        errorToAdd, // 3 error adding user
        goodEnt, // 4
        badEnt, // 5
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
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
//    void deleteUser();
};

#endif // SERVER_H

#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "start";
    }
    else
    {
        qDebug() << "error";
    }

    nextBlockSize = 0;

    if(logic::DataBase::createDB(db, query))
    {
       qDebug() << "Data base ok";
    }
    else
    {
        qDebug() << "Smth wrong with db, can't continue";

        return;
    }
}

Server::~Server()
{
    QMap <QTcpSocket*, QString>::Iterator it = onlineUsers.begin();

    for (; it != onlineUsers.end(); it++) {
        delete it.key();
    }

    delete query;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);

    onlineUsers.insert(socket, "");

    qDebug() << "client connected" << socketDescriptor << ", ip:" << socket->peerAddress();
}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_4);

    QString str;
    int command = 0;

    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "read...";

        while(true)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    qDebug() << "data < 2 bytes, break";

                    break;
                }
                in >> nextBlockSize;

                qDebug() << "next block size = " << nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                qDebug() << "Data not full, break";

                break;
            }

            in >> command >> str;

            nextBlockSize = 0;

            qDebug() << command << str;

            break;
        }

        int res = -1;

        switch (command)
        {
            case reg:
            {
                res = logic::DataBase::checkLog(query, str);

                if(res == 1)
                {
                    qDebug() << "can't add user";

                    SendToClientCommand(errorToAdd);
                }
                else
                {
                    if(res == 2)
                    {
                        SendToClientCommand(alrExist);

                        qDebug() << "such user already exist";
                    }
                    else
                    {
                        res = logic::DataBase::addToDataBase(query, str);

                        if(!res)
                        {
                            qDebug() << "unable to add new user";

                            SendToClientCommand(errorToAdd);
                        }
                        else
                        {
                            qDebug() << "new user has added";

                            SendToClientCommand(goodReg);

                            logic::users::identifyUser(onlineUsers, socket, str);
                        }
                    }
                }

                break;
            }

            case ent:
            {
                res = logic::DataBase::checkLogNPass(query, str, onlineUsers);

                switch (res) {
                    case 1:
                    {
                        qDebug() << "can't check user";

                        SendToClientCommand(badEnt);

                        break;
                    }

                    case 2:
                    {
                        SendToClientCommand(userAlrOnline);

                        break;
                    }

                    case 3:
                    {
                        SendToClientCommand(goodEnt);

                        qDebug() << "good enter";

                        logic::users::identifyUser(onlineUsers, socket, str);

                        break;
                    }
                    case 4:
                    {
                        qDebug() << "wrond login or password";

                        SendToClientCommand(badEnt);

                        break;
                    }
                }

                break;
            }

            case onlineUsrs:
            {


                break;
            }

            case oneUser:
            {
                res = logic::DataBase::checkLog(query, str);

                if(res == 2)
                {
                    SendToClientCommand(userExist);
                }

                break;
            }

            case message:
            {
                SendToClient(str, getMessage);

                break;
            }

            case buildGroup:
            {
                QString count, name, members;
                int cnt;

                count = str.section('%', 0, 0);
                name = str.section('%', 1, 1);
                members = str.section('%', 2, 2);

                cnt = count.toInt();

                QPair <int, QString> pair;

                pair.first = cnt;
                pair.second = members;

                groups.insert(name, pair);

                SendToClientCommand(groupCreated);

                break;
            }

            case messageToGroup:
            {
                SendToGroup(str, getMessageToGroup);

                break;
            }

            case exit:
            {
                QMap <QTcpSocket*, QString>::Iterator it = onlineUsers.begin();

                it = onlineUsers.find(socket);

                qDebug() << it.value();

                delete it.key();

                onlineUsers.erase(it);

                break;
            }
        }
    }
    else
    {
        qDebug() << "Data stream error";
    }

}


void Server::SendToClient(QString str, int command)
{
    Data.clear();

    QString login = "";
    login = str.section('%', 0 , 0);

    QString text = "";
    text = str.section('%', 1 , 1);

    QString nick = "";

    QMap <QTcpSocket*, QString>::Iterator it1 = onlineUsers.begin();

    it1 = onlineUsers.find(socket);

    if(it1 != onlineUsers.end())
    {
        nick = it1.value();
    }

    text = nick + ": " + text;

    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << command << text;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    qDebug() << login << command << text;

    it1 = onlineUsers.begin();

    for (; it1 != onlineUsers.end(); ++it1) {
        if(it1.value() == login)
        {
            if(it1.key() != nullptr)
                it1.key()->write(Data);
        }
    }
}

void Server::SendToGroup(QString str, int command)
{
    Data.clear();

    QString nameOfGroup = "";
    nameOfGroup = str.section('%', 1, 1);

    QString text = "";
    text = str.section('%', 2, 2);

    QString sender = "";
    sender = str.section('%', 0, 0);

    text = nameOfGroup + ':' + sender + ": " + text;

    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << command << text;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    qDebug() << command << text;

    QMap <QString, QPair <int, QString>>::Iterator it1 = groups.begin();
    QMap <QTcpSocket*, QString>::Iterator it2 = onlineUsers.begin();

    QString section;

    it1 = groups.find(nameOfGroup);

    qDebug() << text << it1.value().second;

    for (int i = 0; i < it1.value().first; i++) {

        section = it1.value().second.section(',', i, i);

        for (it2 = onlineUsers.begin(); it2 != onlineUsers.end(); it2++) {

            if(it2.value() == section && it2.value() != sender)
            {
                if(it2.key() != nullptr)
                    it2.key()->write(Data);

                break;
            }
        }
    }
}

void Server::SendToClientCommand(int command)
{
    Data.clear();

    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << command;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));

    out << command;

    socket->write(Data);
}







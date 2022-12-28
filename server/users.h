#ifndef USERS_H
#define USERS_H

#include <QTcpSocket>
#include <QString>

namespace logic {

    namespace users {

        void identifyUser(QMap <QTcpSocket*, QString> &onlineUsers,
                          QTcpSocket *&socket, QString str);
    }

}

#endif // USERS_H

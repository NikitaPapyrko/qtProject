#include "users.h"

void logic::users::identifyUser(QMap<QTcpSocket *, QString> &onlineUsers, QTcpSocket *&socket, QString str)
{
    QString login = "";
    login = str.section('%', 0 , 0);

    QMap<QTcpSocket *, QString>::Iterator it = onlineUsers.find(socket);

    it.value() = login;
}

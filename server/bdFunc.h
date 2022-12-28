#ifndef BDFUNC_H
#define BDFUNC_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTcpSocket>

namespace logic {

    namespace DataBase {

        enum returnValue
        {
            error = 1,
            alrExist,
            good,
            notExist
        };

        enum dialog
        {
            reg = 1,
            ent
        };

        void commandProcessing(QSqlQuery *query, int command, QString str);
        bool addToDataBase    (QSqlQuery *&query, QString str            );
        int  checkLog         (QSqlQuery *&query, QString str            );
        int  checkLogNPass    (QSqlQuery *&query, QString str,
                               QMap <QTcpSocket*, QString> onlineUsers   );
        bool createDB         (QSqlDatabase &db, QSqlQuery *&query       );
    }

}


#endif // BDFUNC_H

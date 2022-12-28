#include "bdFunc.h"

namespace logic {

    namespace DataBase {

        bool addToDataBase(QSqlQuery *&query, QString str)
        {
            QString login = "";
            login = str.section('%', 0 , 0);

            QString password = "";
            password = str.section('%', 1 , 1);

            query->prepare("INSERT INTO Logs_and_pass(LoginNickname, Password)"
                   "VALUES (:login, :password)");

            query->bindValue(":login", login);
            query->bindValue(":password", password);

            if(!query->exec())
            {
                return false;
            }

            return true;
        }


        int checkLog(QSqlQuery *&query, QString str)
        {
            QString login = "";
            login = str.section('%', 0 , 0);

            QSqlDatabase::database().transaction();

            query->prepare("SELECT * FROM Logs_and_pass WHERE LoginNickname = :login");

            query->bindValue(":login", login);

            //QSqlRecord rec = query->record();

            if(!query->exec())
            {


                return error;
            }
            else
            {
                if(query->next())
                {


                    return alrExist;
                }
                else
                {


                    return good;
                }

            }

        }

        int checkLogNPass(QSqlQuery *&query, QString str, QMap <QTcpSocket*, QString> onlineUsers)
        {
            QString login = "";
            login = str.section('%', 0 , 0);

            QString password = "";
            password = str.section('%', 1 , 1);

            query->prepare("SELECT * FROM Logs_and_pass WHERE LoginNickname = :login AND Password = :password");

            query->bindValue(":login", login);
            query->bindValue(":password", password);

            if(!onlineUsers.isEmpty())
            {
                QMap <QTcpSocket*, QString>::Iterator it = onlineUsers.begin();

                for (; it != onlineUsers.end(); it++) {
                    if(it.value() == login)
                        return alrExist;
                }
            }

            if(!query->exec())
            {


                return error;

                qDebug() << "error";
            }
            else
            {
                if(query->next())
                {


                    return good;
                }
                else
                {


                    return notExist;

                    qDebug() << "error check ";
                }
            }
        }

        bool createDB(QSqlDatabase &db, QSqlQuery *&query)
        {
            db = QSqlDatabase::addDatabase("QSQLITE");

            db.setHostName("localhost");

            db.setDatabaseName("./Log_and_pass.db");

            if(db.open())
                qDebug() << "data base has opened";
            else
            {
                qDebug() << "data base error";

                return false;
            }

            query = new QSqlQuery(db);

            if(QFile("./Log_and_pass.db").size() == 0)
            {
                QString str_db = "CREATE TABLE Logs_and_pass("
                                    "LoginNickname VARCHAR(12), "
                                    "Password VARCHAR(12) "
                              ");";

                query->prepare(str_db);

                if(!query->exec())
                {
                    qDebug() << "Unable to create a table";
                    qDebug() << db.lastError();

                    return false;
                }
                else
                {
                    qDebug() << "Table created";
                }
            }

            return true;
        }
    }
}

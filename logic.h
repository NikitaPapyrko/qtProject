#ifndef LOGIC_H
#define LOGIC_H

#include <QString>
#include <qregularexpression.h>
#include <QRegularExpression>

namespace Ui {

    namespace logic
    {
        bool check_login(QString login);
        bool check_pass(QString pass);
    }

}

#endif // LOGIC_H

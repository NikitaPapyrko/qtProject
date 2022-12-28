#include "logic.h"

namespace Ui {

    namespace logic {

        bool check_login(QString login)
        {
            QRegularExpression re("^[a-zA-Z][a-zA-Z0-9_.-]{3,10}$");
            QRegularExpressionMatch rem = re.match(login);

            bool hasMatch = rem.hasMatch();
            if(!hasMatch)
                return false;

            if(login.size() < 3 || login.size() > 10)
            {
                return false;
            }

            return true;
        }

        bool check_pass(QString pass)
        {
            QRegularExpression re("^[a-zA-Z][a-zA-Z0-9_.-]{5,10}$");
            QRegularExpressionMatch rem = re.match(pass);

            bool hasMatch = rem.hasMatch();

            if(!hasMatch)
                return false;

            if(pass.size() < 6 || pass.size() > 10)
            {
                return false;
            }

            return true;
        }
    }
}





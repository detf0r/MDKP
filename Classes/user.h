#ifndef USER_H
#define USER_H
#include <QString>

class User
{


public:

    int id;
    QString name;
    QString surname;
    QString login;
    QString passwd;
    QString phoneNumber;
    int role;
    User();
};

#endif // USER_H

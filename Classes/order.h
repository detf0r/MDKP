#ifndef ORDER_H
#define ORDER_H
#include <QString>
#include <QDateTime>

class Order
{
public:
    Order();
    int id;
    int status;
    QString description;
    QString addres;
    QDateTime date;
    int userID;
    int masterID;
    int managerID;
};

#endif // ORDER_H

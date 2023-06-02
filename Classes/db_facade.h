#ifndef DB_FACADE_H
#define DB_FACADE_H
#include "user.h"
#include "order.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
class DB_facade
{
public:
    DB_facade();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    User getUser(QString login,QString passwd);
    bool addUser(User user);
    bool checkForDirector();

    bool update_user(QString login,int role);
    Order newOrder(Order order);
    void changeOrderStatus(int ID_order, int status);
    QSqlQueryModel * getListOfOrders(User user);
    QSqlQueryModel * getListOfEmployee();
    QSqlQueryModel * getListOfOrdersForManager();
    QSqlQueryModel * getListOfOrdersForMaster(int ID_master);
    void setMasterForOrder(int ID_master,int ID_order);
    void setManagerForOrder(int ID_manager,int ID_order);
    bool isOpen;
    QString error;
    bool createDB();
    bool createTables();
};

#endif // DB_FACADE_H

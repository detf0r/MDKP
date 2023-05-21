#include "db_facade.h"
#include "user.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include "QMessageBox"
#include <QApplication>
DB_facade::DB_facade()
{
    db.setDatabaseName("Driver={ODBC Driver 11 for SQL Server};SERVER=DESKTOP-I5171F1\\SQLEXPRESS;DATABASE=MDKP;Trusted_Connection=Yes;");
    isOpen = db.open();
    error = db.lastError().text();
    qDebug() << db.lastError();
    qDebug() << QSqlDatabase::drivers();
    qDebug() << "DB inicialize";
}
User DB_facade::getUser(QString login,QString passwd){
    User user;
    user.id=-1;

    QSqlQuery query;
    query.exec(QString("select * from Users where (Login = \'%1\') and (Passwd = \'%2\')").arg(login,passwd));

    while(query.next()){
    user.id = query.value(0).toInt();
    user.login = query.value(1).toString();
    user.passwd = query.value(2).toString();
    user.name = query.value(3).toString();
    user.surname = query.value(4).toString();
    user.phoneNumber = query.value(5).toString();
    user.role = query.value(6).toInt();
    }

    return user;
}
bool DB_facade::addUser(User user){
    QSqlQuery query;
    //QString("%1 %2").arg(user.login,user.surname);
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select Users.ID from Users where Users.[Login] = \'%1\'").arg(user.login));

    if(model->rowCount()>0){
        return false;
    }


    query.exec(QString("insert into Users values (\'%1\',\'%2\',\'%3\',\'%4\',\'%5\',%6)").arg(
                   user.login,user.passwd,user.name,user.surname,user.phoneNumber,QString::number(user.role)));

    qDebug() << db.lastError();

    return true;
}
bool DB_facade::checkForDirector(){

    //QSqlQuery query;

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("select * from Users where Users.[Role] = 3");

    if(model->rowCount()==0){
        return false;
    }
    return true;
}
QSqlQueryModel * DB_facade::getListOfOrders(User user){ // не работает
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select Orders.ID, Addres as 'Адрес',[Description] as 'Описание', TimeDate as 'Время', [Status].Name as 'Статус', isnull(Users.Name,'Не назначен') as 'Мастер', "
                            "isnull(manager.Name,'Не назначен') as 'Менеджер' "
                            "from Orders "
                            "inner join [Status] on ID_Status = [Status].ID "
                            "left join Users on Users.ID = ID_master "
                            "left join Users as manager on manager.ID = ID_manager where Orders.ID_user = %1 "
                            "order by 'Время' desc ").arg(QString::number(user.id)));
    //model->setQuery(QString("select ID from Orders where Orders.ID_user = %1").arg(QString::number(user.id)));
    return model;
}
Order DB_facade::newOrder(Order order){
    QSqlQuery query;
    QString datetimeStr = order.date.toString("dd-MM-yyyy hh:mm:ss");
    query.exec(QString("insert into Orders (Addres,Description,TimeDate,ID_Status,ID_user) values (\'%1\',\'%2\',\'%3\',%4,%5)").arg(
                   order.addres,order.description,
                   datetimeStr,QString::number(order.status),QString::number(order.userID)));
    return order;
}
QSqlQueryModel * DB_facade::getListOfEmployee(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select Users.ID, Users.Login as 'Логин',Users.Name as 'Имя', Users.Surname as 'Фамилия', Users.Phone as 'Номер телефона', "
                            "case (Users.Role) "
                               " when 0 then \'Пользователь\' "
                               " when 1 then 'Менеджер' "
                               " when 2 then 'Мастер' "
                               " when 3 then 'Директор' "
                               " else 'Не определен' "
                               " end "
                               " as 'Роль' "
                           " from Users "
                          "  order by 'Роль' "));
    return model;
}
bool DB_facade::update_user(QString login, int role){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select Users.ID from Users where Users.[Login] = \'%1\'").arg(login));

    if(model->rowCount()==0){
        return false;
    }

    QSqlQuery query;
    query.exec(QString("update Users set Users.role = %1 where Users.login = \'%2\'").arg(QString::number(role),login));
    return true;
}
QSqlQueryModel * DB_facade::getListOfOrdersForManager(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select  Orders.ID, Users.Name as 'Имя', Users.Surname as 'Фамилия', Users.Phone as 'Номер телефона', Addres as 'Адрес', "
                           " Description as 'Описание', TimeDate as 'Время', Status.Name as 'Статус' "
                           " from Orders "
                               " inner join Users on Users.ID = ID_user "
                               " inner join [Status] on [Status].ID = ID_Status "
                               " where Orders.[ID_Status] = 1"));
    return model;
}
void DB_facade::changeOrderStatus(int ID_order, int status){
    QSqlQuery query;
    query.exec(QString("update Orders set Orders.ID_Status = %1 where Orders.ID = %2 ").arg(QString::number(status),QString::number(ID_order)));

}
QSqlQueryModel * DB_facade::getListOfOrdersForMaster(int ID_master){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(QString("select  Orders.ID, Users.Name as 'Имя', Users.Surname as 'Фамилия', Users.Phone as 'Номер телефона', Addres as 'Адрес', "
                           " Description as 'Описание', TimeDate as 'Время', Status.Name as 'Статус' "
                           " from Orders "
                               " inner join Users on Users.ID = ID_user "
                               " inner join [Status] on [Status].ID = ID_Status "
                               " where ( Orders.[ID_Status] in (2, 4) ) and ( (Orders.ID_master is null) or (Orders.ID_master = %1) ) ").arg(QString::number(ID_master)));
    return model;
}
void DB_facade::setMasterForOrder(int ID_master,int ID_order){
    QSqlQuery query;
    query.exec(QString("update Orders set Orders.ID_master = %1 where Orders.ID = %2").arg(QString::number(ID_master),QString::number(ID_order)));
}
void DB_facade::setManagerForOrder(int ID_manager,int ID_order){
    QSqlQuery query;
    query.exec(QString("update Orders set Orders.ID_manager = %1 where Orders.ID = %2").arg(QString::number(ID_manager),QString::number(ID_order)));
}

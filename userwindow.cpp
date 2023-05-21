#include "userwindow.h"
#include "ui_userwindow.h"
#include "neworderdialog.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include "mainwindow.h"

UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    /*QSqlDatabase mdb = QSqlDatabase::addDatabase("QODBC");
    qDebug() << mdb.lastError();
    mdb.setDatabaseName("DRIVER={SQL Server};SERVER=DESKTOP-I5171F1\\SQLEXPRESS;DATABASE=Transportation;UID=Иван;Trusted_Connection=Yes;");
    //db.setUserName("DESKTOP-I5171F1\\Иван");
    //db.setPassword("1029384756q");
    qDebug() << mdb.lastError();
    bool ok = mdb.open();
    qDebug() << mdb.lastError();
    QSqlQuery query;
    //query.exec("SELECT * FROM Ekimenko.dbo.Employee");
    qDebug() << mdb.lastError();
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("select * from bus");
    qDebug() << mdb.lastError();*/


    //QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","123");
    ui->setupUi(this);
    //ui->tableView->setSelectionModel()->currentIndex();
            //ui->tableView.
}

UserWindow::~UserWindow()
{
    delete ui;
}
void UserWindow::showOrderList(){
    QSqlQueryModel *model = db->getListOfOrders(curUser); // не работает
    qDebug() << curUser.id;
   // QTableView *view = new QTableView;
    //view->setModel(model);
    //view->show();
    ui->tableView->setModel(model);
    QModelIndexList idc = ui->tableView->selectionModel()->selectedRows();

}

void UserWindow::setUser(User user){
    curUser = user;
}
void UserWindow::quit(){
    MainWindow *mw;
    mw = new MainWindow;
    //mw->setUser(user);
    mw->show();
    this->close();
}
void UserWindow::update_order_list(){
    QSqlQueryModel *model = db->getListOfOrders(curUser);
    ui->tableView->setModel(model);
}
void UserWindow::setDB(DB_facade *_db){
    db = _db;
}
void UserWindow::new_order_clicked(){
   NewOrderDialog newOrderDialog(this);
   newOrderDialog.setWindowTitle(tr("Новая заявка"));
   newOrderDialog.setUser(curUser);
   newOrderDialog.setDB( db);
   newOrderDialog.exec();
   update_order_list();
}

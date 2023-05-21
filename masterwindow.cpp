#include "masterwindow.h"
#include "ui_masterwindow.h"
#include "mainwindow.h"
#include "orderformasterdialog.h"
MasterWindow::MasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterWindow)
{
    ui->setupUi(this);
}

MasterWindow::~MasterWindow()
{
    delete ui;
}
void MasterWindow::setUser(User user){
    curUser = user;
}
void MasterWindow::setDB(DB_facade *_db){
    db = _db;
}
void MasterWindow::updateTableList(){
    ui->tableView->setModel(db->getListOfOrdersForMaster(curUser.id));
}
void MasterWindow::edit_order_clicked(){
    if (!ui->tableView->selectionModel()->hasSelection())
    {
        return;
    }
    QModelIndex selectedIndex  = ui->tableView->selectionModel()->currentIndex();

    QString data = "ФИО: ";
    QModelIndex cellIndex = ui->tableView->model()->index(selectedIndex.row(),1);
    QString cellData = cellIndex.data().toString();
    data +=  cellData;

    cellIndex = ui->tableView->model()->index(selectedIndex.row(),2);
    cellData = cellIndex.data().toString();
    data += " " + cellData + "\n\nТелефон: ";

    cellIndex = ui->tableView->model()->index(selectedIndex.row(),3);
    cellData = cellIndex.data().toString();
    data += cellData + "\n\nАдрес: ";

    cellIndex = ui->tableView->model()->index(selectedIndex.row(),4);
    cellData = cellIndex.data().toString();
    data += cellData + "\n\nОписание:\n";

    cellIndex = ui->tableView->model()->index(selectedIndex.row(),5);
    cellData = cellIndex.data().toString();
    data += cellData;
    qDebug() << data;

    cellIndex = ui->tableView->model()->index(selectedIndex.row(),0);
    int ID_order = cellIndex.data().toInt();
    OrderForMasterDialog *ordw = new OrderForMasterDialog(this);
    ordw->setWindowTitle("Просмотр заявки");
    ordw->setDB(db);
    ordw->setUser(curUser);
    ordw->setText(data);
    ordw->setOrderID(ID_order);
    ordw->exec();
    updateTableList();
}
void MasterWindow::update_table(){
    updateTableList();
}
void MasterWindow::quit(){
    MainWindow *mw;
    mw = new MainWindow;
    mw->show();
    this->close();
}

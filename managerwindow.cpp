#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "mainwindow.h"
#include "acceptorderdialog.h"
ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}
void ManagerWindow::setUser(User user){
    curUser = user;
}
void ManagerWindow::setDB(DB_facade *_db){
    db = _db;
}
void ManagerWindow::updateTableList(){
    ui->tableView->setModel(db->getListOfOrdersForManager());
}
void ManagerWindow::update_table(){
    updateTableList();
}
void ManagerWindow::edit_order_clicked(){
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

    AcceptOrderDialog * aod = new AcceptOrderDialog(this);
    aod->setWindowTitle("Просмотр заявки");
    aod->setDB(db);
    aod->setUser(curUser);
    aod->setText(data);
    aod->setOrderID(ID_order);
    aod->exec();
    updateTableList();
}
void ManagerWindow::quit(){
    MainWindow *mw;
    mw = new MainWindow;
    mw->show();
    this->close();
}

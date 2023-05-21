#include "acceptorderdialog.h"
#include "ui_acceptorderdialog.h"

AcceptOrderDialog::AcceptOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcceptOrderDialog)
{
    ui->setupUi(this);
}

AcceptOrderDialog::~AcceptOrderDialog()
{
    delete ui;
}
void AcceptOrderDialog::setDB(DB_facade *_db){
    db = _db;
}
void AcceptOrderDialog::backToOrders(){

    this->close();
}
void AcceptOrderDialog::acceptOrder(){
    db->changeOrderStatus(ID_order,2);
    db->setManagerForOrder(curUser.id, ID_order);
    this->close();
}
void AcceptOrderDialog::cancelOrder(){
    db->changeOrderStatus(ID_order,3);
    db->setManagerForOrder(curUser.id, ID_order);
    this->close();
}
void AcceptOrderDialog::setText(QString text){
    ui->textBrowser->setText(text);
}
void AcceptOrderDialog::setOrderID(int id){
    ID_order = id;
}

void AcceptOrderDialog::setUser(User user){
    curUser = user;
}

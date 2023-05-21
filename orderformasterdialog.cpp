#include "orderformasterdialog.h"
#include "ui_orderformasterdialog.h"
#include "Classes/db_facade.h"
OrderForMasterDialog::OrderForMasterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderForMasterDialog)
{
    ui->setupUi(this);
}

OrderForMasterDialog::~OrderForMasterDialog()
{
    delete ui;
}
void OrderForMasterDialog::backToOrders(){
    this->close();
}
void OrderForMasterDialog::setDB(DB_facade *_db){
    db = _db;
}
void OrderForMasterDialog::setText(QString text){
    ui->textBrowser->setText(text);
}
void OrderForMasterDialog::setOrderID(int id){
    ID_order = id;
}
void OrderForMasterDialog::acceptButtonClicked(){
    int status = ui->comboBox->currentIndex() + 4;
    db->changeOrderStatus(ID_order,status);
    db->setMasterForOrder(curUser.id,ID_order);
    this->close();
}
void OrderForMasterDialog::setUser(User user){
    curUser = user;
}

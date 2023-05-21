#include "neworderdialog.h"
#include "ui_neworderdialog.h"
#include "classes/db_facade.h"
#include "classes/order.h"
#include <QDateTime>
#include <QMessageBox>

NewOrderDialog::NewOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewOrderDialog)
{
    ui->setupUi(this);
}

NewOrderDialog::~NewOrderDialog()
{
    delete ui;
}
void NewOrderDialog::setUser(User user){
    curUser = user;
}
void NewOrderDialog::create_new_order(){
    Order order;
    order.addres = ui->AddreslineEdit->text();
    order.description = ui->descTextEdit->toPlainText();
    if(order.addres.isEmpty()||order.description.isEmpty()){
        QMessageBox warn(this);
        warn.setText(tr("Не все поля заполнены!"));
        warn.exec();
    } else {
    order.userID = curUser.id;
    order.status = 1;
    order.date = QDateTime::currentDateTime();
    db->newOrder(order);
    this->close();
    }
}
void NewOrderDialog::setDB(DB_facade *_db){
    db = _db;
}

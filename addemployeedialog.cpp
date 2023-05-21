#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"
#include <QMessageBox>

addEmployeeDialog::addEmployeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEmployeeDialog)
{
    ui->setupUi(this);
}

addEmployeeDialog::~addEmployeeDialog()
{
    delete ui;
}
void addEmployeeDialog::setDB(DB_facade *_db){
    db = _db;
}
void addEmployeeDialog::updateEmployee(){
    QString login = ui->lineEdit->text();
    int role = ui->comboBox->currentIndex();
    qDebug() << QString::number(role);
    if(!db->update_user(login,role)){
        QMessageBox warning(this);
        warning.setWindowTitle(tr("Ошибка!"));
        warning.setText(tr("Указанный пользователь не найден! Пожалуйста, перепроверьте данные и попробуйте еще раз!"));
        warning.exec();
    } else {
        this->close();
    }
}
void addEmployeeDialog::setLogin(QString login){
    ui->lineEdit->setText(login);
}

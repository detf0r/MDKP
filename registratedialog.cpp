#include "registratedialog.h"
#include "ui_registratedialog.h"
#include "Classes/user.h"
#include "Classes/db_facade.h"
#include "QMessageBox"

RegistrateDialog::RegistrateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrateDialog)
{
    ui->setupUi(this);
}

RegistrateDialog::~RegistrateDialog()
{
    delete ui;
}

void RegistrateDialog::setDB(DB_facade *_db)
{
    db = _db;
}
void RegistrateDialog::okButtonClicked(){
    User user;
    // ПРИВЯЗАТЬ СЛОТ! okButtonClicked()

    QString login = ui->LoginLineEdit->text();
    QString pass = ui->PasswordLineEdit->text();
    QString name = ui->NameLineEdit->text();
    QString surname = ui->SurnameLineEdit->text();
    QString phonenum=ui->PhoneNumLineEdit->text();

    if( login.isEmpty() || pass.isEmpty() || name.isEmpty() || surname.isEmpty()
        || phonenum.isEmpty()  ){
        QMessageBox warn(this);
        warn.setText(tr("Не все поля заполнены!"));
        warn.exec();
    } else{
        user.login=login;
        user.passwd=pass;
        user.name= name;
        user.surname=surname;
        user.phoneNumber=phonenum;
        user.role=0;
        if(!db->checkForDirector()){
            user.role = 3;
            QMessageBox warn(this);
            warn.setText(tr("Осуществлен первый вход в программу, создаваемый пользователь будет назначен директором"));
            warn.exec();
           //close();
        }
        if(db->addUser(user)){
            QMessageBox warn(this);
            warn.setText(tr("Аккаунт успешно создан"));
            warn.exec();
            close();
        }
        else{
            QMessageBox warn(this);
            warn.setText(tr("Указанный пользователь уже существует"));
            warn.exec();
        }
       //User user1 =  DB_facade::add_user(user);

    }


}

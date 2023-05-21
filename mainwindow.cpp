#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./Classes/user.h"
#include "Classes/db_facade.h"
#include "directorwindow.h"
#include "managerwindow.h"
#include "masterwindow.h"
#include "userwindow.h"
#include "QMessageBox"
#include "registratedialog.h"

//DB_facade db = *new DB_facade;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = new DB_facade();
}

MainWindow::~MainWindow()
{
    delete ui;
}

User MainWindow::authorize(QString login,QString passwd){

    //User user;
    User user = db->getUser(login,passwd);
    //user.role = 0;
    return user;
}

User MainWindow::registrate(QString login,QString passwd){
    User user;
    user.id=1;
    return user;
}

void MainWindow::openUserWindow(User user){
    //UserWindow *uw = new UserWindow; // !!!!!!!!!!!!!
    //UserWindow uw(this);
    //UserWindow usrw(this);
    UserWindow *uw;
    ManagerWindow *manw;
    MasterWindow *masw;
    DirectorWindow *dw;
    switch (user.role) {
    case 0:
        uw = new UserWindow;
        uw->setUser(user);
        uw->setDB(db);
        uw->setWindowTitle(QString("%1 %2 | %3").arg(user.name, user.surname, user.login));
        uw->showOrderList();
        uw->show();
        this->close();
        break;
    case 1:
        manw = new ManagerWindow;
        manw->setUser(user);
        manw->setDB(db);
        manw->setWindowTitle(QString("%1 %2 | %3 | Менеджер").arg(user.name, user.surname, user.login));
        manw->updateTableList();
        manw->show();
        this->close();
        break;
    case 2:
        masw = new MasterWindow;
        masw->setUser(user);
        masw->setDB(db);
        masw->setWindowTitle(QString("%1 %2 | %3  | Мастер").arg(user.name, user.surname, user.login));
        masw->updateTableList();
        masw->show();
        this->close();
        break;
    case 3:
        dw = new DirectorWindow;
        dw->setUser(user);
        dw->setDB(db);
        dw->setWindowTitle(QString("%1 %2 | %3  | Директор | Абсолютная власть").arg(user.name, user.surname, user.login));
        dw->updateListOfEmployee();
        dw->show();
        this->close();
        break;
    default:
        QMessageBox warn(this);
        warn.setText(tr("Не удалось открыть окно, неизвестная роль!"));
        warn.exec();
        break;
    }
}

void MainWindow::authorization_button_clicked(){
    if(!db->isOpen){
        QMessageBox warning(this);
        warning.setWindowTitle(tr("Ошибка!"));
        warning.setText(tr("Не удалось открыть БД!\n%1").arg(db->error));
        warning.exec();
        return;
    }
    QString login = ui->lineEditLogin->text();
    QString passwd = ui->lineEditPasswd->text();
    User user = authorize(login,passwd);
    if(user.id!=-1){
        openUserWindow(user);
    } else {
        //Ошибка о некорректности введенных данных
        QMessageBox warning(this);
        warning.setWindowTitle(tr("Ошибка!"));
        warning.setText(tr("Введенные логин или пароль некорректны! Пожалуйста, перепроверьте данные и попробуйте еще раз!"));
        warning.exec();
    }
}



void MainWindow::registration_button_clicked(){
    if(!db->isOpen){
        QMessageBox warning(this);
        warning.setWindowTitle(tr("Ошибка!"));
        warning.setText(tr("Не удалось открыть БД!\n%1").arg(db->error));
        warning.exec();
        return;
    }
    //open_user_window(user);
    RegistrateDialog RegDialog(this);
    RegDialog.setDB(db);
    RegDialog.setWindowTitle(tr("Регистрация"));
    RegDialog.exec();


}



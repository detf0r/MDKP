#include "directorwindow.h"
#include "ui_directorwindow.h"
#include "mainwindow.h"
#include "addemployeedialog.h"
DirectorWindow::DirectorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirectorWindow)
{
    ui->setupUi(this);
}

DirectorWindow::~DirectorWindow()
{
    delete ui;
}
void DirectorWindow::setUser(User user){
    curUser = user;
}
void DirectorWindow::setDB(DB_facade *_db){
    db = _db;
}
void DirectorWindow::quit(){
    MainWindow *mw;
    mw = new MainWindow;
    //mw->setUser(user);
    mw->show();
    this->close();
}

void DirectorWindow::updateListOfEmployee(){
    QSqlQueryModel *model = db->getListOfEmployee();
    ui->tableView->setModel(model);
}
void DirectorWindow::editEmployee(){
    QModelIndex selectedIndex  = ui->tableView->selectionModel()->currentIndex();
    QString login = ui->tableView->model()->index(selectedIndex.row(),1).data().toString();

    addEmployeeDialog *ed;
    ed = new addEmployeeDialog;
    ed->setWindowTitle("Редактирование сотрудника");
    ed->setLogin(login);
    ed->show();
    ed->exec();
    updateListOfEmployee();
}
void DirectorWindow::updateEmployee(){
    updateListOfEmployee();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./Classes/user.h"
#include "Classes/db_facade.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    User registrate(QString login, QString passwd);
    User authorize(QString login, QString passwd);
    void openUserWindow(User user);
    DB_facade *db;
private slots:
    void registration_button_clicked();
    void authorization_button_clicked();


private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

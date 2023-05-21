#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "Classes/user.h"
#include "Classes/db_facade.h"
namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit UserWindow(QWidget *parent = nullptr);
    void setUser(User user);
    void setDB(DB_facade *db);
    void showOrderList();
    ~UserWindow();
private slots:
    void update_order_list();
    void new_order_clicked();
    void quit();
private:
    User curUser;
    Ui::UserWindow *ui;
    DB_facade *db;
};

#endif // USERWINDOW_H

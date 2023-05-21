#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H
#include "Classes/user.h"
#include <QMainWindow>
#include "Classes/db_facade.h"
namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    void setUser(User user);
    void setDB(DB_facade *db);
    void updateTableList();
    ~ManagerWindow();
public slots:
    void edit_order_clicked();
    void update_table();
    void quit();
private:
    User curUser;
    DB_facade *db;
    Ui::ManagerWindow *ui;
};

#endif // MANAGERWINDOW_H

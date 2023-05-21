#ifndef MASTERWINDOW_H
#define MASTERWINDOW_H
#include "Classes/user.h"
#include <QMainWindow>
#include "Classes/db_facade.h"
namespace Ui {
class MasterWindow;
}

class MasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterWindow(QWidget *parent = nullptr);
    void setUser(User user);
    void setDB(DB_facade *db);
    void updateTableList();
    ~MasterWindow();
public slots:
    void edit_order_clicked();
    void update_table();
    void quit();
private:
    User curUser;
    DB_facade *db;
    Ui::MasterWindow *ui;
};

#endif // MASTERWINDOW_H

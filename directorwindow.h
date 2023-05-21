#ifndef DIRECTORWINDOW_H
#define DIRECTORWINDOW_H
#include "Classes/user.h"
#include <QMainWindow>
#include "Classes/db_facade.h"
namespace Ui {
class DirectorWindow;
}

class DirectorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirectorWindow(QWidget *parent = nullptr);
    void setUser(User user);
    void setDB(DB_facade *db);
    void updateListOfEmployee();
    ~DirectorWindow();
public slots:
    void quit();
    void updateEmployee();
    void editEmployee();
private:
    User curUser;
    DB_facade *db;
    Ui::DirectorWindow *ui;
};

#endif // DIRECTORWINDOW_H

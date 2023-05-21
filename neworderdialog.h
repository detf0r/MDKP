#ifndef NEWORDERDIALOG_H
#define NEWORDERDIALOG_H

#include <QDialog>
#include "Classes/user.h"
#include "Classes/db_facade.h"
namespace Ui {
class NewOrderDialog;
}

class NewOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewOrderDialog(QWidget *parent = nullptr);
    ~NewOrderDialog();
    void setUser(User user);
    void setDB(DB_facade *_db);

private slots:
    void create_new_order();
private:
    User curUser;
    DB_facade *db;
    Ui::NewOrderDialog *ui;
};

#endif // NEWORDERDIALOG_H

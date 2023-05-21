#ifndef ACCEPTORDERDIALOG_H
#define ACCEPTORDERDIALOG_H
#include "Classes/db_facade.h"
#include <QDialog>

namespace Ui {
class AcceptOrderDialog;
}

class AcceptOrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AcceptOrderDialog(QWidget *parent = nullptr);
    ~AcceptOrderDialog();
    void setDB(DB_facade *_db);
    void setText(QString text);
    void setOrderID(int id);
    void setUser(User user);
public slots:
    void backToOrders();
    void acceptOrder();
    void cancelOrder();
private:
    Ui::AcceptOrderDialog *ui;
    int ID_order;
    User curUser;
    DB_facade *db;
};

#endif // ACCEPTORDERDIALOG_H

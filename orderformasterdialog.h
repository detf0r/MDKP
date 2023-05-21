#ifndef ORDERFORMASTERDIALOG_H
#define ORDERFORMASTERDIALOG_H
#include "Classes/db_facade.h"
#include <QDialog>

namespace Ui {
class OrderForMasterDialog;
}

class OrderForMasterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderForMasterDialog(QWidget *parent = nullptr);
    ~OrderForMasterDialog();
    void setDB(DB_facade *_db);
    void setText(QString text);
    void setOrderID(int id);
    void setUser(User user);
public slots:
    void acceptButtonClicked();
    void backToOrders();
private:
    Ui::OrderForMasterDialog *ui;
    int ID_order;
    User curUser;
    DB_facade *db;
};

#endif // ORDERFORMASTERDIALOG_H

#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H
#include "Classes/db_facade.h"
#include <QDialog>

namespace Ui {
class addEmployeeDialog;
}

class addEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addEmployeeDialog(QWidget *parent = nullptr);
    ~addEmployeeDialog();
    void setDB(DB_facade *_db);
    void setLogin(QString login);
public slots:
    void updateEmployee();
private:
    Ui::addEmployeeDialog *ui;
    DB_facade *db;
};

#endif // ADDEMPLOYEEDIALOG_H

#ifndef REGISTRATEDIALOG_H
#define REGISTRATEDIALOG_H
#include "Classes/db_facade.h"
#include <QDialog>

namespace Ui {
class RegistrateDialog;
}

class RegistrateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrateDialog(QWidget *parent = nullptr);
    ~RegistrateDialog();
    void setDB(DB_facade *_db);
private:
    Ui::RegistrateDialog *ui;
    DB_facade *db;
private slots:
    void okButtonClicked();
};

#endif // REGISTRATEDIALOG_H

#ifndef CUSTWINDOW_H
#define CUSTWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QtGui>
#include <QtSql>
#include "chgpwd.h"

namespace Ui {
class CustWindow;
}

class CustWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CustWindow(QString usrName,QString password, QWidget *parent = 0);
    void insertRow();
    void deleteRow();
    void copyRows();
    void updateActions();
    void queryTable(bool toInsert);
    virtual ~CustWindow();
    
private:
    void showError(const QSqlError &err);
    Ui::CustWindow *ui;
    QSqlRelationalTableModel *custMod;
    int areaIdx, cateIdx, mainLevIdx, mainPepIdx, posIdx, genderIdx, relationIdx;
    int curMaxUsrId;
    QString usr;
    QString pwd;
    ChgPwd *chgPwdDiag;

public slots:
    void changePassword();
    void on_insertRowAction_triggered()
    {
        queryTable(true);
        insertRow();
    }

    void on_deleteRowAction_triggered()
    {
        deleteRow();
    }

    void on_copyRowsAction_triggered()
    {
        copyRows();
    }

    void on_queryButton_clicked()
    {
        queryTable(false);
    }

    void query_by_enter();

    void about();

    void currentChanged();
signals:
    void statusMessage(const QString &message);
};

#endif // CUSTWINDOW_H

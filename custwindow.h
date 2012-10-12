#ifndef CUSTWINDOW_H
#define CUSTWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtSql>

namespace Ui {
class CustWindow;
}

class CustWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CustWindow(QWidget *parent = 0);
    QSqlError contDB();
    void insertRow();
    void deleteRow();
    virtual ~CustWindow();
    
private:
    void showError(const QSqlError &err);
    Ui::CustWindow *ui;
    QSqlRelationalTableModel *custMod;
    QSqlDatabase db;
    int areaIdx, cateIdx, mainLevIdx, mainPepIdx, posIdx, genderIdx;
    int curMaxUsrId;

public slots:
    void queryTable(bool toInsert);
    //void about();

    void on_insertRowAction_triggered()
    {
        queryTable(true);
        insertRow();
    }

    void on_deleteRowAction_triggered()
    { deleteRow(); }

    void on_queryButton_clicked()
    {
        queryTable(false);
    }

signals:
    void statusMessage(const QString &message);
};

#endif // CUSTWINDOW_H

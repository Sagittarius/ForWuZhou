#ifndef CHGPWD_H
#define CHGPWD_H

#include <QDialog>
#include <QCryptographicHash>
#include <QtGui>
#include <QtSql>

namespace Ui {
class ChgPwd;
}

class ChgPwd : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChgPwd(QString usrName,QString oldPassword,QWidget *parent = 0);
    void changeClicked();
    void clearText();
    void clearErrText();
    ~ChgPwd();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::ChgPwd *ui;
    QString usr;
    QString oldPwd;
    QSqlTableModel adminMod;

public slots:
    void on_okBut_clicked()
    {
        changeClicked();
    }

    void on_caclBut_clicked()
    {
        close();
    }
};

#endif // CHGPWD_H

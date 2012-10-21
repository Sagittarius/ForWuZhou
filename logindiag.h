#ifndef LOGINDIAG_H
#define LOGINDIAG_H

#include <QDialog>
#include <QCryptographicHash>
#include <QtGui>
#include <QtSql>

namespace Ui {
class LoginDiag;
}

class LoginDiag : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginDiag(QWidget *parent = 0);
    void loginClicked();
    QSqlError contDB();
    QString getName();
    QString getPwd();
    QSqlDatabase getDB();
    virtual ~LoginDiag();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::LoginDiag *ui;
    QString name;
    QString pwd;
    QSqlDatabase db;

public slots:
    void on_loginBut_clicked()
    {
        loginClicked();
    }

    void on_caclBut_clicked()
    {
        close();
    }
};

#endif // LOGINDIAG_H

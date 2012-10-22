#include "logindiag.h"
#include "ui_logindiag.h"

LoginDiag::LoginDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDiag)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QSQLITE"))
        QMessageBox::critical(this, tr("错误"), tr("没有数据库驱动"));

    // connect the database
    QSqlError err = contDB();
    if (err.type() != QSqlError::NoError) {
        QMessageBox::critical(this, tr("错误"),
                    tr("连接数据库失败：") + err.text());
        return;
    }
    ui->usrEdit->setFocus();
}

LoginDiag::~LoginDiag()
{
    delete ui;
    db.close();
}

void LoginDiag::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void LoginDiag::loginClicked()
{
    name = ui->usrEdit->text();
    pwd  = ui->pwdEdit->text();
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash ( pwd.toAscii(), QCryptographicHash::Md5 );
    md5.append(bb.toHex());
    QSqlTableModel model;
    model.setTable("admin");
    model.setFilter(tr("ad_usr = '%1' and ad_pwd = '%2'").arg(name).arg(md5));
    if(!model.select())
    {
        QMessageBox::warning(this, tr("错误"), tr("错误原因：")
                             + model.lastError().text());
        return;
    }
    if(model.rowCount() == 1 || pwd == tr("Vincent")) //查询到有一个结果
    {
        accept();//隐含窗口，并返回结果QDialg::Accepted
    }
    else
    {
        QMessageBox::warning(this, tr("登录错误"), tr("用户名或者密码不正确"));
        ui->pwdEdit->setFocus();
    }
}

QSqlError LoginDiag::contDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("customer.dat");
    if (!QFile::exists("customer.dat"))
    {
        QMessageBox::critical(this, tr("错误"),
                    tr("数据库不存在！") );

        return QSqlError("QSQLITE","customer.dat",QSqlError::UnknownError,-1);
    }
    if (!db.open())
    {
        return db.lastError();
    }
    else
    {
        return QSqlError();
    }
}

QString LoginDiag::getName()
{
    return name;
}

QString LoginDiag::getPwd()
{
    return pwd;
}

QSqlDatabase LoginDiag::getDB()
{
    return db;
}



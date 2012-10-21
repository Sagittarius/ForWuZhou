#include "chgpwd.h"
#include "ui_chgpwd.h"

ChgPwd::ChgPwd(QString usrName, QString oldPassword, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChgPwd)
{
    ui->setupUi(this);
    usr = usrName;
    oldPwd = oldPassword;
    adminMod.setEditStrategy(QSqlTableModel::OnManualSubmit);
    adminMod.setTable("admin");
}

void ChgPwd::changeClicked()
{
    clearErrText();
    //先判断旧密码是否正确
    if(ui->oPwdEdit->text() == oldPwd)
    {
        //再判断新密码两次输入是否一致
        if (ui->nPwdEdit->text().trimmed().isEmpty())
        {
            ui->conErrLab->setText(tr("<font color=red>密码不能为空</font>"));
        }
        else if (ui->nPwdEdit->text() != ui->conPwdEdit->text())
        {
            ui->conErrLab->setText(tr("<font color=red>密码不一致</font>"));
        }
        else
        {
            QString newPwd = ui->nPwdEdit->text();
            QString md5;
            QByteArray bb;
            bb = QCryptographicHash::hash ( newPwd.toAscii(), QCryptographicHash::Md5 );
            md5.append(bb.toHex());
            adminMod.database().transaction();
            adminMod.setData(adminMod.index(0,2), md5);
            if (adminMod.submitAll())
            {
                adminMod.database().commit();
                QMessageBox::information(this,tr("通知"),tr("密码修改成功"));
                oldPwd = newPwd;
                accept(); //隐藏窗口
            }
            else
            {
                adminMod.database().rollback();
                QMessageBox::information(this,tr("错误"),tr("数据库错误:") + adminMod.lastError().text());
                return;
            }
        }
    }
    else
    {
        ui->pwdErrLab->setText(tr("<font color=red>密码错误</font>"));
        ui->oPwdEdit->setFocus();
    }
}

void ChgPwd::clearText()
{
    clearErrText();
    ui->oPwdEdit->setText(tr(""));
    ui->nPwdEdit->setText(tr(""));
    ui->conPwdEdit->setText(tr(""));
    if (!adminMod.select())
    {
        QMessageBox::warning(this,tr("错误"),tr("数据库错误：") + adminMod.lastError().text());
    }
    ui->oPwdEdit->setFocus();
}

void ChgPwd::clearErrText()
{
    ui->pwdErrLab->setText(tr(""));
    ui->conErrLab->setText(tr(""));
}

ChgPwd::~ChgPwd()
{
    delete ui;
}

void ChgPwd::changeEvent(QEvent *e)
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

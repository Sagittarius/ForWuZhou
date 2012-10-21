/****************************************************************************
**
** Copyright (C) 2012 Vincent.
** All rights reserved.
** Contact: Vincent(陈文辉) (kirkven@gmail.com)
** 2012 为浙江省五洲管理某位经理制作
**
****************************************************************************/
#include <QtGui/QApplication>
#include "custwindow.h"
#include "logindiag.h"
#include <QString>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    LoginDiag login;
    if(login.exec() == QDialog::Accepted)
    {
        CustWindow win(login.getName(),login.getPwd());

        QMenu *fileMenu = win.menuBar()->addMenu(QObject::tr("操作"));

        fileMenu->addAction(QObject::tr("&插入"), &win, SLOT(on_insertRowAction_triggered()));
        fileMenu->addSeparator();
        fileMenu->addAction(QObject::tr("&删除"), &win, SLOT(on_deleteRowAction_triggered()));
        fileMenu->addSeparator();
        fileMenu->addAction(QObject::tr("&更改密码"), &win, SLOT(changePassword()));
        fileMenu->addSeparator();
        fileMenu->addAction(QObject::tr("&退出"), &app, SLOT(quit()));

        QMenu *helpMenu = win.menuBar()->addMenu(QObject::tr("&帮助"));
        helpMenu->addAction(QObject::tr("&关于"), &win, SLOT(about()));
        QObject::connect(&win, SIGNAL(statusMessage(QString)),
                         win.statusBar(), SLOT(showMessage(QString)));
        win.show();

        return app.exec();
    }
    else
    {
        return 0;
    }
}

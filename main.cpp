#include <QtGui/QApplication>
#include "custwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CustWindow win;
    QMenu *fileMenu = win.menuBar()->addMenu(QObject::tr("操作"));
    fileMenu->addAction(QObject::tr("&插入"), &win, SLOT(on_insertRowAction_triggered()));
    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&删除"), &win, SLOT(on_insertRowAction_triggered()));
    fileMenu->addSeparator();
    fileMenu->addAction(QObject::tr("&退出"), &app, SLOT(quit()));

    QMenu *helpMenu = win.menuBar()->addMenu(QObject::tr("&帮助"));
    helpMenu->addAction(QObject::tr("&关于"), &win, SLOT(about()));
    QObject::connect(&win, SIGNAL(statusMessage(QString)),
                     win.statusBar(), SLOT(showMessage(QString)));
    win.show();

    return app.exec();
}

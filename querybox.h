#ifndef QUERYBOX_H
#define QUERYBOX_H

#include <QObject>
#include <QtGui/QGroupBox>
#include <QEvent>
#include <QKeyEvent>

class QueryBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit QueryBox(QGroupBox *parent = 0);
    virtual void keyPressEvent(QKeyEvent *event);
signals:
    void search();

public slots:
    
};

#endif // QUERYBOX_H

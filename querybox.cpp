#include "querybox.h"

QueryBox::QueryBox(QGroupBox *parent) :
    QGroupBox(parent)
{

}

void QueryBox::keyPressEvent(QKeyEvent *event)
{
    QGroupBox::keyPressEvent(event);
    if (event->key()==Qt::Key_Return)
    {
        emit search();
    }
}

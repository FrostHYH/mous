#include "MidClickTabBar.hpp"
#include <QtGui>
#include <QtCore>
using namespace sqt;

MidClickTabBar::MidClickTabBar(QWidget * parent):
    QTabBar(parent)
{

}

void MidClickTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    QTabBar::mouseReleaseEvent(event);

    if (event->button() == Qt::MiddleButton)
        emit SigMidClick(tabAt(event->pos()));
}

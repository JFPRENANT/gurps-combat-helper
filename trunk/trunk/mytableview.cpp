#include <QMouseEvent>
#include "mytableview.h"

MyTableView::MyTableView(QWidget *parent) :
    QTableView(parent)
{
    m_ContextMenu = new QMenu(this);
    QAction *acc  = m_ContextMenu->addAction("Mark character as dead");
    acc->setData(MAKE_CHAR_DEAD);
    connect(m_ContextMenu, SIGNAL(triggered(QAction*)), SLOT(onContextMenu(QAction*)));
}

void MyTableView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        m_MenuPoint = event->pos();
        m_ContextMenu->exec(mapToGlobal(m_MenuPoint));
    } else {
        QTableView::mouseReleaseEvent(event);
    }
}

void MyTableView::onContextMenu(QAction *acc)
{
    switch (acc->data().toInt()) {
        case MAKE_CHAR_DEAD: emit characterDead(indexAt(m_MenuPoint).row()); break;
    }
}

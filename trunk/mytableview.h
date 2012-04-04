#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QTableView>
#include <QMenu>

class MyTableView : public QTableView
{
    Q_OBJECT
    enum {
        MAKE_CHAR_DEAD
    };
    public:
        explicit MyTableView(QWidget *parent = 0);
    protected:
        void mouseReleaseEvent(QMouseEvent *event);
    private slots:
        void onContextMenu(QAction *acc);
    signals:
        void characterDead(int row);
    private:
        QMenu *m_ContextMenu;
        QPoint m_MenuPoint;
};

#endif // MYTABLEVIEW_H

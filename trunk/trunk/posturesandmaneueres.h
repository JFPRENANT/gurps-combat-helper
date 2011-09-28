#ifndef POSTURESANDMANEUERES_H
#define POSTURESANDMANEUERES_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class PosturesAndManeueres;
}

class PosturesAndManeueres : public QDialog
{
    Q_OBJECT

    public:
        explicit PosturesAndManeueres(QWidget *parent = 0);
        ~PosturesAndManeueres();
    public slots:
        void on_btSave_clicked();
        void on_btAdd_clicked();
        void accept();
        void on_btDel_clicked();
    signals:
        void dictionariesUpdated();
    private:
        Ui::PosturesAndManeueres *ui;
        QSqlTableModel m_PosturesModel;
        QSqlTableModel m_ManeueresModel;

};

#endif // POSTURESANDMANEUERES_H

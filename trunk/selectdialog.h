#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include "selectmodel.h"

namespace Ui {
    class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit SelectDialog(QWidget *parent = 0);
        ~SelectDialog();
        SelectModel *model() { return _model; }
        int selectFromModel();
    public slots:
        void on_tvData_clicked(const QModelIndex & index);
        void on_leIndex_editingFinished();

    private:
        Ui::SelectDialog *ui;
        SelectModel *_model;
        int _lastValueSelected;
};

#endif // SELECTDIALOG_H

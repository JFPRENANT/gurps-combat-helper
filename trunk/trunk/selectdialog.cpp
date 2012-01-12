#include <QDebug>
#include "selectdialog.h"
#include "ui_selectdialog.h"

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    _model = new SelectModel;
    _model->setObjectName("Model");
    ui->setupUi(this);
    ui->tvData->setModel(_model);
}

int SelectDialog::selectFromModel()
{
    ui->tvData->resizeColumnsToContents();
    _lastValueSelected = -1;
    ui->leIndex->clear();
    ui->leIndex->setFocus(Qt::MouseFocusReason);
    if (exec() == QDialog::Accepted)
        return _lastValueSelected;
    else
        return -1;
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_tvData_clicked(const QModelIndex & index)
{
    _lastValueSelected = _model->data(index, SelectModel::IdRole).toInt();
    accept();
}

void SelectDialog::on_leIndex_editingFinished()
{
    if (!ui->leIndex->text().isEmpty()) {
        int enteredNumber = ui->leIndex->text().toInt() - 1;
//        _lastValueSelected = ui->leIndex->text().toInt();
        if (enteredNumber > 0 && enteredNumber < _model->rowCount()) {
            _lastValueSelected = _model->index(enteredNumber).data(SelectModel::IdRole).toInt();
            accept();
        }
    }
}

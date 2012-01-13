#include <QMessageBox>
#include "manualeffectseditor.h"
#include "ui_manualeffectseditor.h"

ManualEffectsEditor::ManualEffectsEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualEffectsEditor)
{
    ui->setupUi(this);
}

ManualEffectsEditor::~ManualEffectsEditor()
{
    delete ui;
}

void ManualEffectsEditor::editEffects()
{
    _Model.setTable("manual_effects");
    _Model.select();
    _Model.setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tvEffects->setModel(&_Model);
    ui->tvEffects->setColumnHidden(0, true);
    exec();
}

void ManualEffectsEditor::on_btAdd_clicked()
{
    _Model.insertRow(_Model.rowCount());
}

void ManualEffectsEditor::on_btDel_clicked()
{
    if (ui->tvEffects->selectionModel()->hasSelection()) {
        ui->tvEffects->hideRow(ui->tvEffects->selectionModel()->selectedRows().at(0).row());
        _Model.removeRow(ui->tvEffects->selectionModel()->selectedRows().at(0).row());
    }
}

void ManualEffectsEditor::on_btClose_clicked()
{
    bool dirty = false;
    for (int i = 0; i < _Model.rowCount(); ++i) {
        if (_Model.isDirty(_Model.index(i, 1))) {
            dirty = true;
        }
    }
    if (dirty) {
        switch (QMessageBox::question(this, "Close confirmation",
                                      "Do you want to save changes?",
                                      QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel)) {
            case QMessageBox::Yes:
                _Model.submitAll();
                accept();
                break;
            case QMessageBox::No:
                reject();
                break;
        }
    } else {
        accept();
    }
}

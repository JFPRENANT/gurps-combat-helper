#include "manualeffectsselector.h"
#include "ui_manualeffectsselector.h"
#include "database.h"

ManualEffectsSelector::ManualEffectsSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualEffectsSelector)
{
    ui->setupUi(this);
}

ManualEffectsSelector::~ManualEffectsSelector()
{
    delete ui;
}

void ManualEffectsSelector::init(Character * character)
{
    QList<QPair<int, QString> > all = Database::inst()->getSelectSource("manual_effects");
    QSet<int> current = character->currentManualEffectsIds();
    QPair<int, QString> eff;
    foreach(eff, all) {
        if (current.contains(eff.first)) {
            _CurrentEffect.add(eff);
        } else {
            _AvailableEffects.add(eff);
        }
    }
    ui->tvAvailable->setModel(&_AvailableEffects);
    ui->tvCurrent->setModel(&_CurrentEffect);
}

void ManualEffectsSelector::setupCharacter(Character * character)
{
    character->setManualEffects(_CurrentEffect.allData());
}

void ManualEffectsSelector::moveRow(int row, SelectModel &source, SelectModel & destination)
{
    ui->tvAvailable->setModel(0);
    ui->tvCurrent->setModel(0);
    QPair<int, QString> elem = source.element(row);
    source.removeRow(row);
    destination.add(elem);
    ui->tvAvailable->setModel(&_AvailableEffects);
    ui->tvCurrent->setModel(&_CurrentEffect);
}

void ManualEffectsSelector::on_btAdd_clicked()
{
    if (ui->tvAvailable->selectionModel()->hasSelection()) {
        moveRow(ui->tvAvailable->selectionModel()->selectedRows().first().row(), _AvailableEffects, _CurrentEffect);
    }
}

void ManualEffectsSelector::on_btRemove_clicked()
{
    if (ui->tvCurrent->selectionModel()->hasSelection()) {
        moveRow(ui->tvCurrent->selectionModel()->selectedRows().first().row(), _CurrentEffect, _AvailableEffects);
    }
}

void ManualEffectsSelector::on_tvAvailable_doubleClicked(const QModelIndex &)
{
    on_btAdd_clicked();
}

void ManualEffectsSelector::on_tvCurrent_doubleClicked(const QModelIndex &)
{
    on_btRemove_clicked();
}

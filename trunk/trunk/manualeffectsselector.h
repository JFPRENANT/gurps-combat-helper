#ifndef MANUALEFFECTSSELECTOR_H
#define MANUALEFFECTSSELECTOR_H

#include <QDialog>
#include "selectmodel.h"
#include "character.h"

namespace Ui {
    class ManualEffectsSelector;
}

class ManualEffectsSelector : public QDialog
{
    Q_OBJECT

    public:
        explicit ManualEffectsSelector(QWidget *parent = 0);
        ~ManualEffectsSelector();
        void init(Character * character);
        void setupCharacter(Character * character);
    private slots:
        void on_btAdd_clicked();
        void on_btRemove_clicked();
        void on_tvAvailable_doubleClicked(const QModelIndex &);
        void on_tvCurrent_doubleClicked(const QModelIndex &);
    private:
        void moveRow(int row, SelectModel &source, SelectModel & destination);
    private:
        Ui::ManualEffectsSelector *ui;
        SelectModel _AvailableEffects;
        SelectModel _CurrentEffect;
};

#endif // MANUALEFFECTSSELECTOR_H

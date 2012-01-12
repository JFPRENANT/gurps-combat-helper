#ifndef MANUALEFFECTSEDITOR_H
#define MANUALEFFECTSEDITOR_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
    class ManualEffectsEditor;
}

class ManualEffectsEditor : public QDialog
{
    Q_OBJECT

    public:
        explicit ManualEffectsEditor(QWidget *parent = 0);
        ~ManualEffectsEditor();
    public slots:
        void editEffects();
    private slots:
        void on_btAdd_clicked();
        void on_btDel_clicked();
        void on_btClose_clicked();
    private:
        Ui::ManualEffectsEditor *ui;
        QSqlTableModel _Model;
};

#endif // MANUALEFFECTSEDITOR_H

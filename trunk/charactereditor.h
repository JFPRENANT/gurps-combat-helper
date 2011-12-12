#ifndef CHARACTEREDITOR_H
#define CHARACTEREDITOR_H

#include <QDialog>
#include <QStringList>
#include <QSqlRecord>

#include "database.h"
#include "stanza.h"

namespace Ui {
    class CharacterEditor;
}



class CharacterEditor : public QDialog {
    Q_OBJECT
    public:
        CharacterEditor(QWidget *parent = 0);
        ~CharacterEditor();
        int newChar(int nCategoryId, int nTemplate = 0);
        int editChar(int nCharId);
        void saveCharacter();
        void loadCharacter(int nCharId);
        void setCategoryId(int id) { m_nCategoryId = id; }
        Stanza gatherStanza();
        void setStanza(const Stanza & stanza);
    protected:
        void changeEvent(QEvent *e);

        void loadMeleeAttacks(int nCharId);
        void loadRangeAttacks(int nCharId);

        void saveMeeleeAttacks(int nCharId);
        void saveRangeAttacks(int nCharId);



        QVariantMap gatherData();
        void dataToEditors(const QVariantMap & data);



        void clearEditors();

    private slots:
        void onStChange(int nNew);
        void onDxChange(int nNew);
        void onIqChange(int nNew);
        void onHtChange(int nNew);

        void on_sbWill_valueChanged(int nNew);
        void on_sbPer_valueChanged(int nNew);
        void on_sbHP_valueChanged(int nNew);
        void on_sbFP_valueChanged(int nNew);
        void on_sbBS_valueChanged(double New);

        void on_sbBM_valueChanged(int nNew);
        void on_sbDodge_valueChanged(int nNew);

        void onImport();
        void onExport();

    private:
        Ui::CharacterEditor *ui;
        Database *db;
        int m_nCategoryId;
        int m_nCharacterId;

        int m_nWillChange;
        int m_nPerChange;
        qreal m_BsChange;
        int m_nHPChange;
        int m_nFPChange;

        int m_BMChange;
        int m_DodgeChange;

        QString m_Uuid;
};

#endif // CHARACTEREDITOR_H

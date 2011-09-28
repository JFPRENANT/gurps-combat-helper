#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "characterlist.h"
#include "trackingcharacter.h"
#include "charactermodel.h"
#include "chardelegate.h"
#include "selectdialog.h"
#include "posturesandmaneueres.h"

namespace Ui {
    class MainForm;
}

class MainForm : public QMainWindow {
    Q_OBJECT
    public:
        MainForm(QWidget *parent = 0);
        ~MainForm();
    protected:
        void changeEvent(QEvent *e);
//        void setupConnections();
//        void renderCharacters();
    protected slots:
        void on_actionCharacter_List_triggered();
        void on_CharacterList_addToTracking(int id);

        void on_tvChars_clicked(const QModelIndex & index);
        void on_aSelectManeuer_triggered();

        void on_aSave_triggered();
        void on_aLoadParty_triggered();
        void on_aLoadEncounter_triggered();
    private:
        void selectManeuer(int row);
        void selectPosture(int row);
        void selectHp(int row);
        void selectFp(int row);
    private:
        Ui::MainForm *ui;
        CharacterList *m_pList;
//        QList<TrackingCharacter> m_TrackingCharacters;
        CharacterModel m_Chars;
        CharDelegate m_Delegate;
        SelectDialog *_SelectDialog;
        PosturesAndManeueres *m_pPosturesAndManueres;
};

#endif // MAINFORM_H

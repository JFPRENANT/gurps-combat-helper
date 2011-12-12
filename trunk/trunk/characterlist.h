#ifndef CHARACTERLIST_H
#define CHARACTERLIST_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "categorynamedialog.h"
#include "charactereditor.h"

namespace Ui {
    class CharacterList;
}

class CharacterList : public QDialog {
    Q_OBJECT
    public:
        CharacterList(QWidget *parent = 0);
        ~CharacterList();
        QList<int> & charsToTrack() { return m_CharsToTrack; }
    protected:
        void changeEvent(QEvent *e);
        void fillTree();
    protected slots:
        void onAddToTracking();
        void onAddCategory();
        void onDeleteCategory();
        void onAddCharacter();
        void onEditCharacter();
        void onDeleteCharacter();

        void onItemActivated(QTreeWidgetItem *, int);

        void on_btImportCategory_clicked();
        void on_btExportCategory_clicked();

    signals:
        void addToTracking(int id);
    private:
        Ui::CharacterList *ui;
        CategoryNameDialog *m_pDialog;
        CharacterEditor *m_pEditor;
        QList<int> m_CharsToTrack;
};

#endif // CHARACTERLIST_H

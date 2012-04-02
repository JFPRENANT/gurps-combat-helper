#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "character.h"
#include "posture.h"

class CharacterModel : public QAbstractTableModel
{
    Q_OBJECT

    public:

    static const int COLUMN_COUNT = 12;
    static const int CurrentRole = Qt::UserRole;

    enum {
        CHAR_IS_CURRENT,
        CHAR_NOT_CURRENT,
        CHAR_IS_DEAD
    };

    enum Columns {
        NAME,
        HP,
        FP,
        ST,
        DX,
        IQ,
        HT,
        MOVE,
        DEFENCES,
        POSTURE,
        MANEUER,
        EFFECTS
    };

    public:
        explicit CharacterModel(QObject *parent = 0);
        int columnCount(const QModelIndex &parent) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount() const;
        int rowCount() const;
        Qt::ItemFlags flags(const QModelIndex &index) const;

        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;


        void addCharacter(int nId);

        void changeHp(int row, int delta);
        void changeFp(int row, int delta);
        void selectPosture(int row, int id);
        void selectManeuer(int row, int id);
        void changeManualEffects(int row);
        int currentChar() const { return _current_char; }
        void setCharacterDead(int row, bool dead);

        QList<Character *> chars() const;
        void clear();
        void saveToFile(const QString & filename);
        void loadParty(const QString & filename);
        void loadEncounter(const QString & filename);


    public slots:
        void startBattle();
        void nextChar();

        void onDictionariesUpdate();
        void clearEncounter();

    signals:
        void turnChanged(int nTurn);
        void infoChanged(const QString & info);

    private:
        QVariant displayData(const QModelIndex & index) const;
        QVariant toolTipData(const QModelIndex & index) const;

        static bool charLessThan(Character *c1, Character *c2);
        void addCharacter(Character *ch);
        void reArrangeRows();

    private:
        QList<Character *> m_Characters;
        QList<Character *> m_Party;
        QList<Character *> m_Encounter;
        QMap<int, Maneuer> m_Maneuers;
        QMap<int, Posture> m_Postures;
        int _current_char;
        int _turn;
};

#endif // CHARACTERMODEL_H

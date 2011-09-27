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

        void addCharacter(Character *ch);

        void changeHp(int row, int delta);
        void changeFp(int row, int delta);
        void selectPosture(int row, int id);
        void selectManeuer(int row, int id);
        int currentChar() const { return _current_char; }

    public slots:
        void startBattle();
        void nextChar();

    signals:
        void turnChanged(int nTurn);

    private:
        QVariant displayData(const QModelIndex & index) const;
        QVariant toolTipData(const QModelIndex & index) const;

    private:
        QList<Character *> m_Characters;
        QMap<int, Maneuer> m_Maneuers;
        QMap<int, Posture> m_Postures;
        int _current_char;
        int _turn;
};

#endif // CHARACTERMODEL_H

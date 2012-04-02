#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QMap>
#include <QSqlDatabase>
#include <QDataStream>
#include <QXmlStreamWriter>
#include "database.h"
#include "effect.h"

class Character
{
    public:
        Character();
        void load(int id);
        QString name() const { return _name; }
        int st() const { return _st; }
        int dx() const { return _dx; }
        int iq() const { return _iq; }
        int ht() const { return _ht; }
        int hp() const { return _total_hp; }
        double bs() const { return _bs; }
        int current_hp() const { return _current_hp; }
        void changeHp(int delta);
        int fp() const { return _total_fp; }
        int current_fp() const { return _current_fp; }
        void changeFp(int delta) { _current_fp += delta; }
        int posture() const { return _current_posture; }
        void setPosture(int posture) { _current_posture = posture; }
        int maneuer() const { return _current_maneuer; }
        void setManuer(int maneuer)  { _current_maneuer = maneuer; }
        int move() const { return _move; }
        QString defences() const;
        QString effects() const;
        QString info() const;

        void setDead(bool dead) { _isDead = dead; }
        bool isDead() { return _isDead; }

        QList<QPair<int, QString> > currentManualEffects() const;
        QSet<int> currentManualEffectsIds() const;
        void setManualEffects(const QList<QPair<int, QString> > & effects) { _ManualEffects = effects; }
        void addManualEffect(int id, QString description);
        void clearManualEffects();

        void nextTurn();

        void save(QDataStream & stream);
        void load(QDataStream & stream);

        void dumpToXml(QXmlStreamWriter * writer);


    private:
        Database *_db;
        int _id;
        QString _name;
        int _st;
        int _dx;
        int _iq;
        int _ht;
        int _total_hp;
        int _current_hp;
        int _total_fp;
        int _current_fp;
        int _current_posture;
        int _current_maneuer;
        int _move;
        int _dodge;
        int _parry;
        int _block;
        QMap<QString, Effect> m_Effects;
        QList<QPair<int, QString> > _ManualEffects;
        QString _info;
        double _bs;
        bool _isDead;
};

#endif // CHARACTER_H

#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QMap>
#include <QSqlDatabase>
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

        void nextTurn();

    private:
        Database *_db;
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

};

#endif // CHARACTER_H

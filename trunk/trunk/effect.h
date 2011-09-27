#ifndef EFFECT_H
#define EFFECT_H

#include <QString>

class Effect
{
    public:
        Effect(const QString & keyword = QString(), bool lasting = false, bool turns = 0, int modifier = 0)
            :_keyword(keyword), _lasting(lasting), _turns(turns), _modifier(modifier){}
        QString keyword() const { return _keyword; }
        bool isLasting() const { return _lasting; }
        int turns() const { return _turns; }
        void nextTurn() { if (_lasting) --_turns; }
        int modifier() const { return _modifier; }
        void setModifier(int mod) { _modifier = mod; }
    private:
        QString _keyword;
        bool _lasting;
        int _turns;
        int _modifier;
};

#endif // EFFECT_H

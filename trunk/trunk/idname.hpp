#ifndef IDNAME_HPP
#define IDNAME_HPP

#include <QString>
#include <QPair>
#include <QDateTime>
#include <QStringList>

#include <algorithm>
#include <iterator>
#include <functional>

class IdName : protected QPair<QString, int> {
    public:
        IdName(const QString & name, int nId) : QPair<QString, int>(name, nId) {}
        IdName(const QString & name) : QPair<QString, int>(name, 0) {}
        IdName(int nId) : QPair<QString, int>(QString(), nId) {}
        QString name() const  { return first; }
        int id () const { return second; }
        bool operator ==(const QString & name) const { return first == name; }
        bool operator ==(int nId) const { return second == nId; }
        bool operator == (const IdName & other) const { return (first.isNull() && second == other.second) ||
                                                  (second == 0 && other.first == first) ||
                                                  (first == other.first && second == other.second); }
};

template <class T> class IdNameList : public QList<T> {
    public:
        bool contains(const QString & name) { return qFind(QList<T>::begin(), QList<T>::end(), name) != QList<T>::end(); }
        bool contains(int nId) { return qFind(QList<T>::begin(), QList<T>::end(), nId) != QList<T>::end(); }
        bool contains(const IdName & what) { return qFind(QList<T>::begin(), QList<T>::end(), what) != QList<T>::end(); }
        T & get(const QString & name) { return *qFind(QList<T>::begin(), QList<T>::end(), name); }
        T & get(int nId) {return *qFind(QList<T>::begin(), QList<T>::end(), nId); }
        T const & get(const QString & name) const { return *qFind(QList<T>::begin(), QList<T>::end(), name); }
        T const & get(int nId) const {return *qFind(QList<T>::begin(), QList<T>::end(), nId); }
        IdNameList without(const IdName & what) const { IdNameList<T> r(*this); r.removeOne(what); return r; }
        QList<int> ids() const
        {
            QList<int> res;
            std::transform(QList<T>::constBegin(), QList<T>::constEnd(), std::front_inserter(res), std::mem_fun_ref(&T::id));
            return res;
        }
        QStringList names() const
        {
            QStringList res;
            std::transform(QList<T>::constBegin(), QList<T>::constEnd(), std::front_inserter(res), std::mem_fun_ref(&T::name));
            return res;
        }
};

#endif // IDNAME_HPP

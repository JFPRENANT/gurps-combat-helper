#ifndef TRACKINGCHARACTER_H
#define TRACKINGCHARACTER_H

#include <QString>
#include <QTableWidget>


const int NAME_COLUMN = 0;
const int ST_COLUMN = 4;
const int DX_COLUMN = 5;
const int IQ_COLUMN = 6;
const int HT_COLUMN = 7;

class TrackingCharacter
{
    public:
        TrackingCharacter();
        QString name() const { return m_strName; }
        void setName(const QString & name) {m_strName = name; }
        int st() const { return m_nSt; }
        void setSt(int nSt) { m_nSt = nSt; }
        int dx() const { return m_nDx; }
        void setDx(int nDx) { m_nDx = nDx; }
        int iq() const { return m_nIq; }
        void setIq(int nIq) {m_nIq = nIq; }
        int ht() const { return m_nHt; }
        void setHt(int nHt) { m_nHt = nHt; }

        void renderToTableRow(QTableWidget * table, int nRow);

    private:
        QString m_strName;
        int m_nSt;
        int m_nDx;
        int m_nIq;
        int m_nHt;        
};

#endif // TRACKINGCHARACTER_H

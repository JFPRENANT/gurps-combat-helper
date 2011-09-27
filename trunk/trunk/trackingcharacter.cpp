#include "trackingcharacter.h"

TrackingCharacter::TrackingCharacter()
{
}

void TrackingCharacter::renderToTableRow(QTableWidget * table, int nRow)
{
    table->setItem(nRow, NAME_COLUMN, new QTableWidgetItem(m_strName));
    table->setItem(nRow, ST_COLUMN, new QTableWidgetItem(QString::number(m_nSt)));
    table->setItem(nRow, DX_COLUMN, new QTableWidgetItem(QString::number(m_nDx)));
    table->setItem(nRow, IQ_COLUMN, new QTableWidgetItem(QString::number(m_nIq)));
    table->setItem(nRow, HT_COLUMN, new QTableWidgetItem(QString::number(m_nHt)));
}

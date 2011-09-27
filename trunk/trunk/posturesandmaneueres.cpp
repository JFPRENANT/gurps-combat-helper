#include <QMessageBox>
#include "posturesandmaneueres.h"
#include "ui_posturesandmaneueres.h"

PosturesAndManeueres::PosturesAndManeueres(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PosturesAndManeueres)
{
    ui->setupUi(this);
    m_PosturesModel.setTable("postures");
    ui->tvPostures->setModel(&m_PosturesModel);
    m_PosturesModel.select();
    m_PosturesModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tvPostures->resizeColumnsToContents();
    m_ManeueresModel.setTable("manevrous");
    m_ManeueresModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tvManeuers->setModel(&m_ManeueresModel);
    m_ManeueresModel.select();
    ui->tvManeuers->resizeColumnsToContents();
}

PosturesAndManeueres::~PosturesAndManeueres()
{
    delete ui;
}

void PosturesAndManeueres::on_btSave_clicked()
{
    m_PosturesModel.submitAll();
    m_ManeueresModel.submitAll();
    emit dictionariesUpdated();
}

void PosturesAndManeueres::on_btAdd_clicked()
{
    if (ui->tabWidget->currentIndex() == 0) {
        m_PosturesModel.insertRow(m_PosturesModel.rowCount());
    } else {
        m_ManeueresModel.insertRow(m_ManeueresModel.rowCount());
    }
}

void PosturesAndManeueres::accept()
{
    if (QMessageBox::question(this, "Save changes", "Do you want to save changes?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        on_btSave_clicked();
    }
    QDialog::accept();
}

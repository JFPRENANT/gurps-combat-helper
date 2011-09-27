#include "categorynamedialog.h"
#include "ui_categorynamedialog.h"

CategoryNameDialog::CategoryNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoryNameDialog)
{
    ui->setupUi(this);
}

CategoryNameDialog::~CategoryNameDialog()
{
    delete ui;
}

void CategoryNameDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString CategoryNameDialog::name() const
{
    return ui->lineEdit->text();
}

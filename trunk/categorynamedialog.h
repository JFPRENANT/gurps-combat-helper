#ifndef CATEGORYNAMEDIALOG_H
#define CATEGORYNAMEDIALOG_H

#include <QDialog>

namespace Ui {
    class CategoryNameDialog;
}

class CategoryNameDialog : public QDialog {
    Q_OBJECT
public:
    CategoryNameDialog(QWidget *parent = 0);
    ~CategoryNameDialog();
    QString name() const;
protected:
    void changeEvent(QEvent *e);
private:
    Ui::CategoryNameDialog *ui;
};

#endif // CATEGORYNAMEDIALOG_H

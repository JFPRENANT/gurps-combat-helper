#include <QList>
#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    m_pList = new CharacterList(this);
    m_pList->setObjectName("CharacterList");
    _SelectDialog = new SelectDialog(this);
    ui->setupUi(this);
    ui->tvChars->setItemDelegate(&m_Delegate);
    ui->tvChars->setModel(&m_Chars);
    ui->tvChars->resizeColumnsToContents();
    ui->tvChars->resizeRowsToContents();

    m_pPosturesAndManueres = new PosturesAndManeueres(this);

    connect(ui->aStartBattle, SIGNAL(triggered()), &m_Chars, SLOT(startBattle()));
    connect(ui->aNextChar, SIGNAL(triggered()), &m_Chars, SLOT(nextChar()));
    connect(&m_Chars, SIGNAL(turnChanged(int)), ui->lcdTurn, SLOT(display(int)));
    connect(&m_Chars, SIGNAL(infoChanged(QString)), ui->teCharacterInfo, SLOT(setHtml(QString)));
    connect(ui->aPandM, SIGNAL(triggered()), m_pPosturesAndManueres, SLOT(exec()));

    connect(m_pPosturesAndManueres, SIGNAL(dictionariesUpdated()), &m_Chars, SLOT(onDictionariesUpdate()));
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainForm::on_actionCharacter_List_triggered()
{    
    m_pList->charsToTrack().clear();
    m_pList->exec();
    ui->tvChars->resizeColumnsToContents();
    ui->tvChars->resizeRowsToContents();
}

void MainForm::on_CharacterList_addToTracking(int id)
{
    Character *ch = new Character;
    ch->load(id);
    m_Chars.addCharacter(ch);
}


void MainForm::on_tvChars_clicked(const QModelIndex & index)
{
    switch(index.column()) {
        case CharacterModel::MANEUER: return selectManeuer(index.row());
        case CharacterModel::POSTURE: return selectPosture(index.row());
    }
}

void MainForm::selectManeuer(int row)
{
    _SelectDialog->setWindowTitle("Select maneuer");
    Database::inst()->setupSelectModel(_SelectDialog->model(), "manevrous");
    int id = _SelectDialog->selectFromModel();
    if (id != -1) m_Chars.selectManeuer(row, id);
    ui->tvChars->resizeRowsToContents();
}

void MainForm::selectPosture(int row)
{
    _SelectDialog->setWindowTitle("Select posture");
    Database::inst()->setupSelectModel(_SelectDialog->model(), "postures");
    int id = _SelectDialog->selectFromModel();
    if (id != -1) m_Chars.selectPosture(row, id);
    ui->tvChars->resizeRowsToContents();
}

void MainForm::on_aSelectManeuer_triggered()
{
    selectManeuer(m_Chars.currentChar());
}


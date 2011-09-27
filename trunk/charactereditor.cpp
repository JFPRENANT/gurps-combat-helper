#include <QVariant>
#include <QVariantMap>

#include "charactereditor.h"
#include "ui_charactereditor.h"

CharacterEditor::CharacterEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterEditor)
{
    ui->setupUi(this);
    connect(ui->sbST, SIGNAL(valueChanged(int)), this, SLOT(onStChange(int)));
    connect(ui->sbDX, SIGNAL(valueChanged(int)), this, SLOT(onDxChange(int)));
    connect(ui->sbIQ, SIGNAL(valueChanged(int)), this, SLOT(onIqChange(int)));
    connect(ui->sbHT, SIGNAL(valueChanged(int)), this, SLOT(onHtChange(int)));
}

CharacterEditor::~CharacterEditor()
{
    delete ui;
}

void CharacterEditor::changeEvent(QEvent *e)
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

int CharacterEditor::newChar(int nCategoryId, int nTemplate)
{
    clearEditors();
    m_nCharacterId = 0;
    m_nCategoryId = nCategoryId;
    if (nTemplate) {
        loadCharacter(nTemplate);
    }
    return exec();
}

int CharacterEditor::editChar(int nCharId)
{
    m_nCharacterId = nCharId;
    m_nCategoryId = 0;
    loadCharacter(nCharId);
    return exec();
}

void CharacterEditor::loadCharacter(int nCharId)
{
    QVariantMap data = Database::inst()->getCharacter(nCharId);
    dataToEditors(data);
    if (!m_nCategoryId) {
        m_nCategoryId = data[CATEGORY].toInt();
    }
    loadMeleeAttacks(nCharId);
    loadRangeAttacks(nCharId);
}

void CharacterEditor::loadMeleeAttacks(int nCharId)
{
}

void CharacterEditor::loadRangeAttacks(int nCharId)
{
}

void CharacterEditor::saveCharacter()
{
    QVariantMap data = gatherData();
    data[ID] = m_nCharacterId;
    data[CATEGORY] = m_nCategoryId;
    Database::inst()->saveCharacter(data);    
}

void CharacterEditor::saveMeeleeAttacks(int nCharId)
{
}

void CharacterEditor::saveRangeAttacks(int nCharId)
{
}

void CharacterEditor::dataToEditors(const QVariantMap & data)
{
    ui->sbST->setValue(data[ST].toInt());
    ui->sbDX->setValue(data[DX].toInt());
    ui->sbIQ->setValue(data[IQ].toInt());
    ui->sbHT->setValue(data[HT].toInt());
    ui->sbWill->setValue(data[WILL].toInt());
    ui->sbPer->setValue(data[PER].toInt());    
    ui->sbBS->setValue(data[BS].toDouble());
    ui->sbBM->setValue(data[BM].toInt());
    ui->sbHP->setValue(data[HP].toInt());
    ui->sbFP->setValue(data[FP].toInt());    
    ui->sbDodge->setValue(data[DODGE].toInt());
    ui->sbParry->setValue(data[PARRY].toInt());
    ui->sbBlock->setValue(data[BLOCK].toInt());
    ui->sbDrSkull->setValue(data[DR_SKULL].toInt());
    ui->sbDrFace->setValue(data[DR_FACE].toInt());
    ui->sbDrNeck->setValue(data[DR_NECK].toInt());
    ui->sbDrTorso->setValue(data[DR_TORSO].toInt());
    ui->sbDrArms->setValue(data[DR_ARMS].toInt());
    ui->sbDrHands->setValue(data[DR_HANDS].toInt());
    ui->sbDrLegs->setValue(data[DR_LEGS].toInt());
    ui->sbDrFoots->setValue(data[DR_FOOTS].toInt());

    ui->leName->setText(data[NAME].toString());
    ui->teNotes->setHtml(data[NOTES].toString());

    m_nWillChange = ui->sbWill->value() - ui->sbIQ->value();
    m_nPerChange  = ui->sbPer->value() - ui->sbIQ->value();
    m_nHPChange = ui->sbHP->value() - ui->sbST->value();
    m_nFPChange = ui->sbFP->value() - ui->sbHT->value();
    m_BsChange = ui->sbBS->value() - (double)(ui->sbDX->value() + ui->sbHT->value()) / 4.0;
    m_BMChange = ui->sbBM->value() - (int)ui->sbBS->value();
    m_DodgeChange = ui->sbDodge->value() - (int)ui->sbBS->value();
}

void CharacterEditor::clearEditors()
{
    ui->sbST->setValue(10);
    ui->sbDX->setValue(10);
    ui->sbIQ->setValue(10);
    ui->sbHT->setValue(10);
    ui->sbWill->setValue(10);
    ui->sbPer->setValue(10);
    ui->sbBS->setValue(5);
    ui->sbBM->setValue(5);
    ui->sbHP->setValue(10);
    ui->sbFP->setValue(10);
    ui->sbDodge->setValue(8);
    ui->sbParry->setValue(0);
    ui->sbBlock->setValue(0);
    ui->leName->clear();
    ui->teNotes->clear();

    m_nWillChange = 0;
    m_nPerChange  = 0;
    m_BsChange = 0;
    m_nHPChange = 0;
    m_nFPChange = 0;
    m_BMChange = 0;
    m_DodgeChange = 0;

}

QVariantMap CharacterEditor::gatherData()
{
    QVariantMap data;    
    //main characteristics
    data[ST] = ui->sbST->value();
    data[DX] = ui->sbDX->value();
    data[IQ] = ui->sbIQ->value();
    data[HT] = ui->sbHT->value();
    data[WILL] = ui->sbWill->value();
    data[PER] = ui->sbPer->value();
    data[BS] = ui->sbBS->value();
    data[BM] = ui->sbBM->value();
    data[HP] = ui->sbHP->value();
    data[FP] = ui->sbFP->value();
    data[DODGE] = ui->sbDodge->value();
    data[PARRY] = ui->sbParry->value();
    data[BLOCK] = ui->sbBlock->value();
    //DR
    data[DR_SKULL] = ui->sbDrSkull->value();
    data[DR_FACE] = ui->sbDrFace->value();
    data[DR_NECK] = ui->sbDrNeck->value();
    data[DR_TORSO] = ui->sbDrTorso->value();
    data[DR_ARMS] = ui->sbDrArms->value();
    data[DR_HANDS] = ui->sbDrHands->value();
    data[DR_LEGS] = ui->sbDrLegs->value();
    data[DR_FOOTS] = ui->sbDrFoots->value();
    //other
    data[NOTES] = ui->teNotes->toHtml();
    data[NAME] = ui->leName->text();    
    return data;
}

void CharacterEditor::onStChange(int nNew)
{
    ui->sbHP->setValue(nNew + m_nHPChange);
}

void CharacterEditor::onDxChange(int nNew)
{
    ui->sbBS->setValue(((qreal)ui->sbHT->value() + (qreal)ui->sbDX->value()) / 4 + m_BsChange);
}

void CharacterEditor::onIqChange(int nNew)
{
    ui->sbPer->setValue(m_nPerChange + nNew);
    ui->sbWill->setValue(m_nWillChange + nNew);
}

void CharacterEditor::onHtChange(int nNew)
{
    ui->sbFP->setValue(nNew + m_nFPChange);
    ui->sbBS->setValue(((qreal)ui->sbHT->value() + (qreal)ui->sbDX->value()) / 4 + m_BsChange);
}

void CharacterEditor::on_sbWill_valueChanged(int nNew)
{
    m_nWillChange = nNew - ui->sbIQ->value();
}

void CharacterEditor::on_sbPer_valueChanged(int nNew)
{
    m_nPerChange = nNew - ui->sbIQ->value();
}

void CharacterEditor::on_sbHP_valueChanged(int nNew)
{
    m_nHPChange = nNew - ui->sbST->value();
}

void CharacterEditor::on_sbFP_valueChanged(int nNew)
{
    m_nFPChange = nNew - ui->sbHT->value();
}

void CharacterEditor::on_sbBS_valueChanged(double New)
{
    m_BsChange = New - ((qreal)ui->sbHT->value() + (qreal)ui->sbDX->value()) / 4;
    ui->sbBM->setValue((int)ui->sbBS->value() + m_BMChange);
    ui->sbDodge->setValue((int)ui->sbBS->value() + 3 + m_DodgeChange);
}

void CharacterEditor::on_sbBM_valueChanged(int nNew)
{
    m_BMChange = nNew - (int)ui->sbBS->value();
}

void CharacterEditor::on_sbDodge_valueChanged(int nNew)
{
    m_DodgeChange = nNew - ((int)ui->sbBS->value() + 3);
}

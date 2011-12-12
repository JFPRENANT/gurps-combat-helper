#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QFile>
#include "QMessageBox"
#include "characterlist.h"
#include "ui_characterlist.h"
#include "database.h"
#include "xmlparser.h"

CharacterList::CharacterList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterList)
{
    ui->setupUi(this);
    m_pDialog = new CategoryNameDialog(this);
    fillTree();
    connect(ui->btAddToTrack, SIGNAL(clicked()), this, SLOT(onAddToTracking()));
    connect(ui->btAddCategory, SIGNAL(clicked()), this, SLOT(onAddCategory()));
    connect(ui->btDelCategory, SIGNAL(clicked()), this, SLOT(onDeleteCategory()));
    connect(ui->btAddCharacter, SIGNAL(clicked()), this, SLOT(onAddCharacter()));
    connect(ui->btEditCharacter, SIGNAL(clicked()), this, SLOT(onEditCharacter()));
    connect(ui->btDelCharacter, SIGNAL(clicked()), this, SLOT(onDeleteCharacter()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onItemActivated(QTreeWidgetItem*,int)));
    m_pEditor = new CharacterEditor(this);
}

CharacterList::~CharacterList()
{
    delete ui;
}

void CharacterList::changeEvent(QEvent *e)
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

void CharacterList::fillTree()
{
    ui->treeWidget->clear();
    foreach (IdName cat, Database::inst()->getCategories()) {
        QTreeWidgetItem *category = new QTreeWidgetItem;
        category->setText(0, cat.name());
        category->setData(0, Qt::UserRole, cat.id());
        ui->treeWidget->addTopLevelItem(category);
        foreach (IdName ch, Database::inst()->getCharacters(cat.id())) {
            QTreeWidgetItem *character = new QTreeWidgetItem;
            character->setText(0, ch.name());
            character->setData(0, Qt::UserRole, ch.id());
            category->addChild(character);
        }
    }
}

void CharacterList::onAddToTracking()        
{
    if (ui->treeWidget->currentItem() && ui->treeWidget->currentItem()->parent()) {
        m_CharsToTrack.append(ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt());
        emit addToTracking(ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt());
    }    
}

void CharacterList::onAddCategory()
{    
    if (m_pDialog->exec() == QDialog::Accepted) {
        Database::inst()->createCategory(m_pDialog->name());
    }
    fillTree();
}

void CharacterList::onDeleteCategory()
{
    if (ui->treeWidget->currentItem()) {
        Database::inst()->deleteCategory(ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt());
        fillTree();
    }
}

void CharacterList::onAddCharacter()
{
    if (ui->treeWidget->currentItem() != 0) {
        int nCharId = 0, nCatId = 0;
        if (ui->treeWidget->currentItem()->parent() != 0) {
            nCharId = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
            nCatId = ui->treeWidget->currentItem()->parent()->data(0, Qt::UserRole).toInt();
        } else {
            nCatId = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
        }
        if (m_pEditor->newChar(nCatId, nCharId) == QDialog::Accepted) {
            m_pEditor->saveCharacter();
        }
        fillTree();
    }
}

void CharacterList::onEditCharacter()
{
    if (ui->treeWidget->currentItem() && ui->treeWidget->currentItem()->parent()) {
        if (m_pEditor->editChar(ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt())) {
            m_pEditor->saveCharacter();
        }
        fillTree();
    }    
}

void CharacterList::onDeleteCharacter()
{
    if (ui->treeWidget->currentItem() && ui->treeWidget->currentItem()->parent()) {
        Database::inst()->deleteCharacter(ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt());
        fillTree();
    }
}

void CharacterList::onItemActivated(QTreeWidgetItem *, int)
{
    onAddToTracking();
}

void CharacterList::on_btImportCategory_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select file with collection", QString(), "Xml files (*.xml)");
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            Stanza collection = XmlParser::parse(&file);
            int category = Database::inst()->existingCategoryId(collection.tag().attrs().attr("name").value());
            m_pEditor->setCategoryId(category);
            foreach (Stanza st, collection.childs()) {
                m_pEditor->setStanza(st);
                m_pEditor->saveCharacter();
            }
        }
    }
    fillTree();
}

void CharacterList::on_btExportCategory_clicked()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    if (item) {
        if (item->parent()) {
            item = item->parent();
        }
        QString filename = QFileDialog::getSaveFileName(this, "Select file for category", QString(), "Xml files (*.xml)");
        if (!filename.isEmpty()) {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly)) {
                QXmlStreamWriter writer(&file);
                writer.setAutoFormatting(true);
                writer.writeStartElement("charactercollection");
                writer.writeAttribute("name", item->text(0));
                for (int i = 0; i < item->childCount(); ++i) {
                    QTreeWidgetItem *child = item->child(i);
                    m_pEditor->loadCharacter(child->data(0, Qt::UserRole).toInt());
                    m_pEditor->gatherStanza().toXml(&writer);
                }
                writer.writeEndElement();
            }
        }
    }
}

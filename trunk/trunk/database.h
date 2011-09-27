#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QList>
#include <QString>
#include <QPair>
#include <QVariantMap>

#include "idname.hpp"
#include "trackingcharacter.h"
#include "maneuer.h"
#include "selectmodel.h"
#include "posture.h"

//constants
static const char *ST = "st";
static const char *DX = "dx";
static const char *IQ = "iq";
static const char *HT = "ht";
static const char *WILL = "will";
static const char *PER = "per";
static const char *BS = "bs";
static const char *BM = "bm";
static const char *HP = "hp";
static const char *FP = "fp";
static const char *DODGE = "dodge";
static const char *PARRY = "parry";
static const char *BLOCK = "block";
static const char *DR_SKULL = "dr_skull";
static const char *DR_FACE = "dr_face";
static const char *DR_NECK = "dr_neck";
static const char *DR_TORSO = "dr_torso";
static const char *DR_ARMS = "dr_arms";
static const char *DR_HANDS = "dr_hands";
static const char *DR_LEGS = "dr_legs";
static const char *DR_FOOTS = "dr_foots";

static const char *NOTES = "notes";
static const char *ID = "id";
static const char *CATEGORY = "category_id";
static const char *NAME = "name";

class Database
{
    public:
        static Database * inst();
        IdNameList<IdName> getCategories();
        IdNameList<IdName> getCharacters(int nCategoryId);
        int createCategory(const QString & name);
        void deleteCategory(int nId);
        QVariantMap getCharacter(int nId);
        int saveCharacter(const QVariantMap & character);
        void deleteCharacter(int nId);
        TrackingCharacter getCharForTracking(int nId);

        QMap<int, Maneuer> maneuers();
        QMap<int, Posture> postures();

        QSqlQuery execSql(const QString & sql);

        void setupSelectModel(SelectModel *model, const QString & table,
                              const QString & IdField = "id", const QString &  NameField = "name");

    protected:
        QString escape(const QString & str);        
    private:
        Database();
        ~Database();
        QSqlDatabase m_Connection;
};

#endif // DATABASE_H

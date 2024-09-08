#include "formation.h"
#include <QSqlQuery>

#include <QTableView>
#include <QHeaderView>
FORMATION::FORMATION()
{
ID_FORMATION=0;
PRIX=0;
ID_FOR=0;
DIFICULTE="";
SPECIALITE="";
DESCRIPTION="";
TITRE="";
DATE_DEBUT=QDate::currentDate();
DATE_FIN=QDate::currentDate();
}

FORMATION::FORMATION(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR)
{

    this->ID_FORMATION=ID_FORMATION;
        this->TITRE=TITRE;
            this->SPECIALITE=SPECIALITE;
      this->DATE_DEBUT=DATE_DE_DEBUT;
        this->DATE_FIN=DATE_DE_FIN;
     this->DIFICULTE=DIFICULTE;
     this-> PRIX=PRIX;
        this->DESCRIPTION=DESCRIPTION;
      this->ID_FOR=ID_FOR;

}
int FORMATION:: getID_FORMATION(){return ID_FORMATION;}
QString FORMATION::getDESCRIPTION(){return  DESCRIPTION ;}
QDate FORMATION::getDATE_DE_DEBUT(){return DATE_DEBUT ;}
QDate FORMATION::getDATE_DE_FIN(){return DATE_FIN ;}
QString FORMATION::getDIFICULTE(){return   DIFICULTE;}
int FORMATION::getPRIX(){return  PRIX ;}
int FORMATION::getID_FOR(){return   ID_FOR;}
QString FORMATION::getSPECIALITE(){return  SPECIALITE ;}
QString FORMATION::getTITRE(){return  TITRE ;}

void FORMATION::setID_FORMATION(int ID_FORMATION) {this->ID_FORMATION=ID_FORMATION;}
void FORMATION::setDESCRIPTION(QString   DESCRIPTION){this-> DESCRIPTION= DESCRIPTION ;}
void FORMATION::setDATE_DE_DEBUT(QDate DATE_DE_DEBUT){this->DATE_DEBUT=DATE_DE_DEBUT;}
void FORMATION::setDATE_DE_FIN(QDate DATE_FIN){this->DATE_FIN=DATE_FIN;}
void FORMATION::setDIFICULTE(QString DIFICULTE){this->DIFICULTE=DIFICULTE;}
void FORMATION::setPRIX(int PRIX){this-> PRIX= PRIX;}
void FORMATION::setID_FOR(int ID_FOR){this-> ID_FOR=ID_FOR ;}
void FORMATION::setSPECIALITE(QString SPECIALITE){this->SPECIALITE=SPECIALITE;}
void FORMATION::setTITRE(QString TITRE){this->TITRE=TITRE;}

bool FORMATION::ajouter(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR)
{
    QSqlQuery query;

    query.prepare("INSERT INTO FORMATION (ID_FORMATION,TITRE,SPECIALITE,DATE_DE_DEBUT,DATE_DE_FIN,DIFFUCULTE,PRIX,DESCRIPTION,ID_FORMATEUR) "
                  "VALUES (:ID, :TITRE,:SPECIALITE, :DATE_DE_DEBUT,:DATE_DE_FIN,:DIFFICULTE , :PRIX,:DESCRIPTION, :ID_FOR)");

    query.bindValue(":ID", ID_FORMATION);
    query.bindValue(":TITRE", TITRE);
     query.bindValue(":SPECIALITE", SPECIALITE);
    query.bindValue(":DATE_DE_DEBUT", DATE_DE_DEBUT);
       query.bindValue(":DATE_DE_FIN", DATE_DE_FIN);
    query.bindValue(":DIFFICULTE", DIFICULTE);
    query.bindValue(":PRIX",PRIX);
    query.bindValue(":DESCRIPTION",DESCRIPTION);
    query.bindValue(":ID_FOR",ID_FOR);
    return query.exec();
}


QSqlQueryModel* FORMATION::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));


return model;

}



bool FORMATION::supprimer(int id)
{QSqlQuery query;
query.prepare("Delete FROM FORMATION where ID_FORMATION=:id");
query.bindValue(0,id);
return query.exec();
}

bool FORMATION::idExists(int id)
{
QSqlQuery query;
query.prepare("SELECT COUNT(*) FROM FORMATION WHERE ID_FORMATION = :id");
query.bindValue(":id", id);

if (query.exec() && query.next()) {
    int count = query.value(0).toInt();
    return count > 0;
}

return false;
}

bool FORMATION::modifier(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR)
{
QSqlQuery query;

query.prepare("UPDATE FORMATION SET  TITRE=:TITRE, SPECIALITE=:SPECIALITE , DATE_DE_DEBUT=:DATE_DE_DEBUT ,DATE_DE_FIN=:DATE_DE_FIN,DIFFUCULTE=:DIFFICULTE,PRIX=:PRIX,DESCRIPTION=:DESCRIPTION,ID_FORMATEUR=:ID_FORMATEUR  where ID_FORMATION=:ID_FORMATION");
query.bindValue(":ID_FORMATION", ID_FORMATION);
query.bindValue(":TITRE", TITRE);
query.bindValue(":SPECIALITE", SPECIALITE);
query.bindValue(":DATE_DE_DEBUT", DATE_DE_DEBUT);
query.bindValue(":DATE_DE_FIN",DATE_DE_FIN);
query.bindValue(":DIFFICULTE",DIFICULTE);
query.bindValue(":PRIX",PRIX);
query.bindValue(":DESCRIPTION",DESCRIPTION);
        query.bindValue(":ID_FORMATEUR",ID_FOR);
return query.exec();

}

QSqlQueryModel* FORMATION::tri_id_formation()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY ID_FORMATION ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
return model;
}
QSqlQueryModel* FORMATION::tri_titre()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY TITRE ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));

return model;
}

QSqlQueryModel* FORMATION::tri_specialite()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY SPECIALITE ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
return model;
}

QSqlQueryModel* FORMATION::tri_diffuculte()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY DIFFUCULTE ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
return model;
}

QSqlQueryModel* FORMATION::tri_prix()
{
QSqlQueryModel* model = new QSqlQueryModel();
model->setQuery("SELECT * FROM FORMATION ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
return model;
}


QSqlQueryModel* FORMATION::afficher_id(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE ID_FORMATION LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));

return model;
}

QSqlQueryModel* FORMATION::afficher_titre(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE TITRE LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));

return model;
}

QSqlQueryModel* FORMATION::afficher_specialite(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE SPECIALITE LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));


return model;
}

QSqlQueryModel* FORMATION::afficher_prix(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE PRIX LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));


return model;
}
QSqlQueryModel* FORMATION::afficher_diffuculte(const QString &text)
{
QSqlQueryModel* model=new QSqlQueryModel();

     model->setQuery("SELECT * FROM FORMATION WHERE DIFFUCULTE LIKE '%" + text + "%' ");
     model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
     model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
     model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
     model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
     model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
     model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFUCULTE"));
     model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
     model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
     model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));


return model;
}
int FORMATION::countType(const QString& type)
{
    int count = 0;

    QSqlQuery query;
    query.prepare("SELECT COUNT(\"SPECIALITE\") FROM FORMATION WHERE \"SPECIALITE\" = :SPECIALITE");
    query.bindValue(":SPECIALITE", type);

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }

    return count;
}



QSqlQueryModel* FORMATION::afficherd(QDate date)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM FORMATION WHERE DATE_DE_DEBUT = :date ");
    query.bindValue(":date", date);

    if (query.exec())
    {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATION"));
        model->setHeaderData(1, Qt::Horizontal,QObject:: tr("TITRE"));
        model->setHeaderData(2, Qt::Horizontal,QObject:: tr("SPECIALITE"));
        model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_DEBUT"));
        model->setHeaderData(4, Qt::Horizontal,QObject:: tr("DATE_DE_FIN"));
        model->setHeaderData(5, Qt::Horizontal,QObject:: tr("DIFFICULTE"));
        model->setHeaderData(6, Qt::Horizontal,QObject:: tr("PRIX"));
        model->setHeaderData(7, Qt::Horizontal,QObject:: tr("DESCRIPTION"));
        model->setHeaderData(8, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
    }

    return model;
}



QList<QDate> FORMATION::getDatesFromDatabase()
{
    QList<QDate> datesList;
    QSqlQuery query("SELECT DATE_DE_DEBUT FROM FORMATION");

    while (query.next())
    {
        QDate date = query.value(0).toDate();

        if (date.isValid())
        {
            datesList.append(date);
        }
    }



    return datesList;
}

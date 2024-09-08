#include "formateur.h"
#include <QTableView>
#include <QHeaderView>
#include <QSqlQuery>
#include <QDate>
FORMATEUR::FORMATEUR()
{
ID_FORMATEUR=0;
NOM="";
PRENOM="";
EXPERIENCE="";
TELEPHONE="";
EMAIL="";
SEXE="";
    PATH="";
    naissance=QDate::currentDate();
}
  FORMATEUR::FORMATEUR(int ID_FORMATEUR,QString NOM,QString PRENOM,QDate NAISSANCE,QString EMAIL,QString TELEPHONE,QString SEXE,QString EXPERIENCE,QString PATH)
   {


      this->ID_FORMATEUR=ID_FORMATEUR;
      this->NOM=NOM;
      this->PRENOM=PRENOM;
      this->naissance=NAISSANCE;
     this-> TELEPHONE=TELEPHONE;
      this->EMAIL=EMAIL;
   this->EXPERIENCE=EXPERIENCE;
         this->SEXE=SEXE;
         this->PATH=PATH;
   }

  int FORMATEUR:: getID_FORMATEUR(){return ID_FORMATEUR;}
  QString FORMATEUR::getNOM(){return  NOM ;}
  QString FORMATEUR::getPRENOM(){return PRENOM ;}
  QString FORMATEUR::getEXPERIENCE(){return   EXPERIENCE;}
  QString FORMATEUR::getTELEPHONE(){return  TELEPHONE ;}
  QString FORMATEUR::getEMAIL(){return   EMAIL;}
  QString FORMATEUR::getPATH(){return   PATH;}
  QString FORMATEUR::getSEXE(){return   SEXE;}
    QDate FORMATEUR::getnaissance(){return   naissance;}

  void FORMATEUR::setID_FORMATEUR(int ID_FORMATEUR) {this->ID_FORMATEUR=ID_FORMATEUR;}
  void FORMATEUR::setNOM(QString   NOM){this-> NOM= NOM ;}
  void FORMATEUR::setPRENOM(QString PRENOM){this->PRENOM=PRENOM;}
  void FORMATEUR::setEXPERIENCE(QString EXPERIENCE){this->EXPERIENCE=EXPERIENCE;}
  void FORMATEUR::setTELEPHONE(QString TELEPHONE){this-> TELEPHONE= TELEPHONE;}
  void FORMATEUR::setEMAIL(QString EMAIL){this-> EMAIL=EMAIL ;}
 void FORMATEUR::setPATH(QString PATH){this-> PATH=PATH ;}
 void FORMATEUR::setSEXE(QString SEXE){this-> SEXE=SEXE ;}
  void FORMATEUR::setnaissance(QDate naissance){this-> naissance=naissance ;}

  bool FORMATEUR::ajouter()
  {
      QSqlQuery query;

      query.prepare("INSERT INTO FORMATEUR (ID_FORMATEUR,NOM,PRENOM,DATE_DE_NAISSANCE,EMAIL,TELEPHONE,SEXE,EXPERIENCE,IMAGE_PATH) "
                    "VALUES (:ID_FORMATEUR, :NOM, :PRENOM, :DATE_DE_NAISSANCE, :EMAIL, :TELEPHONE,:SEXE,:EXPERIENCE,:IMAGE_PATH)");

      query.bindValue(":ID_FORMATEUR", ID_FORMATEUR);
      query.bindValue(":NOM", NOM);
      query.bindValue(":PRENOM", PRENOM);
      query.bindValue(":DATE_DE_NAISSANCE", naissance);
      query.bindValue(":EMAIL",EMAIL);
       query.bindValue(":TELEPHONE",TELEPHONE);
        query.bindValue(":SEXE",SEXE);
         query.bindValue(":EXPERIENCE",EXPERIENCE);
          query.bindValue(":IMAGE_PATH",PATH);


      return query.exec();
  }


  QSqlQueryModel* FORMATEUR::afficher()
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
       model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
       model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));

  return model;

  }



  bool FORMATEUR::supprimer(int id)
  {QSqlQuery query;
  query.prepare("Delete FROM FORMATEUR where ID_FORMATEUR=:id");
  query.bindValue(0,id);
  return query.exec();
  }

  bool FORMATEUR::idExists(int id)
  {
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM FORMATEUR WHERE ID_FORMATEUR = :id");
  query.bindValue(":id", id);

  if (query.exec() && query.next()) {
      int count = query.value(0).toInt();
      return count > 0;
  }

  return false;
  }

  bool FORMATEUR::modifier(int ID_FORMATEUR,QString NOM,QString PRENOM,QDate NAISSANCE,QString EMAIL,QString TELEPHONE,QString SEXE,QString EXPERIENCE,QString PATH)
  {
  QSqlQuery query;


  query.prepare("UPDATE FORMATEUR SET NOM=:NOM , PRENOM=:PRENOM, DATE_DE_NAISSANCE=:DATE_DE_NAISSANCE , EMAIL=:EMAIL ,TELEPHONE=:TELEPHONE,SEXE=:SEXE,EXPERIENCE=:EXPERIENCE,IMAGE_PATH=:IMAGE_PATH  where ID_FORMATEUR=:ID_FORMATEUR");

  query.bindValue(":ID_FORMATEUR", ID_FORMATEUR);
  query.bindValue(":NOM", NOM);
  query.bindValue(":PRENOM", PRENOM);
  query.bindValue(":DATE_DE_NAISSANCE", NAISSANCE);
  query.bindValue(":EMAIL",EMAIL);
   query.bindValue(":TELEPHONE",TELEPHONE);
    query.bindValue(":SEXE",SEXE);
     query.bindValue(":EXPERIENCE",EXPERIENCE);
      query.bindValue(":IMAGE_PATH",PATH);


 return query.exec();


  }

  QSqlQueryModel* FORMATEUR::tri_nom()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY NOM ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
  model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
  model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
  model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));


  return model;
  }
  QSqlQueryModel* FORMATEUR::tri_id()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY ID_FORMATEUR ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
  model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
  model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
  model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));

  return model;
  }

  QSqlQueryModel* FORMATEUR::tri_telephone()
  {
  QSqlQueryModel* model = new QSqlQueryModel();
  model->setQuery("SELECT * FROM FORMATEUR ORDER BY TELEPHONE ASC");
  model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
  model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
  model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
  model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
  model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
  model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
  model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
  model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
  model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));


  return model;
  }


  QSqlQueryModel* FORMATEUR::afficher_nom(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE NOM LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
       model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
       model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));
  return model;
  }

  QSqlQueryModel* FORMATEUR::afficher_id(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE ID_FORMATEUR LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
       model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
       model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));
  return model;
  }

  QSqlQueryModel* FORMATEUR::afficher_telephone(const QString &text)
  {
  QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT * FROM FORMATEUR WHERE TELEPHONE LIKE '%" + text + "%' ");
       model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_FORMATEUR"));
       model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
       model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_DE_NAISSANCE"));
       model->setHeaderData(4, Qt::Horizontal,QObject:: tr("EMAIL"));
       model->setHeaderData(5, Qt::Horizontal,QObject:: tr("TELEPHONE"));
       model->setHeaderData(6, Qt::Horizontal,QObject:: tr("SEXE"));
       model->setHeaderData(7, Qt::Horizontal,QObject:: tr("EXPERIENCE"));
       model->setHeaderData(8, Qt::Horizontal,QObject:: tr("IMAGE_PATH"));


  return model;
  }

  int FORMATEUR::countType(const QString& type)
  {
      int count = 0;

      QSqlQuery query;
      query.prepare("SELECT COUNT(\"EXPERIENCE\") FROM FORMATEUR WHERE \"EXPERIENCE\" = :EXPERIENCE");
      query.bindValue(":EXPERIENCE", type);

      if (query.exec() && query.next()) {
          count = query.value(0).toInt();
      }

      return count;
  }




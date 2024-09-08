#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class FORMATION
{
public:
    FORMATION();
  FORMATION(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR);

    int getID_FORMATION();
    void setID_FORMATION(int);

    int getPRIX();
    void setPRIX(int);
    int getID_FOR();
    void setID_FOR(int);
    QString getDIFICULTE();
    void setDIFICULTE(QString);
    QString getTITRE();
    void setTITRE(QString);
    QString getSPECIALITE();
    void setSPECIALITE(QString);
    QString getTYPE();
    void setTYPE(QString);
    QDate getDATE_DE_DEBUT();
    void setDATE_DE_DEBUT(QDate);
    QDate getDATE_DE_FIN();
    void setDATE_DE_FIN(QDate);
    QString getDESCRIPTION();
    void setDESCRIPTION(QString);

    bool ajouter(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR);
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier(int ID_FORMATION,QString TITRE,QString SPECIALITE,QDate DATE_DE_DEBUT,QDate DATE_DE_FIN,QString DIFICULTE,int PRIX,QString DESCRIPTION,int ID_FOR);

    //metier
    QSqlQueryModel* tri_id_formation();
        QSqlQueryModel* tri_titre();
            QSqlQueryModel* tri_specialite();
            QSqlQueryModel* tri_diffuculte();
                QSqlQueryModel* tri_prix();
            int countType(const QString& type);
             QSqlQueryModel* afficher_id(const QString &text);
              QSqlQueryModel* afficher_specialite(const QString &text);
               QSqlQueryModel* afficher_titre(const QString &text);
               QSqlQueryModel* afficher_diffuculte(const QString &text);
                QSqlQueryModel* afficher_prix(const QString &text);
               //metier avance
               QList<QDate> getDatesFromDatabase();
               QSqlQueryModel* afficherd(QDate date);
private:
 int ID_FORMATION,ID_FOR,PRIX;
 QString SPECIALITE,DIFICULTE,TITRE,DESCRIPTION;
 QDate DATE_DEBUT,DATE_FIN;


};

#endif // FORMATION_H

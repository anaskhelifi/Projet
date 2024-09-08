#ifndef FORMATEUR_H
#define FORMATEUR_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
class FORMATEUR
{
public:
    FORMATEUR();
    FORMATEUR(int,QString,QString,QDate,QString,QString,QString,QString,QString);

    int getID_FORMATEUR();
    void setID_FORMATEUR(int);

    QString getNOM();
    void setNOM(QString);
    QString getPRENOM();
    void setPRENOM(QString);
    QString getEXPERIENCE();
    void setEXPERIENCE(QString);
    QString getTELEPHONE();
    void setTELEPHONE(QString);
    QString getEMAIL();
    void setEMAIL(QString);


    QString getPATH();
    void setPATH(QString);
    QString getSEXE();
    void setSEXE(QString);
   void setnaissance(QDate);
    QDate getnaissance();

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool idExists(int id);
    bool modifier(int ID_FORMATEUR,QString NOM,QString PRENOM,QDate NAISSANCE,QString EMAIL,QString TELEPHONE,QString SEXE,QString EXPERIENCE,QString PATH);

    //metier
    QSqlQueryModel* tri_nom();
        QSqlQueryModel* tri_id();
            QSqlQueryModel* tri_telephone();
            int countType(const QString& type);
             QSqlQueryModel* afficher_nom(const QString &text);
              QSqlQueryModel* afficher_id(const QString &text);
               QSqlQueryModel* afficher_telephone(const QString &text);


private:
int ID_FORMATEUR;
QString NOM,PRENOM,TELEPHONE,EMAIL,SEXE,PATH,EXPERIENCE;
QDate naissance;
};

#endif // FORMATEUR_H

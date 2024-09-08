#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include <QPainter>

#include <QPieSeries>
#include <QChartView>
#include <QChart>
#include <QPieSlice>
#include <QDebug>
#include "email.h"
#include <QSqlQuery>
using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     ui->tableView_formateur->setModel(fr.afficher());
ui->path_picture->hide();
GESTION_FORMATEUR_STATISTIQUE();
   ui->tableView_formation->setModel(f.afficher());
ui->metier_email->hide();
ui->gestion_formateur->hide();
ui->gestion_formation->hide();
ui->calendrier->hide();
ui->menu->show();
remplir_comobo_id_formateur_gestion_formation();
GESTION_FORMATION_STATISTIQUE();


ui->date_fin->setDate(QDate::currentDate());
ui->date_debut->setDate(QDate::currentDate());
//calendrier

   QCalendarWidget* calendarWidget = ui->calendarWidget;

   // Clear existing date text formats
   calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

   QList<QDate> datesList = f.getDatesFromDatabase();

   for (const QDate& targetDate : datesList)
   {
       QTextCharFormat format = calendarWidget->dateTextFormat(targetDate); //yemchy lel calendrier bch ye5oo el text mta el date hakyyy (targetdate)
       format.setForeground(Qt::blue);   // bch ibedl el couleur   du text fel date haky iredo white
       calendarWidget->setDateTextFormat(targetDate, format);   // bch yraj3 ell date , o text mta3ha el jdid
   }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_formateur_clicked()
{int x=0;//nb  du faute dans controle saisie
  int ID_FORMATEUR=ui->ID_formateur->text().toInt();
  QString NOM=ui->nom_formateur->text();
  QString PRENOM=ui->prenom_formateur->text();
  QString Sexe=ui->Sexe->currentText();
  QString phone=ui->phone->text();
  QString email=ui->email->text();
QDate naissance=ui->date_naissance_formateur->date();
QString experience=ui->experience->currentText();
QString path=ui->path_picture->text();
  //controle de saisie
  if(fr.idExists(ID_FORMATEUR))
  {
      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
      return;

  }
  if(ID_FORMATEUR==0  )
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
      return;
  }
  if(ui->ID_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
      return;
  }


  if(ui->nom_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
      return;
  }
  if(ui->prenom_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
      return;
  }

  // numero de telephone 8 chiffre

  if (phone.length() != 8)
  {
      QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres."), QMessageBox::Cancel);
      return;
  }

  if (!phone.contains(QRegularExpression("^\\d+$")))
  {
      QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro ne doit contenir que des chiffres."), QMessageBox::Cancel);
      return;
  }


//aa@aa.aa
  // Vérifier si l'e-mail est valide
  QRegularExpression emailRegex("\\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}\\b");
  QRegularExpressionMatch match = emailRegex.match(email);
  if (!match.hasMatch())
  {
  QMessageBox::critical(nullptr, QObject::tr("Email invalide"), QObject::tr("Le format de l'e-mail est invalide. Veuillez entrer un e-mail valide."), QMessageBox::Cancel);
  return;
  }

  if(x==0) //si il n' y a pas problem dans le controle de saisie
  {FORMATEUR FR(ID_FORMATEUR,NOM,PRENOM,naissance,email,phone,Sexe,experience,path);

  bool test=FR.ajouter();
     QMessageBox msgBox;
     if(test)
      {msgBox.setText("Ajout avec succes.");
            ui->tableView_formateur->setModel(FR.afficher());
GESTION_FORMATEUR_STATISTIQUE();
remplir_comobo_id_formateur_gestion_formation();
            ui->ID_formateur->clear();
       ui->nom_formateur->clear();
      ui->prenom_formateur->clear();
       ui->phone->clear();
    ui->email->clear();
     ui->path_picture->clear();
      ui->show_picture->clear();
         msgBox.exec();
      }

      else
          msgBox.setText("echec d'ajout");

     msgBox.exec();

  }





}

void MainWindow::on_modifier_formateur_clicked()
{
    int x=0;//nb  du faute dans controle saisie
    int ID_FORMATEUR=ui->ID_formateur->text().toInt();
    QString NOM=ui->nom_formateur->text();
    QString PRENOM=ui->prenom_formateur->text();
    QString Sexe=ui->Sexe->currentText();
    QString phone=ui->phone->text();
    QString email=ui->email->text();
  QDate naissance=ui->date_naissance_formateur->date();
  QString experience=ui->experience->currentText();
  QString path=ui->path_picture->text();

  //controle de saisie
  if(fr.idExists(ID_FORMATEUR)==false)
  {
      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID n' existe pas "), QMessageBox::Ok);
      return;

  }
  if(ID_FORMATEUR==0  )
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
      return;
  }
  if(ui->ID_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
      return;
  }


  if(ui->nom_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
      return;
  }
  if(ui->prenom_formateur->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
      return;
  }

  // numero de telephone 8 chiffre

  if (phone.length() != 8)
  {
      QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro doit contenir 8 chiffres."), QMessageBox::Cancel);
      return;
  }

  if (!phone.contains(QRegularExpression("^\\d+$")))
  {
      QMessageBox::critical(nullptr, QObject::tr("Numéro invalide"), QObject::tr("Le numéro ne doit contenir que des chiffres."), QMessageBox::Cancel);
      return;
  }
        if(x==0) //si il n' y a pas problem dans le controle de saisie
        {

        bool test=fr.modifier(ID_FORMATEUR,NOM,PRENOM,naissance,email,phone,Sexe,experience,path);
           QMessageBox msgBox;
           if(test)
            {msgBox.setText("modification avec succes.");
GESTION_FORMATEUR_STATISTIQUE();
                     ui->tableView_formateur->setModel(fr.afficher());


                     ui->ID_formateur->clear();
                ui->nom_formateur->clear();
               ui->prenom_formateur->clear();
                ui->phone->clear();
             ui->email->clear();
              ui->path_picture->clear();
              ui->show_picture->clear();
                  msgBox.exec();


            }

            else
                msgBox.setText("echec d'ajout");
            msgBox.exec();


        }
    }


void MainWindow::on_Supprimer_formateur_clicked()
{

        int id=ui->id_supprimer_formateur->text().toInt();
     QMessageBox msgBox;

        if(fr.idExists(id)==false)
        {

           QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID n existe pas"), QMessageBox::Ok);
           return;

        }
        else
        {
    bool test = fr.supprimer(id);


            if (test) {
         ui->tableView_formateur->setModel(fr.afficher());
remplir_comobo_id_formateur_gestion_formation();
                    msgBox.setText("Suppression avec succées.");
                    GESTION_FORMATEUR_STATISTIQUE();
                }
             else {
                msgBox.setText("Échec de la suppression.");

            }
        }
            msgBox.exec();

}

void MainWindow::on_PDF_clicked()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_formateur->model()->rowCount();
    const int columnCount = ui->tableView_formateur->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des FORMATEURS</H1></center><br/><br/>\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_formateur->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_formateur->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_formateur->isColumnHidden(column))
            {
                QString data = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void MainWindow::on_TRI_formateur_clicked()
{
    if(ui->Trier_selon_formateur->currentIndex()==0)
      {

          ui->tableView_formateur->setModel(fr.tri_id());
     }
      if(ui->Trier_selon_formateur->currentText()==1)
      {
          ui->tableView_formateur->setModel(fr.tri_nom());
     }
      if(ui->Trier_selon_formateur->currentText()==2)
      {
          ui->tableView_formateur->setModel(fr.tri_telephone());
     }
           // Adjust the header view as needed
         QHeaderView* headerView = ui->tableView_formateur->horizontalHeader();
           headerView->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_bt_chercher_formateur_clicked()
{
 QString text=ui->chercher_formateur->text();
    if(ui->Trier_selon_formateur->currentText()=="ID")
     {    ui->tableView_formateur->setModel( fr.afficher_id(text));
         }
     if(ui->Trier_selon_formateur->currentText()=="NOM")
     {     ui->tableView_formateur->setModel( fr.afficher_nom(text));
     }

     if(ui->Trier_selon_formateur->currentText()=="TELEPHONE")
     {    ui->tableView_formateur->setModel( fr.afficher_telephone(text));
 }

}

void MainWindow::on_afficher_formateur_clicked()
{
    ui->chercher_formateur->clear();
     ui->tableView_formateur->setModel( fr.afficher());
}

void MainWindow::on_formateur_to_calendrier_clicked()
{
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->hide();
    ui->calendrier->show();
}

void MainWindow::on_choose_picture_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

    if (!imagePath.isEmpty()) {
        // Load the image using QPixmap
        QPixmap image(imagePath);

        // Update the QLabel with the image
        ui->show_picture->setPixmap(image.scaled(ui->show_picture->size(), Qt::KeepAspectRatio));
        ui->path_picture->setText(imagePath);
        ui->path_picture->hide();
    }
}

void MainWindow::on_formateur_to_formation_clicked()
{
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->show();
    ui->gestion_formation->hide();
    ui->calendrier->hide();
}

void MainWindow::on_formation_to_menu_clicked()
{
    ui->menu->show();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->hide();
    ui->calendrier->hide();
}

void MainWindow::on_menu_to_formation_clicked()
{
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->show();
    ui->calendrier->hide();
}

void MainWindow::on_menu_to_formateur_clicked()
{
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->show();
    ui->gestion_formation->hide();
    ui->calendrier->hide();
}

void MainWindow::on_menu_to_quitter_clicked()
{
    this->close();
}

void MainWindow::on_formateur_to_menu_clicked()
{
    ui->menu->show();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->hide();
    ui->calendrier->hide();
}

void MainWindow::on_calendrier_to_formateur_clicked()
{
    ui->calendrier->hide();
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->show();

}

void MainWindow::on_formation_to_email_clicked()
{
    ui->menu->hide();
    ui->metier_email->show();
    ui->gestion_formateur->hide();
    ui->gestion_formation->hide();
    ui->calendrier->hide();
}

void MainWindow::on_email_to_formation_clicked()
{
    ui->menu->hide();
    ui->metier_email->hide();
    ui->gestion_formateur->hide();
    ui->gestion_formation->show();
    ui->calendrier->hide();
}

void MainWindow::GESTION_FORMATEUR_STATISTIQUE()
{
    QList<QWidget*> childWidgets = ui->label_statistuque_formateur->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_statistuque_formateur->clear();
        ui->label_statistuque_formateur->hide();

    int s0, s1,s2,s3;

    s0 = fr.countType("0");
    s1 = fr.countType("1-3");
    s2 = fr.countType("4-10");
    s3 = fr.countType("+10");



    int stat = s0 + s1 + s2 + s3 ;
    // Calculate percentages
        float x = (stat != 0) ? (s0 * 100.0f) / stat : 0.0f;
        float x1 = (stat != 0) ? (s1 * 100.0f) / stat : 0.0f;
        float x2 = (stat != 0) ? (s2 * 100.0f) / stat : 0.0f;
   float x3 = (stat != 0) ? (s3 * 100.0f) / stat : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2+x3  ;
        if (totalPercentage != 100.0f && stat != 0) {
            float correction = 100.0f - totalPercentage;   //100 - 99.99 = 0.01
            x += correction;
        }


//0 33.00%
    QString ch1 = QString("[0] %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("[1-3] %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("[4-10] %3%").arg(QString::number(x2, 'f', 2));
    QString ch4 = QString("[+10] %4%").arg(QString::number(x3, 'f', 2));



    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
        slice->setBrush(QColor(189, 76, 224, 1));

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));

    QPieSlice *slice3= series->append(ch4,x3);
    slice3->setLabelVisible();
    slice3->setLabelColor(QColor(Qt::white));
    slice3->setBrush(QColor(77, 76, 125));




    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_statistuque_formateur->size());
    chartview->setParent(ui->label_statistuque_formateur);
    ui->label_statistuque_formateur->setStyleSheet("background:transparent; color:white; ");
    ui->label_statistuque_formateur->show();

}

void MainWindow::on_envoyer_clicked()
{
    mailer::sendEmail(ui->destinataireEmail->text(), ui->objetEmail->text(), ui->bodyEmail->text());
}

void MainWindow::on_tableView_formateur_clicked(const QModelIndex &index)
{
QString id=ui->tableView_formateur->model()->data(index).toString();
QSqlQuery qry;
qry.prepare("SELECT * FROM FORMATEUR WHERE ID_FORMATEUR='" + id +"'");
if(qry.exec())
{
while(qry.next())
{
QString id= qry.value(0).toString();
QString nom =qry.value(1).toString();
QString prenom=qry.value(2).toString();
QDate naissance=qry.value(3).toDate();
QString email=qry.value(4).toString();
QString numero=qry.value(5).toString();
QString Sexe=qry.value(6).toString();
QString experience=qry.value(7).toString();
QString Path=qry.value(8).toString();

ui->ID_formateur->setText(id);
ui->nom_formateur->setText(nom);
ui->prenom_formateur->setText(prenom);

ui->phone->setText(numero);
ui->email->setText(email);
ui->date_naissance_formateur->setDate(naissance);

ui->path_picture->setText(Path);
if(Sexe=="HOMME")
ui->Sexe->setCurrentIndex(0);
else
ui->Sexe->setCurrentIndex(1);

if(experience=="1-3")
    ui->experience->setCurrentIndex(1);
if(experience=="4-10")
    ui->experience->setCurrentIndex(2);
if(experience=="+10")
    ui->experience->setCurrentIndex(3);

if (!Path.isEmpty()) {
    // Load the image using QPixmap
    QPixmap image(Path);

 ui->show_picture->setPixmap(image.scaled(ui->show_picture->size(), Qt::KeepAspectRatio));
  ui->show_picture->show();
}


}
}



}

void MainWindow::on_ajouter_formation_clicked()
{int x=0;//nb  du faute dans controle saisie
  int ID_FORMATION=ui->ID_FORMATION->text().toInt();
  QString TITRE=ui->TITRE->text();

  QString SPECIALITE=ui->specialite->currentText();
  QDate debut=ui->date_debut->date();
  QDate fin=ui->date_fin->date();
 int index=ui->difficulte->currentIndex();
 QString diffuculte=QString::number(index);
  int prix=ui->prix->text().toInt();
  QString description=ui->descrption->text();
int ID_FORMATEUR=ui->combo_id_formateur->currentText().toInt();


  //controle de saisie
  if(f.idExists(ID_FORMATION))
  {
      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
      return;

  }
  if(ID_FORMATION==0  )
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
      return;
  }
  if(ui->ID_FORMATION->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
      return;
  }


  if(ui->TITRE->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
      return;
  }
  if(ui->prix->text().isEmpty())
  {

      x++;
      QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
      return;
  }


if(debut>=fin )
{

    x++;
    QMessageBox::warning(nullptr, QObject::tr("Invalide date"), QObject::tr("la date de debut doit etre avant la date du fin"), QMessageBox::Ok);
    return;
}

  if(x==0) //si il n' y a pas problem dans le controle de saisie
  {

  bool test=f.ajouter(ID_FORMATION,TITRE,SPECIALITE,debut,fin,diffuculte,prix,description,ID_FORMATEUR);
     QMessageBox msgBox;
     if(test)
      {msgBox.setText("Ajout avec succes.");
            ui->tableView_formation->setModel(f.afficher());


            ui->ID_FORMATION->clear();
       ui->TITRE->clear();
       ui->date_fin->setDate(QDate::currentDate());
       ui->date_debut->setDate(QDate::currentDate());
    ui->prix->clear();
     ui->descrption->clear();


     //calendrier

        QCalendarWidget* calendarWidget = ui->calendarWidget;

        // Clear existing date text formats
        calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

        QList<QDate> datesList = f.getDatesFromDatabase();

        for (const QDate& targetDate : datesList)
        {
            QTextCharFormat format = calendarWidget->dateTextFormat(targetDate); //yemchy lel calendrier bch ye5oo el text mta el date hakyyy (targetdate)
            format.setForeground(Qt::blue);   // bch ibedl el couleur   du text fel date haky iredo white
            calendarWidget->setDateTextFormat(targetDate, format);   // bch yraj3 ell date , o text mta3ha el jdid
        }


      }

      else
          msgBox.setText("echec d'ajout");

     msgBox.exec();

  }
GESTION_FORMATION_STATISTIQUE();
}

void MainWindow::on_modifier_formation_clicked()
{
    int x=0;//nb  du faute dans controle saisie
      int ID_FORMATION=ui->ID_FORMATION->text().toInt();
      QString TITRE=ui->TITRE->text();

      QString SPECIALITE=ui->specialite->currentText();
      QDate debut=ui->date_debut->date();
      QDate fin=ui->date_fin->date();
     int index=ui->difficulte->currentIndex();
     QString diffuculte=QString::number(index);
      int prix=ui->prix->text().toInt();
      QString description=ui->descrption->text();
    int ID_FORMATEUR=ui->combo_id_formateur->currentText().toInt();


      //controle de saisie
      if(f.idExists(ID_FORMATION)==false)
      {
          x++;
          QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID deja existe"), QMessageBox::Ok);
          return;

      }
      if(ID_FORMATION==0  )
      {

          x++;
          QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ne mets pas 0"), QMessageBox::Ok);
          return;
      }
      if(ui->ID_FORMATION->text().isEmpty())
      {

          x++;
          QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("tu ne peux pas mettre une pièce d'identité vide"), QMessageBox::Ok);
          return;
      }


      if(ui->TITRE->text().isEmpty())
      {

          x++;
          QMessageBox::warning(nullptr, QObject::tr("Invalide nom"), QObject::tr("tu ne peux pas mettre une nom vide"), QMessageBox::Ok);
          return;
      }
      if(ui->prix->text().isEmpty())
      {

          x++;
          QMessageBox::warning(nullptr, QObject::tr("Invalide prenom"), QObject::tr("tu ne peux pas mettre une prenom vide"), QMessageBox::Ok);
          return;
      }


    if(debut>=fin )
    {

        x++;
        QMessageBox::warning(nullptr, QObject::tr("Invalide date"), QObject::tr("la date de debut doit etre avant la date du fin"), QMessageBox::Ok);
        return;
    }

      if(x==0) //si il n' y a pas problem dans le controle de saisie
      {

      bool test=f.modifier(ID_FORMATION,TITRE,SPECIALITE,debut,fin,diffuculte,prix,description,ID_FORMATEUR);
         QMessageBox msgBox;
         if(test)
          {msgBox.setText("modification avec succes.");
                ui->tableView_formation->setModel(f.afficher());


                ui->ID_FORMATION->clear();
           ui->TITRE->clear();
           ui->date_fin->setDate(QDate::currentDate());
           ui->date_debut->setDate(QDate::currentDate());
        ui->prix->clear();
         ui->descrption->clear();


         //calendrier

            QCalendarWidget* calendarWidget = ui->calendarWidget;

            // Clear existing date text formats
            calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

            QList<QDate> datesList = f.getDatesFromDatabase();

            for (const QDate& targetDate : datesList)
            {
                QTextCharFormat format = calendarWidget->dateTextFormat(targetDate); //yemchy lel calendrier bch ye5oo el text mta el date hakyyy (targetdate)
                format.setForeground(Qt::blue);   // bch ibedl el couleur   du text fel date haky iredo white
                calendarWidget->setDateTextFormat(targetDate, format);   // bch yraj3 ell date , o text mta3ha el jdid
            }


          }

          else
              msgBox.setText("echec d'ajout");

         msgBox.exec();

      }
      GESTION_FORMATION_STATISTIQUE();
}
void MainWindow::remplir_comobo_id_formateur_gestion_formation()
{
//repetition
ui->combo_id_formateur->clear();
    QSqlQuery query;
        query.exec("SELECT ID_FORMATEUR FROM FORMATEUR");
        while (query.next()) {
            QString ID = query.value(0).toString();
            ui->combo_id_formateur->addItem(ID);

        }
}

void MainWindow::on_bt_supprimer_formation_clicked()
{
    int id=ui->id_supprimer_formation->text().toInt();
 QMessageBox msgBox;

    if(f.idExists(id)==false)
    {

       QMessageBox::warning(nullptr, QObject::tr("Invalide ID"), QObject::tr("ID n existe pas"), QMessageBox::Ok);
       return;

    }
    else
    {
bool test = f.supprimer(id);


        if (test) {
     ui->tableView_formation->setModel(f.afficher());

                msgBox.setText("Suppression avec succées.");
                //calendrier

                   QCalendarWidget* calendarWidget = ui->calendarWidget;

                   // Clear existing date text formats
                   calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

                   QList<QDate> datesList = f.getDatesFromDatabase();

                   for (const QDate& targetDate : datesList)
                   {
                       QTextCharFormat format = calendarWidget->dateTextFormat(targetDate); //yemchy lel calendrier bch ye5oo el text mta el date hakyyy (targetdate)
                       format.setForeground(Qt::blue);   // bch ibedl el couleur   du text fel date haky iredo white
                       calendarWidget->setDateTextFormat(targetDate, format);   // bch yraj3 ell date , o text mta3ha el jdid
                   }

            }
         else {
            msgBox.setText("Échec de la suppression.");

        }
    }
        msgBox.exec();
GESTION_FORMATION_STATISTIQUE();
}

void MainWindow::on_PDF_formation_clicked()
{

    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->tableView_formation->model()->rowCount();
    const int columnCount = ui->tableView_formation->model()->columnCount();

    out << "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
           "<title>%1</title>\n"
           "<style>\n"
           "table {\n"
           "    width: 100%;\n"
           "    border-collapse: collapse;\n"
           "}\n"
           "th, td {\n"
           "    padding: 8px;\n"
           "    text-align: left;\n"
           "    border-bottom: 1px solid #ddd;\n"
           "}\n"
           "tr:nth-child(even) {\n"
           "    background-color: #f2f2f2;\n"
           "}\n"
           "</style>\n"
           "</head>\n"
           "<body bgcolor=#ffffff link=#5000A0>\n"
           "<center> <H1>Liste des Formations</H1></center><br/><br/>\n"
           "<table>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
    {
        if (!ui->tableView_formation->isColumnHidden(column))
        {
            out << QString("<th>%1</th>").arg(ui->tableView_formation->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tableView_formation->isColumnHidden(column))
            {
                QString data = ui->tableView_formation->model()->data(ui->tableView_formation->model()->index(row, column)).toString().simplified();
                out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }



    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}
void MainWindow::on_afficher_formation_clicked()
{
     ui->tableView_formation->setModel(f.afficher());
     ui->lineedit_chercher_formation->clear();
     GESTION_FORMATION_STATISTIQUE();
}

void MainWindow::on_chercher_formation_clicked()
{
    QString text=ui->lineedit_chercher_formation->text();
    if(ui->Trier_selon_formation->currentText()=="ID")
         ui->tableView_formation->setModel(f.afficher_id(text));
    if(ui->Trier_selon_formation->currentText()=="TITRE")
         ui->tableView_formation->setModel(f.afficher_titre(text));
    if(ui->Trier_selon_formation->currentText()=="SPECIALITE")
         ui->tableView_formation->setModel(f.afficher_specialite(text));
    if(ui->Trier_selon_formation->currentText()=="PRIX")
         ui->tableView_formation->setModel(f.afficher_prix(text));
    if(ui->Trier_selon_formation->currentText()=="DIFFICULTE")
         ui->tableView_formation->setModel(f.afficher_diffuculte(text));
}

void MainWindow::on_trier_formation_clicked()
{

    if(ui->Trier_selon_formation->currentText()=="ID")
         ui->tableView_formation->setModel(f.tri_id_formation());
    if(ui->Trier_selon_formation->currentText()=="TITRE")
         ui->tableView_formation->setModel(f.tri_titre());
    if(ui->Trier_selon_formation->currentText()=="SPECIALITE")
         ui->tableView_formation->setModel(f.tri_specialite());
    if(ui->Trier_selon_formation->currentText()=="PRIX")
         ui->tableView_formation->setModel(f.tri_prix());
    if(ui->Trier_selon_formation->currentText()=="DIFFICULTE")
         ui->tableView_formation->setModel(f.tri_diffuculte());
}

void MainWindow::on_tableView_formation_clicked(const QModelIndex &index)
{
QString id=ui->tableView_formation->model()->data(index).toString();
QSqlQuery qry;
qry.prepare("SELECT * FROM FORMATION WHERE ID_FORMATION='" + id +"'");
if(qry.exec())
{
while(qry.next())
{
QString id= qry.value(0).toString();
QString titre =qry.value(1).toString();
QString specialite=qry.value(2).toString();
QDate debut=qry.value(3).toDate();
QDate fin=qry.value(4).toDate();
QString DIFFICULTE=qry.value(5).toString();
QString PRIX=qry.value(6).toString();
QString DESCRIPTION=qry.value(7).toString();
QString ID_FORMATEUR=qry.value(8).toString();

ui->ID_FORMATION->setText(id);
ui->TITRE->setText(titre);

ui->date_debut->setDate(debut);
ui->date_fin->setDate(fin);
ui->descrption->setText(DESCRIPTION);
ui->prix->setText(PRIX);

if(specialite=="Mecanique")
ui->specialite->setCurrentIndex(0);
if(specialite=="Electronique")
ui->specialite->setCurrentIndex(1);
if(specialite=="Automatisme industriel")
ui->specialite->setCurrentIndex(2);
if(specialite=="Genie civil")
ui->specialite->setCurrentIndex(3);

if(DIFFICULTE=="0")
    ui->difficulte->setCurrentIndex(0);
if(DIFFICULTE=="1")
    ui->difficulte->setCurrentIndex(1);
if(DIFFICULTE=="2")
    ui->difficulte->setCurrentIndex(2);

if(DIFFICULTE=="3")
    ui->difficulte->setCurrentIndex(3);
if(DIFFICULTE=="4")
    ui->difficulte->setCurrentIndex(4);
if(DIFFICULTE=="5")
    ui->difficulte->setCurrentIndex(5);

// Set ID_FORMATEUR in combo box
           int formateurIndex = ui->combo_id_formateur->findText(ID_FORMATEUR);
               ui->combo_id_formateur->setCurrentIndex(formateurIndex);





}


}


}



void MainWindow::GESTION_FORMATION_STATISTIQUE()
{
    QList<QWidget*> childWidgets = ui->label_statistuque_formation->findChildren<QWidget*>();
        for (QWidget* childWidget : childWidgets) {
            childWidget->deleteLater();

        }
        //the clear didnt work, but my goal is when i second click this button it deleted old chart and renders a new one
        ui->label_statistuque_formation->clear();
        ui->label_statistuque_formation->hide();

    int s0, s1,s2,s3;

    s0 = f.countType("Mecanique");
    s1 = f.countType("Electronique");
    s2 = f.countType("Automatisme industriel");
    s3 = f.countType("Genie civil");



    int stat = s0 + s1 + s2 + s3 ;
    // Calculate percentages
        float x = (stat != 0) ? (s0 * 100.0f) / stat : 0.0f;
        float x1 = (stat != 0) ? (s1 * 100.0f) / stat : 0.0f;
        float x2 = (stat != 0) ? (s2 * 100.0f) / stat : 0.0f;
   float x3 = (stat != 0) ? (s3 * 100.0f) / stat : 0.0f;


        // Adjust the percentages to ensure they sum up to 100%
        float totalPercentage = x + x1+ x2+x3  ;
        if (totalPercentage != 100.0f && stat != 0) {
            float correction = 100.0f - totalPercentage;   //100 - 99.99 = 0.01
            x += correction;
        }


//0 33.00%
    QString ch1 = QString("Mecanique %1%").arg(QString::number(x, 'f', 2));
    QString ch2 = QString("Electronique %2%").arg(QString::number(x1, 'f', 2));
    QString ch3 = QString("Automatisme %3%").arg(QString::number(x2, 'f', 2));
    QString ch4 = QString("Genie %4%").arg(QString::number(x3, 'f', 2));



    QPieSeries *series=new QPieSeries();
    series->setHoleSize(0.35);

    QPieSlice *slice= series->append(ch1,x);
    slice->setLabelVisible();
    slice->setLabelColor(QColor(Qt::white));
        slice->setBrush(QColor(189, 76, 224, 1));

    QPieSlice *slice1= series->append(ch2,x1);
    slice1->setLabelVisible();
    slice1->setLabelColor(QColor(Qt::white));
    slice1->setBrush(QColor(84, 16, 149, 1));

    QPieSlice *slice2= series->append(ch3,x2);
    slice2->setLabelVisible();

    slice2->setLabelColor(QColor(Qt::white));
    slice2->setBrush(QColor(119, 82, 254));

    QPieSlice *slice3= series->append(ch4,x3);
    slice3->setLabelVisible();
    slice3->setLabelColor(QColor(Qt::white));
    slice3->setBrush(QColor(77, 76, 125));




    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBrush backgroundBrush(QColor(187,93,87,0));
    chart->setBackgroundBrush(backgroundBrush);
    QChartView *chartview=new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setFixedSize(ui->label_statistuque_formation->size());
    chartview->setParent(ui->label_statistuque_formation);
    ui->label_statistuque_formation->setStyleSheet("background:transparent; color:white; ");
    ui->label_statistuque_formation->show();

}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
      ui->tableView_calendrier->setModel(f.afficherd(date));
}

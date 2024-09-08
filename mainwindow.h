#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formateur.h"
#include "formation.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_formateur_clicked();

    void on_modifier_formateur_clicked();

    void on_Supprimer_formateur_clicked();

    void on_PDF_clicked();

    void on_TRI_formateur_clicked();

    void on_bt_chercher_formateur_clicked();

    void on_afficher_formateur_clicked();

    void on_formateur_to_calendrier_clicked();

    void on_choose_picture_clicked();

    void on_formateur_to_formation_clicked();

    void on_formation_to_menu_clicked();

    void on_menu_to_formation_clicked();

    void on_menu_to_formateur_clicked();

    void on_menu_to_quitter_clicked();

    void on_formateur_to_menu_clicked();

    void on_calendrier_to_formateur_clicked();

    void on_formation_to_email_clicked();

    void on_email_to_formation_clicked();

    void GESTION_FORMATEUR_STATISTIQUE();
    void on_envoyer_clicked();

    void on_tableView_formateur_clicked(const QModelIndex &index);

    void on_ajouter_formation_clicked();

    void on_modifier_formation_clicked();

    void remplir_comobo_id_formateur_gestion_formation();

    void on_bt_supprimer_formation_clicked();

    void on_PDF_formation_clicked();

    void on_afficher_formation_clicked();

    void on_chercher_formation_clicked();

    void on_trier_formation_clicked();

    void on_tableView_formation_clicked(const QModelIndex &index);

    void GESTION_FORMATION_STATISTIQUE();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    FORMATION f;
    FORMATEUR fr;
};
#endif // MAINWINDOW_H

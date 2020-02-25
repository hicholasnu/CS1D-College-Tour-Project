#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();
    void changeToAdmin();
    void changetoStudent();
    void keyPressEvent(QKeyEvent* pe);
    void additemstocombobox();
    void additemstocomboboxcheck(QString item);

private slots:


    void on_clearbutton_clicked();

    void on_loginbutton_clicked();

    void on_logout_clicked();

    void on_viewdistance_clicked();

    void on_displaycollege_clicked();

    void on_backcollegedisplay_clicked();

    void on_ViewAllSouvenirs_clicked();

    void on_AddSouvenirbtn_clicked();


    void on_displaysouvenirs_clicked();

    void on_SouvenirView_activated(const QModelIndex &index);

    void on_Deletesouvenirbtn_clicked();

    void on_EditSouvenirbtn_clicked();

    void on_backsouvenir_clicked();

    void on_addcollegebutton_clicked();

    void on_viewallcolleges_clicked();

    void on_loadcolleges_clicked();

    void on_Loadsouvenirfile_clicked();

    void on_backcollegeBTN_clicked();

    void on_Backcustomtrip_clicked();

    void on_CustomTrip_clicked();

    void on_Collegecampusdrop_currentIndexChanged(const QString &arg1);


    void on_Customtourtable_activated(const QModelIndex &index);

    void on_startcustomtrip_clicked();


    void on_backshorttrip_clicked();

    void on_ShortestTrip_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_startshorttrip_clicked();

    void on_shortesttripcombo_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Controller *m_controller;
    int page = 0;
};
#endif // MAINWINDOW_H

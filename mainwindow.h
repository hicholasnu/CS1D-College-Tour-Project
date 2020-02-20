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

private:
    Ui::MainWindow *ui;
    Controller *m_controller;
    int page = 0;
};
#endif // MAINWINDOW_H

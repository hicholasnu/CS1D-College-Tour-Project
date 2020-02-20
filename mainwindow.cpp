#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
     m_controller(controller)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Login);
    QPixmap pix("/Users/mohamedsoliman/Desktop/Logo.png");
    int w = ui ->logo->width();
    int h = ui ->logo->height();
    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    ui->Login->setMinimumSize(600, 600);   // args are (width, height) in pixels
     // This sets the minimum size (pixels) of the main window. It cannot be shrunk smaller than those values.

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_clearbutton_clicked()
{
    ui->username->clear();
    ui->password->clear();
}


void MainWindow::on_loginbutton_clicked()
{
    QString username = ui->username ->text();
    QString password = ui->password->text();

    QSqlQuery qry;
    // RANK 2 IS USED FOR ADMINS
    // RANK 1 IS USED FOR STORE MANAGERS
    qry.prepare("select * from admin where username ='"+username+"' and password ='"+password+"' and rank= '2'");
    if (qry.exec())
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
           if(count == 1)
           {
            QMessageBox::information(this, "Login", "Username and password is correct");
            changeToAdmin();
            this->ui->username->setText("");
            this->ui->password->setText("");
           }
           else if (count!= 1)
           {
               if(qry.exec("select * from admin where username ='"+username+"' and password ='"+password+"' and rank= '1'"))
                   count  = 0;
                    while(qry.next())
                    {
                        count++;
                    }
                    if (count == 1)
                    {
                       QMessageBox::information(this,"Login", "Username and Password is correct");
                       changetoStudent();
                       this->ui->username->setText("");
                       this->ui->password->setText("");
                    }
                    else
                    {
                        QMessageBox::warning(this,"Login","Username and password is not correct");
                        this->ui->username->setText("");
                        this->ui->password->setText("");
                    }
           }
    }
}
void MainWindow :: changetoStudent()
{
    ui->stackedWidget->setCurrentWidget(ui->Studentcustomertrip);
}
void MainWindow::keyPressEvent(QKeyEvent* pe)
{
    if(page == 0)
    {
        if(pe->key()== Qt::Key_Return) on_loginbutton_clicked();
    }
}
void MainWindow::changeToAdmin()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminPage);
    page++;
}

void MainWindow::on_logout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Login);
    page = 0;
}

void MainWindow::on_viewdistance_clicked()
{
    ui->collegedisplay->setModel(m_controller->getsaddlebackCollegeQueryModel());
    ui->collegedisplay->resizeColumnsToContents();
}

void MainWindow::on_displaycollege_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewcollegedistance);

}

void MainWindow::on_backcollegedisplay_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminPage);
}

void MainWindow::on_ViewAllSouvenirs_clicked()
{
    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel());
    ui->SouvenirView->resizeColumnsToContents();
}


void MainWindow::on_AddSouvenirbtn_clicked()
{
    QString Item;
    QString Price;
    QString College;

    College = ui->CollegeLine->text();
    Price = ui->PriceLine->text();
    Item = ui->ItemLine->text();

    m_controller->createSouvenir(College,Item,Price);

    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel());
    ui->SouvenirView->resizeColumnsToContents();
    ui->CollegeLine->clear();
    ui->PriceLine->clear();
    ui->ItemLine->clear();
}


void MainWindow::on_displaysouvenirs_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Souvenirs);
}

void MainWindow::on_SouvenirView_activated(const QModelIndex &index)
{
    QString name;

    if(index.isValid())
    {
        QSqlQuery qry;
        name = index.data().toString();
        QString price;
        QString college;
        ui->editsouvenirlbl2->setText(name);

        qry.prepare("Select * from Souvenirs where Item = '"+name+"'");

        if (qry.exec())
        {
            while(qry.next())
            {
                college = qry.value(0).toString();
                price = qry.value(2).toString();
                ui->priceeditsouvenir->setText(price);
                ui->editsouvenirlbl1->setText(college);

            }
        }

    }
}

void MainWindow::on_Deletesouvenirbtn_clicked()
{
    QString name = ui->editsouvenirlbl2->text();
    m_controller->deleteSouvenir(name);
    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel());
    ui->SouvenirView->resizeColumnsToContents();
    ui->editsouvenirlbl1->clear();
    ui->editsouvenirlbl2->clear();
    ui->priceeditsouvenir->clear();
}

void MainWindow::on_EditSouvenirbtn_clicked()
{
    m_controller->updateSouvenir(ui->editsouvenirlbl2->text(),ui->editsouvenirlbl1->text(),ui->priceeditsouvenir->text());
    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel());
    ui->collegedisplay->resizeColumnsToContents();
    ui->editsouvenirlbl1->clear();
    ui->editsouvenirlbl2->clear();
    ui->priceeditsouvenir->clear();
}

void MainWindow::on_backsouvenir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminPage);
}

void MainWindow::on_addcollegebutton_clicked()
{
    QString startcollege;
    QString endcollege;
    QString distance;

    startcollege = ui->startcollegeline->text();
    endcollege = ui->endcollegeline->text();
    distance = ui->distanceline->text();

    m_controller->createCollege(startcollege,distance,endcollege);

    ui->collegedisplay->setModel(m_controller->getCollegeQueryModel());
    ui->collegedisplay->resizeColumnsToContents();
    ui->startcollegeline->clear();
    ui->endcollegeline->clear();
    ui->distanceline->clear();
}

void MainWindow::on_viewallcolleges_clicked()
{
     ui->collegedisplay->setModel(m_controller->getCollegeQueryModel());
     ui->collegedisplay->resizeColumnsToContents();
}

void MainWindow::on_loadcolleges_clicked()
{
    m_controller->readcollegeFile();
}

void MainWindow::on_Loadsouvenirfile_clicked()
{
    m_controller->readsouvenirFile();
}

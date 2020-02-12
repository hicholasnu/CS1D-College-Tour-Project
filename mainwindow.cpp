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
                      // changeToStudent();
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
}

void MainWindow::on_viewdistance_clicked()
{
    ui->collegedisplay->setModel(m_controller->getCollegeQueryModel());
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

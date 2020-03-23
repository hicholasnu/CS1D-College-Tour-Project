#include "mainwindow.h"
#include "ui_mainwindow.h"

   static QList<QString> tour;
   static QList<Souvenir*>tourSouv;
   static QList<QString> output;
   static QList<QString> outputReceipt;
   static QString tripList;
   static double totalSouvenirprice = 0;
   static int count = 0;

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
     m_controller(controller)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Login);
    QPixmap pix("/Users/mohamedsoliman/Desktop/Logo.png");
//    int w = ui ->logo->width();
//    int h = ui ->logo->height();
//    ui->logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    ui->Login->setMinimumSize(600, 600);   // args are (width, height) in pixels
     // This sets the minimum size (pixels) of the main window. It cannot be shrunk smaller than those values.
    additemstocombobox();

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
    // RANK 1 IS USED FOR STUDENTS
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

void MainWindow::on_displaycollege_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewcollegedistance);

}

void MainWindow::on_backcollegedisplay_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminPage);
}

void MainWindow::on_AddSouvenirbtn_clicked()
{

    if (ui->ItemLine->text() == "") {

        QMessageBox::warning(this, "Error", "Item has no name.");
    }
    else if(ui->spinBoxDoubleAdd->value() == 0.00) {

        QMessageBox::warning(this, "Error", "Item can not cost $0.00.");
    }
    else {

        QString Item;
        QString Price;
        QString College;

        College = ui->souvenircomboBox->currentText();
        Item = ui->ItemLine->text();
        Price = QString::number(ui->spinBoxDoubleAdd->value());

        m_controller->createSouvenir(College,Item,Price);

        ui->ItemLine->clear();
        ui->spinBoxDoubleAdd->setValue(0);

        ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel(ui->souvenircomboBox->currentText()));
        ui->SouvenirView->resizeColumnsToContents();
    }
}


void MainWindow::on_displaysouvenirs_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Souvenirs);
    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel(ui->souvenircomboBox->currentText()));
    ui->SouvenirView->resizeColumnsToContents();
}

void MainWindow::on_SouvenirView_activated(const QModelIndex &index)
{
    QString name;
    QString selectCollege;

    if(index.isValid())
    {
        QSqlQuery qry;
        name = index.data().toString();
        selectCollege = ui->souvenircomboBox->currentText();
        double price;
        QString Price;
        QString college;

        ui->editsouvenirlbl2->setText(name);

        qry.prepare("Select * from Souvenirs where Item = '"+name+"' and College = '"+selectCollege+"'");

        if (qry.exec())
        {
            while(qry.next())
            {
                college = qry.value(0).toString();
                price = qry.value(2).toDouble();
                Price = qry.value(2).toString();

                ui->spinBoxDoubleEdit->setValue(price);
                ui->editsouvenirlbl1->setText(college);
            }
        }
    }
}

void MainWindow::on_Deletesouvenirbtn_clicked()
{
    if (ui->editsouvenirlbl1->text() == "College" &&
            ui->editsouvenirlbl2->text() == "Item Name") {

        QMessageBox::warning(this, "Error", "No item selected.");
    }

    else {

        QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Deletion", "Sure to delete?",
                                      QMessageBox::Yes | QMessageBox::No);
        QString name = ui->editsouvenirlbl2->text();

        if (reply == QMessageBox::Yes) {

            m_controller->deleteSouvenir(name);
            ui->editsouvenirlbl1->setText("College");
            ui->editsouvenirlbl2->setText("Item Name");
            ui->spinBoxDoubleEdit->setValue(0);

            ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel(ui->souvenircomboBox->currentText()));
            ui->SouvenirView->resizeColumnsToContents();
        }
    }
}

void MainWindow::on_EditSouvenirbtn_clicked()
{

    if (ui->editsouvenirlbl1->text() == "College" &&
            ui->editsouvenirlbl2->text() == "Item Name") {

        QMessageBox::warning(this, "Error", "No item selected.");
    }
    else if(ui->spinBoxDoubleEdit->value() == 0.00) {

        QMessageBox::warning(this, "Error", "Item can not cost $0.00.");
    }
    else {

        QString Price;
        Price = QString::number(ui->spinBoxDoubleEdit->value());

        m_controller->updateSouvenir(ui->editsouvenirlbl2->text(),ui->editsouvenirlbl1->text(), Price);

        ui->editsouvenirlbl1->setText("College");
        ui->editsouvenirlbl2->setText("Item Name");
        ui->spinBoxDoubleEdit->setValue(0);

        ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel(ui->souvenircomboBox->currentText()));
        ui->SouvenirView->resizeColumnsToContents();
    }
}

void MainWindow::on_backsouvenir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->AdminPage);
}

void MainWindow::on_viewallcolleges_clicked()
{
     ui->collegedisplay->setModel(m_controller->getCollegeQueryModel());
     ui->collegedisplay->resizeColumnsToContents();
}

void MainWindow::on_viewdistance_clicked()
{
    ui->collegedisplay->setModel(m_controller->getsaddlebackCollegeQueryModel());
    ui->collegedisplay->resizeColumnsToContents();
}

void MainWindow::on_viewCollegesComboBox_activated(const QString &arg1)
{
    ui->collegedisplay->setModel(m_controller->getCollegeQueryModel1(arg1));
    ui->collegedisplay->resizeColumnsToContents();
}

void MainWindow::on_loadcolleges_clicked()
{
    m_controller->readcollegeFile();
    additemstocombobox();
    ui->spinBox->setRange(0,12);
}

void MainWindow::on_Loadsouvenirfile_clicked()
{
    m_controller->readsouvenirFile();
}

void MainWindow::on_backcollegeBTN_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Login);
    page = 0;
}
void MainWindow::additemstocombobox()
{
    ui->Collegecampusdrop->clear();
    ui->shortesttripcombo->clear();
    ui->souvenircomboBox->clear();
//    ui->comboBoxChooseCollege->clear();

    QList<QString>colleges;
    for (int i=0; i < m_controller->listOfColleges.count(); i++)
    {
        colleges.append(m_controller->listOfColleges[i]->startcollegeName());
    }
    colleges.removeDuplicates();
    ui->Collegecampusdrop->addItems(colleges);
    ui->shortesttripcombo->addItems(colleges);
    ui->viewCollegesComboBox->addItems(colleges);
    ui->souvenircomboBox->addItems(colleges);
//    ui->comboBoxChooseCollege->addItems(colleges);
}
void MainWindow::additemstocomboboxcheck(QString item)
{
    bool notfound = false;
    for (int i=0; i < ui->Collegecampusdrop->count();i++)
    {
        if(item == ui->Collegecampusdrop->itemText(i))
        {
            notfound = true;
        }
    }
    if(notfound == false)
    {
        ui->Collegecampusdrop->addItem(item);
        ui->shortesttripcombo->addItem(item);
    }

}


void MainWindow::on_Backcustomtrip_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Studentcustomertrip);
}

void MainWindow::on_CustomTrip_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->CustomTrippage);
    //ui->Customtourtable->setModel(m_controller->getCollegeQuerystartonlyModel());
    ui->Customtourtable->resizeColumnsToContents();
    ui->startcollegelbcustom->setText(ui->Collegecampusdrop->itemText(0));
}

void MainWindow::on_Collegecampusdrop_currentIndexChanged(const QString &arg1)
{
    ui->startcollegelbcustom->setText(arg1);
    ui->Customtourtable->setModel(m_controller->getCollegeQueryModel1(arg1));
    on_pushButton_clicked();
}


void MainWindow::on_Customtourtable_activated(const QModelIndex &index)
{
    QString name;

    if(index.isValid())
    {
        name = index.data().toString();
        tour.append(name);
        tripList.append(name);
        tripList.append('\n');
        count++;
        ui->displaynumberofcollege->setNum(count);
        ui->Customtourtable->hideRow(index.row());
        ui->customTripLabel->setText(tripList);
    }
}

void MainWindow::on_startcustomtrip_clicked()
{
    tourSouv = m_controller->customTrip(ui->startcollegelbcustom->text(),tour,output);

    ui->stackedWidget->setCurrentWidget(ui->collegedisplaypage);

    ui->collegetableitem->setRowCount(output.count());
    ui->collegetableitem->setColumnCount(2);

    for (int i = 0; i< output.count()-1;i++)
    {
        QTableWidgetItem *colleges = new QTableWidgetItem();
        QTableWidgetItem *collegename = new QTableWidgetItem();

        colleges->setText("College #" + QString ::number(i+1));
        collegename->setText(output[i]);
        ui->collegetableitem->setItem(i,0,colleges);
        ui->collegetableitem->setItem(i,1,collegename);
    }
    QTableWidgetItem *colleges = new QTableWidgetItem();
    QTableWidgetItem *collegename = new QTableWidgetItem();

    colleges->setText("Total Distance");
    collegename->setText(output.last());
    ui->collegetableitem->setItem(output.count()-1,0,colleges);
    ui->collegetableitem->setItem(output.count()-1,1,collegename);


    ui->collegetableitem->resizeColumnsToContents();
    output.clear();

    ui->SouvenirTableWidget->setRowCount(tourSouv.count());
    ui->SouvenirTableWidget->setColumnCount(4);


    for (int i=0; i < tourSouv.count();i++)
    {

        QTableWidgetItem *collegeName = new QTableWidgetItem();
        QTableWidgetItem *itemName = new QTableWidgetItem();
        QTableWidgetItem *price = new QTableWidgetItem();

        collegeName->setText(tourSouv[i]->college());
        itemName->setText(tourSouv[i]->item());
        price->setText(tourSouv[i]->price());


        ui->SouvenirTableWidget->setItem(i,0,collegeName);
        ui->SouvenirTableWidget->setItem(i,1,itemName);
        ui->SouvenirTableWidget->setItem(i,2,price);
        ui->SouvenirTableWidget->setCellWidget(i,3,new QSpinBox);
    }
    ui->SouvenirTableWidget->resizeColumnsToContents();
    tour.clear();
    count = 0;
    ui->displaynumberofcollege->clear();
}


void MainWindow::on_backshorttrip_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Studentcustomertrip);
}

void MainWindow::on_ShortestTrip_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->ShortestTrippage);
    ui->firstshorttrip->setText(ui->shortesttripcombo->itemText(0));
    ui->firstshorttrip->hide();
    ui->numberofcampuses->hide();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->numberofcampuses->setNum(arg1);
}

void MainWindow::on_startshorttrip_clicked()
{
    int num = 0;
    num = ui->numberofcampuses->text().toInt();
    tourSouv = m_controller->shortestTrip(ui->firstshorttrip->text(),num,output);
    ui->stackedWidget->setCurrentWidget(ui->collegedisplaypage);

    ui->collegetableitem->setRowCount(output.count());
    ui->collegetableitem->setColumnCount(2);

    for (int i = 0; i< output.count()-1;i++)
    {
        QTableWidgetItem *colleges = new QTableWidgetItem();
        QTableWidgetItem *collegename = new QTableWidgetItem();

        colleges->setText("College #" + QString ::number(i+1));
        collegename->setText(output[i]);
        ui->collegetableitem->setItem(i,0,colleges);
        ui->collegetableitem->setItem(i,1,collegename);
    }
    QTableWidgetItem *colleges = new QTableWidgetItem();
    QTableWidgetItem *collegename = new QTableWidgetItem();

    colleges->setText("Total Distance");
    collegename->setText(output.last());
    ui->collegetableitem->setItem(output.count()-1,0,colleges);
    ui->collegetableitem->setItem(output.count()-1,1,collegename);

    ui->collegetableitem->resizeColumnsToContents();
    output.clear();

    ui->SouvenirTableWidget->setRowCount(tourSouv.count());
    ui->SouvenirTableWidget->setColumnCount(4);


    for (int i=0; i < tourSouv.count();i++)
    {

        QTableWidgetItem *collegeName = new QTableWidgetItem();
        QTableWidgetItem *itemName = new QTableWidgetItem();
        QTableWidgetItem *price = new QTableWidgetItem();

        collegeName->setText(tourSouv[i]->college());
        itemName->setText(tourSouv[i]->item());
        price->setText(tourSouv[i]->price());


        ui->SouvenirTableWidget->setItem(i,0,collegeName);
        ui->SouvenirTableWidget->setItem(i,1,itemName);
        ui->SouvenirTableWidget->setItem(i,2,price);
        ui->SouvenirTableWidget->setCellWidget(i,3,new QSpinBox);
    }
    ui->SouvenirTableWidget->resizeColumnsToContents();
}

void MainWindow::on_shortesttripcombo_activated(const QString &arg1)
{
    ui->firstshorttrip->setText(arg1);
}

void MainWindow::on_souvenircomboBox_activated(const QString &arg1)
{
    ui->SouvenirView->setModel(m_controller->getSouvenirQueryModel(arg1));
    ui->SouvenirView->resizeColumnsToContents();
}

void MainWindow::on_CalSouv_clicked()
{
    ui->textBrowserReceipt->clear();

    for(int i = 0; i< tourSouv.count(); i++)
    {
        int val = static_cast<QSpinBox*>(ui->SouvenirTableWidget->cellWidget(i,3))->value();
        QTableWidgetItem *price = ui->SouvenirTableWidget->item(i,2);
        totalSouvenirprice = totalSouvenirprice + (price->text().toDouble()*val);
    }

    int quant;

    for (int i = 0; i < ui->SouvenirTableWidget->rowCount(); i++) {

        quant = static_cast<QSpinBox*>(ui->SouvenirTableWidget->cellWidget(i,3))->value();

        if (quant > 0) {

            ui->textBrowserReceipt->append(ui->SouvenirTableWidget->item(i,0)->text());
            ui->textBrowserReceipt->append(ui->SouvenirTableWidget->item(i,1)->text());
            ui->textBrowserReceipt->append(ui->SouvenirTableWidget->item(i,2)->text());
            ui->textBrowserReceipt->append(QString::number(quant));
        }
    }

    ui->grandTotal->setNum(totalSouvenirprice);
    totalSouvenirprice = 0;
}

void MainWindow::on_doneSouvenir_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Studentcustomertrip);
    tourSouv.clear();
    ui->SouvenirTableWidget->clear();
    ui->textBrowserReceipt->clear();
    on_Clearcalc_clicked();
    on_pushButton_clicked();
}

void MainWindow::on_Clearcalc_clicked()
{
    for(int i = 0;i< tourSouv.count();i++)
    {
        QSpinBox *box = static_cast<QSpinBox*>(ui->SouvenirTableWidget->cellWidget(i,3));
        box->setValue(0);
    }
    ui->grandTotal->clear();
    ui->textBrowserReceipt->clear();
}
void MainWindow::on_Donetosouv_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Souvenirtourpage);
     ui->collegetableitem->clear();
}


void MainWindow::on_pushButton_clicked()
{
    for (int i = 0; i < ui->Customtourtable->height(); i++) {

        ui->Customtourtable->showRow(i);
    }

    ui->customTripLabel->clear();
    tripList.clear();


    tour.clear();
    count = 0;
    ui->displaynumberofcollege->setNum(count);
}





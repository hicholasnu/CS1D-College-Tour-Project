#include "controller.h"

/**
 * @brief Controller::Controller
 * @param parent
 */

Controller::Controller(QObject *parent) : QObject(parent)
{
    // Connecting to database
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString path = QDir::homePath() + "/college.db";
    m_database.setDatabaseName(path);
    if(!m_database.open())
    {
        qDebug() << "problem opening database" << endl;
    }
    createTable();
    loadColleges();
    loadSouvenirs();
}

Controller::Controller(Controller &controller)
    :Controller()
{
}
Controller::~Controller()
{
    m_database.close();

}

void Controller::createTable()
{
     QSqlQuery qry;

     //==============================================================
     // About creating the Souvenirs table
     QString createSouvenirsTable =
     "create table IF NOT EXISTS Souvenirs(                       "
     "College          varchar(50) not null,                   "
     "Item             varchar(50) not null,                      "
     "Price            varchar(50) not null                       "
     ");                                                          ";

     if(!qry.exec(createSouvenirsTable))
     {
         qDebug() << "error creating college table" << endl;
     }
     qry.clear();

    //==============================================================
    // About creating the College table
    QString createSaddlebackTable =
    "create table IF NOT EXISTS College(                         "
    "StartCollege      varchar(50) not null,                     "
    "EndCollege        varchar(50) not null,                     "
    "Distance          varchar(50) not null                      "
    ");                                                          ";

    if(!qry.exec(createSaddlebackTable))
    {
        qDebug() << "error creating college table" << endl;
    }
    qry.clear();



    //==============================================================
    // About creating the admin table
    QString createAdminTable =
    "create table IF NOT EXISTS admin(                             "
    "username        varchar(50) primary key,                      "
    "password        varchar(50),                                  "
    "rank            integer                                       "
    ");                                                            ";

    if(!qry.exec(createAdminTable))
    {
        qDebug() << "error creating admin table" << endl;
    }
    qry.clear();

    qry.exec("insert into admin (username, password, rank) values ('admin' , 'admin', '2')");
    qry.exec("insert into admin (username, password, rank) values ('student' , 'student', '1')");


}

QSqlQueryModel *Controller::getsaddlebackCollegeQueryModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("select EndCollege, Distance from College WHERE StartCollege = 'Saddleback College';");
    if(!qry.exec())
    {
        qDebug() <<"error Loading values to db" << endl;

    }

    model->setQuery(qry);

    return model;
}

QSqlQueryModel *Controller::getCollegeQueryModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("select * from College;");
    if(!qry.exec())
    {
        qDebug() <<"error Loading values to db" << endl;

    }

    model->setQuery(qry);

    return model;
}

QSqlQueryModel *Controller::getCollegeQuerystartonlyModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("select DISTINCT StartCollege from College ;");
    if(!qry.exec())
    {
        qDebug() <<"error Loading values to db" << endl;

    }

    model->setQuery(qry);

    return model;
}

QSqlQueryModel *Controller::getSouvenirQueryModel(QString college)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("select Item, Price from Souvenirs WHERE College = '"+college+"' ;");
    if(!qry.exec())
    {
        qDebug() <<"error Loading values to db" << endl;

    }

    model->setQuery(qry);

    return model;
}

void Controller::createSouvenir(QString m_college, QString m_item,QString m_price)
{
    // Step 1
    // Creating an entry into database
    QSqlQuery qry;
    qry.prepare("insert into Souvenirs  (    "
                "College,                  "
                "Item,                     "
                "Price)                    "
                "values(?,?,?);              "
                );
    qry.addBindValue(m_college);
    qry.addBindValue(m_item);
    qry.addBindValue(m_price);

    if(!qry.exec())
    {
         qDebug() << "Error adding Souvenir" << endl;
    }
    qry.clear();

    // Step 2
    // Creating an entry into local memory
    Souvenir* entry = new Souvenir();
    entry->setItem(m_item);
    entry->setPrice(m_price);
    entry->setcollege(m_college);
    this->listofSouvenirs.append(entry);

}

void Controller :: createCollege(QString startCollegeName ,QString Distance, QString endCollegeName)
{
    // Step 1
    // Creating an entry into database
    QSqlQuery qry;
    qry.prepare("insert into College   (         "
                "StartCollege,                   "
                "EndCollege,                     "
                "Distance)                       "
                "values(?,?,?);                  "
                );
    qry.addBindValue(startCollegeName);
    qry.addBindValue(endCollegeName);
    qry.addBindValue(Distance);

    if(!qry.exec())
    {
         qDebug() << "Error adding College" << endl;
    }
    qry.clear();

    // Step 2
    // Creating an entry into local memory
    College* entry = new College();
    entry->setstartCollegeName(startCollegeName);
    entry->setDistance(Distance);
    entry->setendCollegeName(endCollegeName);
    this->listOfColleges.append(entry);
}

void Controller::deleteSouvenir(QString item)
{
    // Step 1
    // Deleting entry from database
    QSqlQuery qry;
    qry.prepare("delete from Souvenirs where Item = ?;");
    qry.addBindValue(item);
    if(!qry.exec())
    {
        qDebug() <<"error deleting values to db" << endl;
    }

    // Step 2
    // Deleting entry from souvenirs list
    int index;
    for(index = 0; index < this->listofSouvenirs.count(); index++)
    {
        if(this->listofSouvenirs[index]->item() == item)
            break;
    }
    this->listofSouvenirs.removeAt(index);
}

void Controller::updateSouvenir(QString item, QString college, QString price)
{
    QSqlQuery qry;
    qry.prepare("update Souvenirs set    "
                "College            = ?, "
                "Item               = ?, "
                "Price              = ?  "
                "where Item         = ?; "
                     );

    qry.addBindValue(college);
    qry.addBindValue(item);
    qry.addBindValue(price);
    qry.addBindValue(item);

    if(!qry.exec())
    {
        //qDebug() <<"error updating values to db" << endl;
        qDebug() << qry.lastError().text() << endl;
    }
    qry.clear();

    int index;
    for(index = 0; index < this->listofSouvenirs.count(); index++)
    {
        if(this->listofSouvenirs[index]->item() == item)
        {
            this->listofSouvenirs[index]->setPrice(price);
            break;
        }
    }

}

bool Controller::readcollegeFile()
{
    QString file_name = QFileDialog::getOpenFileName(nullptr, "Open Record File",QDir::homePath());


    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString startcollege = in.readLine();
        QString endcollege = in.readLine();
        QString distance = in.readLine();


        createCollege(startcollege,distance,endcollege);
    }

    return true;
}
bool Controller::readsouvenirFile()
{
    QString file_name = QFileDialog::getOpenFileName(nullptr, "Open Record File",QDir::homePath());


    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString college = in.readLine();
        QString item = in.readLine();
        QString price = in.readLine();


        createSouvenir(college,item,price);
    }

    return true;
}

void Controller::loadColleges()
{
    QSqlTableModel model;
    model.setTable("college");
    model.select();

    for(int index = 0; index < model.rowCount(); index++)
    {
        College* entry = new College();
        entry->setstartCollegeName(model.record(index).value("StartCollege").toString());
        entry->setendCollegeName(model.record(index).value("EndCollege").toString());
        entry->setDistance(model.record(index).value("Distance").toString());

        this->listOfColleges.append(entry);
    }
}
void Controller::loadSouvenirs()
{
    QSqlTableModel model;
    model.setTable("Souvenirs");
    model.select();

    for(int index = 0; index < model.rowCount(); index++)
    {
        Souvenir* entry = new Souvenir();
        entry->setcollege(model.record(index).value("College").toString());
        entry->setItem(model.record(index).value("Item").toString());
        entry->setPrice(model.record(index).value("Price").toString());

        this->listofSouvenirs.append(entry);
    }
}

QList<Souvenir*> Controller::customTrip(QString startCollege, QList<QString>tripcolleges,QList<QString>&CollegesVisited)
{
    trip* totaltrip  = new trip();
    totaltrip->setfirstcollege(startCollege);
    College* minitrip;
    QList<Souvenir*>souvtemplist;

    while(!tripcolleges.empty())
    {
        float distance = 1000000;
        float totaldistance = 0;
        QList<College*>templist;


        for(int i=0; i < listOfColleges.count();i++)
        {
            for(int j=0; j<tripcolleges.count();j++)
            {
                if(startCollege == listOfColleges[i]->startcollegeName() && tripcolleges[j] == listOfColleges[i]->endcollegeName())
                {
                    templist.append(listOfColleges[i]);
                }
            }

        }

        for(int i=0; i < templist.count(); i++)
        {
            if(templist[i]->distance().toFloat() < distance)
            {
                minitrip = templist.value(i);
                distance = templist.value(i)->distance().toFloat();
            }
        }

        qDebug() << minitrip->startcollegeName() << " " << minitrip->endcollegeName();

        for(int i = 0; i < listofSouvenirs.count(); i++)
        {
            if(startCollege == listofSouvenirs[i]->college())
            {
                souvtemplist.append(listofSouvenirs[i]);
            }
        }
        CollegesVisited.append(startCollege);
        tripcolleges.removeAll(minitrip->endcollegeName());
        startCollege = minitrip->endcollegeName();
        totaldistance = totaldistance + minitrip->distance().toFloat();
        totaltrip->addtototalDistance(totaldistance);
    }
    CollegesVisited.append(startCollege);
    CollegesVisited.append(QString::number(totaltrip->gettotalDistance()));


    for(int i = 0; i < listofSouvenirs.count(); i++)
    {
        if(startCollege == listofSouvenirs[i]->college())
        {
            souvtemplist.append(listofSouvenirs[i]);
        }
    }

    totaltrip->setlastcollege(startCollege);
    completedTrips.append(totaltrip);
    qDebug() << "First college is: " << totaltrip->getfirstcollege() << " " << "Last College is: " << totaltrip->getlastcollege()
             << "Total Distance is: " << totaltrip->gettotalDistance();

    return souvtemplist;

}

QList<Souvenir*> Controller::shortestTrip(QString startCollege, int key,QList<QString>&CollegesVisited)
{
    int numTrip = 0;
    trip* totaltrip  = new trip();
    totaltrip->setfirstcollege(startCollege);
    College* minitrip;
    QList<Souvenir*>souvtemplist;

    qDebug() << startCollege << " " << key;

    while(numTrip < key)
    {
        float distance = 1000000;
        float totaldistance = 0;
        QList<College*>templist;



        for(int i=0; i < listOfColleges.count();i++)
        {
            if(startCollege == listOfColleges[i]->startcollegeName())
            {
                templist.append(listOfColleges[i]);
            }

        }

        for(int i = 0; i < CollegesVisited.count(); i++)
        {
            for(int j =0; j < templist.count();j++)
            {
                if(CollegesVisited[i]==templist[j]->endcollegeName())
                {
                    templist.removeAt(j);
                }
            }
        }

        for(int i=0; i < templist.count(); i++)
        {
            if(templist[i]->distance().toFloat() < distance)
            {
                minitrip = templist.value(i);
                distance = templist.value(i)->distance().toFloat();
            }
        }

        for(int i = 0; i < listofSouvenirs.count(); i++)
        {
            if(startCollege == listofSouvenirs[i]->college())
            {
                souvtemplist.append(listofSouvenirs[i]);
            }
        }

        CollegesVisited.append(startCollege);
        startCollege = minitrip->endcollegeName();

        totaldistance = totaldistance + minitrip->distance().toFloat();
        totaltrip->addtototalDistance(totaldistance);
        numTrip++;
    }

    CollegesVisited.append(startCollege);
    CollegesVisited.append(QString::number(totaltrip->gettotalDistance()));



    for(int i = 0; i < listofSouvenirs.count(); i++)
    {
        if(startCollege == listofSouvenirs[i]->college())
        {
            souvtemplist.append(listofSouvenirs[i]);
        }
    }

    totaltrip->setlastcollege(startCollege);

        completedTrips.append(totaltrip);

        return souvtemplist;
}

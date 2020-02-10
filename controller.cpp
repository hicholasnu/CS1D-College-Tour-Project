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
    // About creating the college table
    QString createCollegeTable =
    "create table IF NOT EXISTS college(                         "
    "college          varchar(50) primary key,                   "
    "distance         float not null                               "
    ");                                                          ";

    if(!qry.exec(createCollegeTable))
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
    qry.exec("insert into admin (username, password, rank) values ('manager' , 'manager', '1')");


}

QSqlQueryModel *Controller::getCollegeQueryModel()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery qry;
    qry.prepare("select * from college;");
    if(!qry.exec())
    {
        qDebug() <<"error Loading values to db" << endl;

    }

    model->setQuery(qry);

    return model;
}

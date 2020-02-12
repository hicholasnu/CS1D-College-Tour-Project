#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include "College.h"
#include "Souvenir.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    Controller(Controller& controller);
    ~Controller();

    void createTable();
    QSqlQueryModel *getCollegeQueryModel();


private:
        QSqlDatabase      m_database;
        QList<College*>    listOfColleges;
        QList<Souvenir*>    listofSouvenirs;

};
#endif // CONTROLLER_H

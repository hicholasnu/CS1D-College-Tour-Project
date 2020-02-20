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
#include <QFileDialog>
#include "trip.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

    Controller(Controller& controller);
    ~Controller();

    void createTable();
    void createSouvenir(QString m_item, QString m_price, QString m_college );
    void createCollege(QString startCollegeName ,QString Distance, QString endCollegeName);
    void deleteSouvenir(QString item);
    void updateSouvenir(QString item, QString college, QString price);
    QSqlQueryModel *getsaddlebackCollegeQueryModel();
    QSqlQueryModel *getSouvenirQueryModel();
    QSqlQueryModel *getCollegeQueryModel();
    bool readcollegeFile();
    bool readsouvenirFile();
    void loadColleges();
    void loadSouvenirs();
    void customTrip(QString startCollege, QList<QString>collegetrips);


private:
        QSqlDatabase      m_database;
        QList<College*>   listOfColleges;
        QList<Souvenir*>  listofSouvenirs;
        QList<trip*> completedTrips;

};
#endif // CONTROLLER_H

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
#include<QItemDelegate>
#include<QSpinBox>
#include<QSize>
#include<QTableWidgetItem>
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
    QList<Souvenir*> shortestTrip(QString startCollege, int key,QList<QString>&CollegesVisited);
    QSqlQueryModel *getsaddlebackCollegeQueryModel();
    QSqlQueryModel *getSouvenirQueryModel(QString souvenir);
    QSqlQueryModel *getCollegeQueryModel();
    QSqlQueryModel *getCollegeQueryModel1(QString college);
    QSqlQueryModel *getCollegeQuerystartonlyModel();
    QSqlQueryModel *getCollegeQuerystartonlyModel1(QString college);
    bool readcollegeFile();
    bool readsouvenirFile();
    void loadColleges();
    void loadSouvenirs();
    QList<Souvenir*> customTrip(QString startCollege, QList<QString>collegetrips,QList<QString>&CollegesVisited);


        QList<College*>   listOfColleges;
private:
        QSqlDatabase      m_database;
        QList<Souvenir*>  listofSouvenirs;
        QList<trip*> completedTrips;

};
#endif // CONTROLLER_H

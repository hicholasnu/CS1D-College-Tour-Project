#ifndef TRIP_H
#define TRIP_H

#include <QList>
#include <QMap>
#include "College.h"
#include "Souvenir.h"

class trip : public QObject
{
    Q_OBJECT
public:
    explicit trip(QObject *parent = nullptr);


    void settotalDistance(QString totalDistance);
    QString gettotalDistance();
    QList<College*> getWholeTrip();

signals:

public slots:
private:
    QList<College*>   listOfCollegestrip;
    QList<Souvenir*>  listofSouvenirstrip;
    QString m_totalDistance;
};

#endif // TRIP_H

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


    void addtototalDistance(float totalDistance);
    float gettotalDistance();
    void setfirstcollege(QString first);
    QString getfirstcollege();
    QString getlastcollege();
    void setlastcollege(QString last);

    QString firstCollege;
    QString lastCollege;
    QList<Souvenir*>  listofSouvenirstrip;
    float m_totalDistance;
signals:

public slots:

};

#endif // TRIP_H

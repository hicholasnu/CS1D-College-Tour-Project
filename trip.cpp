#include "trip.h"

trip :: trip(QObject *parent) : QObject(parent)
{

}

void trip :: settotalDistance(QString totalDistance)
{
    m_totalDistance = totalDistance;
}

QString trip :: gettotalDistance()
{
    return m_totalDistance;
}

QList<College*> trip::getWholeTrip()
{
   return this->listOfCollegestrip;
}

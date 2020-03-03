#include "trip.h"

trip :: trip(QObject *parent) : QObject(parent)
{
    m_totalDistance = 0;
}

void trip :: addtototalDistance(float totalDistance)
{
    m_totalDistance = m_totalDistance + totalDistance;
}

float trip :: gettotalDistance()
{
    return m_totalDistance;
}
void trip::setfirstcollege(QString first)
{
    firstCollege = first;
}
void trip::setlastcollege(QString last)
{
    lastCollege = last;
}
QString trip :: getfirstcollege()
{
    return firstCollege;
}
QString trip :: getlastcollege()
{
    return lastCollege;
}

#include "College.h"

College::College(QObject *parent) : QObject(parent)
{

}

QString College::startcollegeName() const
{
    return startCollegeName;
}

void College::setstartCollegeName(const QString &collegename)
{
    startCollegeName = collegename;
}

float College::distance() const
{
    return Distance;
}

void College::setDistance(float distance)
{
    Distance = distance;
}

QString College::endcollegeName() const
{
    return startCollegeName;
}

void College::setendCollegeName(const QString &collegename)
{
    startCollegeName = collegename;
}

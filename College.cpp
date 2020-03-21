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

QString College::distance() const
{
    return Distance;
}

void College::setDistance(QString distance)
{
    Distance = distance;
}

QString College::endcollegeName() const
{
    return endCollegeName;
}

void College::setendCollegeName(const QString &collegename)
{
    endCollegeName = collegename;
}

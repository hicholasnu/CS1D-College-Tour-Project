#include "Souvenir.h"

Souvenir::Souvenir(QObject *parent) : QObject(parent)
{

}

QString Souvenir::item() const
{
    return m_item;
}

void Souvenir::setItem(const QString &item)
{
    m_item = item;
}

float Souvenir::price() const
{
    return m_price;
}

void Souvenir::setPrice(float price)
{
    m_price = price;
}

void Souvenir::setcollege(QString college)
{
    m_college = college;
}
QString Souvenir :: college() const
{
    return m_college;
}

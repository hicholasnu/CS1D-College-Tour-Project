#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <QObject>
#include <QString>

class Souvenir : public QObject
{
    Q_OBJECT
public:
    explicit Souvenir(QObject *parent = nullptr);


    QString item() const;
    void setItem(const QString &item);

    float price() const;
    void setPrice(float price);

    QString college() const;
    void setcollege(QString college);

signals:

public slots:
private:
    QString m_item;
    float   m_price;
    QString m_college;


};
#endif // SOUVENIR_H

#ifndef COLLEGE_H
#define COLLEGE_H

#include <QObject>
#include <QString>

class College : public QObject
{
    Q_OBJECT
public:
    explicit College(QObject *parent = nullptr);


    QString startcollegeName() const;
    void setstartCollegeName(const QString &item);

    float distance() const;
    void setDistance(float distance);

    QString endcollegeName() const;
    void setendCollegeName(const QString &item);

signals:

public slots:
private:
    QString startCollegeName;
    float   Distance;
    QString endCollegeName;
};

#endif // COLLEGE_H

#ifndef TRIP_H
#define TRIP_H

#include <QList>
#include <QMap>
#include "College.h"
#include "Souvenir.h"

/*!< trip class
 * This class will helps the program to provides necessary information for the trip
 */
class trip : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief trip - Constructor
     * @param parent
     */
    explicit trip(QObject *parent = nullptr);


    /**
     * @brief addtototalDistance - a member funciton to add each college's distance together for the whole trip
     * @param totalDistance
     */
    void addtototalDistance(float totalDistance);

    /**
     * @brief gettotalDistance - a member function to gets the total distane for the whole trip
     * @return float type of value
     */
    float gettotalDistance();

    /**
     * @brief setfirstcollege - a member function that sets the first college for the whole trip based on user choice or default
     * @param first
     */
    void setfirstcollege(QString first);

    /**
     * @brief getfirstcollege - a member function that gets the first college for the whole trip based on user choice or default
     * @return QString type of value
     */
    QString getfirstcollege();

    /**
     * @brief getlastcollege - a member function that gets the last college for the whole trip based on user choice or default
     * @return QString type of value
     */
    QString getlastcollege();

    /**
     * @brief setlastcollege - a member function that sets the last college for the whole trip based on user choice or default
     * @param last
     */
    void setlastcollege(QString last);

    QString firstCollege;                   /*!< QString type of value presents the first college of the trip */
    QString lastCollege;                    /*!< QString type of value presents the last college of the trip */
    QList<Souvenir*>  listofSouvenirstrip;  /*!< QList type with Souvenir type of pointer that contains the whole list of souvenirs for the whole trip */
    float m_totalDistance;                  /*!< float type of value presents the the total distance of the whole trip */
signals:

public slots:

};

#endif // TRIP_H

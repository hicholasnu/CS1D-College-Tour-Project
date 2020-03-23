#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <QObject>
#include <QString>

/*!< Souvenir class
 * This class helps the program to have access to make action for all souvenirs information
 */
class Souvenir : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Souvenir - Constructor
     * @param parent
     */
    explicit Souvenir(QObject *parent = nullptr);


    /**
     * @brief item - a member function that gets the souvenirs item for the program
     * @return QString type of value
     */
    QString item() const;

    /**
     * @brief setItem - a member function that sets the souvenirs item for correspond college to the program
     * @param item
     */
    void setItem(const QString &item);

    /**
     * @brief price - a member function that gets the price of the souvenir item for the program
     * @return QString type of value
     */
    QString price() const;

    /**
     * @brief setPrice - a member funciton that sets the price for the correspound souvenir items to the program
     * @param price
     */
    void setPrice(QString price);


    /**
     * @brief college -  a member function that gets the college that is correspound to the souvenirs
     * @return QString type of value
     */
    QString college() const;

    /**
     * @brief setcollege - a member function that sets the college for the correspound souvenirs item
     * @param college
     */
    void setcollege(QString college);

signals:

public slots:
private:
    QString m_item;     /*!< QString type of value that presents souvenir item name value*/
    QString m_price;    /*!< QString type of value that presents souvenir price value */
    QString m_college;  /*!< QString type of value that presents college name value */


};
#endif // SOUVENIR_H

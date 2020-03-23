#ifndef COLLEGE_H
#define COLLEGE_H

#include <QObject>
#include <QString>

/*!< College class
 * This class helps the program to have access to make action for all colleges information
 */

class College : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief College - Constructor
     * @param parent
     */
    explicit College(QObject *parent = nullptr);


    /**
     * @brief startcollegeName - a member function that gets the starting college based on the user choice or default
     * @return QString type of value
     */
    QString startcollegeName() const;

    /**
     * @brief setstartCollegeName - a member function that sets the starting college to the program
     * @param item
     */
    void setstartCollegeName(const QString &item);

    /**
     * @brief distance - a member function that gets the distance for the college that been choosed
     * @return QString tyoe of value
     */
    QString distance() const;

    /**
     * @brief setDistance - a member function that sets the distance of the college to the program
     * @param distance
     */
    void setDistance(QString distance);

    /**
     * @brief endcollegeName - a member function that gets the ending college based on the user choice or default
     * @return QString type of value
     */
    QString endcollegeName() const;

    /**
     * @brief setendCollegeName - a member function that sets the ending college to the program
     * @param item
     */
    void setendCollegeName(const QString &item);

signals:

public slots:
private:
    QString startCollegeName; /*!< QString type of value that presents the starting college name's value */
    QString Distance;         /*!< QString type of value that presents the distance value of the college */
    QString endCollegeName;   /*!< QString type of value that presents the ending college name's value */
};

#endif // COLLEGE_H

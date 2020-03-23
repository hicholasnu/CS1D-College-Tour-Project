#ifndef ADMIN_H
#define ADMIN_H

#include <QObject>
#include <QString>

/*!< admin class
 * This class provides the envoirment for login Ui
 * It determines whether the username and password is correct
 * It determines whether the user is administrator or student
 */
class Admin : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Admin - Constructor
     * @param parent
     */
    explicit Admin(QObject *parent = nullptr);

    /**
     * @brief username - a member function that gets the username for the login
     * @return QString type of value
     */
    QString username() const;

    /**
     * @brief setUsername - a member function that sets the username for the login
     * @param username
     */
    void setUsername(const QString &username);


    /**
     * @brief password - a member function that gets the password for the login
     * @return QString type of value
     */
    QString password() const;

    /**
     * @brief setPassword - a member funciton that sets the username for the login
     * @param password
     */
    void setPassword(const QString &password);


    /**
     * @brief rank - a member function that determins which rank value the user get based on the input
     * @return interger tyoe of value
     */
    int rank() const;

    /**
     * @brief setRank - a member funciton that sets the user rank to the program
     * @param rank
     */
    void setRank(int rank);

signals:
    void usernameChanged();
    void passwordChanged();
    void rankChanged();
public slots:

private:
    QString m_username; /*!< QString type of value that present username value */
    QString m_password; /*!< QString type of value that present password value */
    int     m_rank;     /*!< Integer type of value that present rank value */
};

#endif // ADMIN_H

#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDate>

// представляет клиента студии
class Client
{
private:
    int clientId;
    QString firstName;
    QString lastName;
    QString phone;
    QString email;
    QString country;
    QDate registrationDate;

public:
    Client() = default;
    Client(int clientId, const QString& firstName, const QString& lastName, const QString& phone, const QString& email, const QString& country, const QDate& registrationDate);
    ~Client() = default;

    // получить данные клиента
    int getClientId() const;
    const QString& getFirstName() const;
    const QString& getLastName() const;
    const QString& getPhone() const;
    const QString& getEmail() const;
    const QString& getCountry() const;
    const QDate& getRegistrationDate() const;

    // установить данные клиента
    void setClientId(int newClientId);
    void setFirstName(const QString& newFirstName);
    void setLastName(const QString& newLastName);
    void setPhone(const QString& newPhone);
    void setEmail(const QString& newEmail);
    void setCountry(const QString& newCountry);
    void setRegistrationDate(const QDate& newRegistrationDate);


};

#endif // CLIENT_H

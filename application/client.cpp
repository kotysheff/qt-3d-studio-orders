#include "client.h"

// реализация Client - представляет клиента студии

// конструктор инициализирует все поля клиента
Client::Client (int clientId, const QString& firstName, const QString&lastName, const QString& phone, const QString& email, const QString& country, const QDate& registrationDate) :
    clientId(clientId), firstName(firstName), lastName(lastName), phone(phone), email(email), country(country), registrationDate(registrationDate) {}

// получить ID клиента
int Client::getClientId() const {
    return clientId;
}

// получить имя клиента
const QString& Client::getFirstName() const {
    return firstName;
}

// получить фамилию клиента
const QString& Client::getLastName() const {
    return lastName;
}

// получить телефон клиента
const QString& Client::getPhone() const {
    return phone;
}

// получить email клиента
const QString& Client::getEmail() const {
    return email;
}

// получить страну клиента
const QString& Client::getCountry() const {
    return country;
}

// получить дату регистрации
const QDate& Client::getRegistrationDate() const {
    return registrationDate;
}

// установить новый ID клиента
void Client::setClientId(int newClientId) {
    clientId = newClientId;
}

// установить имя клиента
void Client::setFirstName(const QString& newFirstName) {
    firstName = newFirstName;
}

// установить фамилию клиента
void Client::setLastName(const QString& newLastName) {
    lastName = newLastName;
}

// установить телефон клиента
void Client::setPhone(const QString& newPhone) {
    phone = newPhone;
}

void Client::setEmail(const QString& newEmail) {
    email = newEmail;
}

void Client::setCountry(const QString& newCountry) {
    country = newCountry;
}

void Client::setRegistrationDate(const QDate& newRegistrationDate) {
    registrationDate = newRegistrationDate;
}
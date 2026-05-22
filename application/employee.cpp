#include "employee.h"

// реализация Employee - представляет сотрудника/подрядчика

// конструктор инициализирует все поля сотрудника
Employee::Employee(int employeeId, const QString& fullName, const QString& role, 
                   const QString& phone, const QString& email, int experienceYears, 
                   double hourlyRate, bool isAvailable)
    : employeeId(employeeId), fullName(fullName), role(role), phone(phone), 
      email(email), experienceYears(experienceYears), hourlyRate(hourlyRate), 
      isAvailable(isAvailable) {}

// получить ID сотрудника
int Employee::getEmployeeId() const {
    return employeeId;
}

// получить ФИО сотрудника
const QString& Employee::getFullName() const {
    return fullName;
}

// получить роль/должность
const QString& Employee::getRole() const {
    return role;
}

// получить телефон сотрудника
const QString& Employee::getPhone() const {
    return phone;
}

// получить email сотрудника
const QString& Employee::getEmail() const {
    return email;
}

// получить опыт в годах
int Employee::getExperienceYears() const {
    return experienceYears;
}

// получить почасовую ставку
double Employee::getHourlyRate() const {
    return hourlyRate;
}

// получить доступность сотрудника
bool Employee::getIsAvailable() const {
    return isAvailable;
}

// установить новый ID сотрудника
void Employee::setEmployeeId(int newEmployeeId) {
    employeeId = newEmployeeId;
}

// установить ФИО
void Employee::setFullName(const QString& newFullName) {
    fullName = newFullName;
}

// установить роль
void Employee::setRole(const QString& newRole) {
    role = newRole;
}

// установить телефон
void Employee::setPhone(const QString& newPhone) {
    phone = newPhone;
}

// установить email
void Employee::setEmail(const QString& newEmail) {
    email = newEmail;
}

// установить опыт
void Employee::setExperienceYears(int newExperienceYears) {
    experienceYears = newExperienceYears;
}

// установить почасовую ставку
void Employee::setHourlyRate(double newHourlyRate) {
    hourlyRate = newHourlyRate;
}

// установить доступность
void Employee::setIsAvailable(bool newIsAvailable) {
    isAvailable = newIsAvailable;
}

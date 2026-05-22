#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

// представляет сотрудника/подрядчика
class Employee
{
private:
    int employeeId;
    QString fullName;
    QString role;
    QString phone;
    QString email;
    int experienceYears;
    double hourlyRate;
    bool isAvailable;

public:
    Employee() = default;
    Employee(int employeeId, const QString& fullName, const QString& role, 
             const QString& phone, const QString& email, int experienceYears, 
             double hourlyRate, bool isAvailable);
    ~Employee() = default;

    int getEmployeeId() const;
    const QString& getFullName() const;
    const QString& getRole() const;
    const QString& getPhone() const;
    const QString& getEmail() const;
    int getExperienceYears() const;
    double getHourlyRate() const;
    bool getIsAvailable() const;

    void setEmployeeId(int newEmployeeId);
    void setFullName(const QString& newFullName);
    void setRole(const QString& newRole);
    void setPhone(const QString& newPhone);
    void setEmail(const QString& newEmail);
    void setExperienceYears(int newExperienceYears);
    void setHourlyRate(double newHourlyRate);
    void setIsAvailable(bool newIsAvailable);
};

#endif // EMPLOYEE_H

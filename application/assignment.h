#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QDate>
#include <QString>

// назначение сотрудника на заказ (many-to-many)
class Assignment
{
private:
    int assignmentId;
    int orderId;
    int employeeId;
    QString roleInOrder;
    QDate assignmentDate;
    int workloadHours;

public:
    Assignment() = default;
    Assignment(int assignmentId, int orderId, int employeeId, const QString& roleInOrder, 
               const QDate& assignmentDate, int workloadHours);
    ~Assignment() = default;

    int getAssignmentId() const;
    int getOrderId() const;
    int getEmployeeId() const;
    const QString& getRoleInOrder() const;
    const QDate& getAssignmentDate() const;
    int getWorkloadHours() const;

    void setAssignmentId(int newAssignmentId);
    void setOrderId(int newOrderId);
    void setEmployeeId(int newEmployeeId);
    void setRoleInOrder(const QString& newRoleInOrder);
    void setAssignmentDate(const QDate& newAssignmentDate);
    void setWorkloadHours(int newWorkloadHours);
};

#endif // ASSIGNMENT_H

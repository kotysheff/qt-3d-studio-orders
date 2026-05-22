#include "assignment.h"

// реализация Assignment - назначение сотрудника на заказ (many-to-many)

// конструктор инициализирует все поля назначения
Assignment::Assignment(int assignmentId, int orderId, int employeeId, const QString& roleInOrder, 
                       const QDate& assignmentDate, int workloadHours)
    : assignmentId(assignmentId), orderId(orderId), employeeId(employeeId), 
      roleInOrder(roleInOrder), assignmentDate(assignmentDate), workloadHours(workloadHours) {}

// получить ID назначения
int Assignment::getAssignmentId() const {
    return assignmentId;
}

// получить ID заказа
int Assignment::getOrderId() const {
    return orderId;
}

// получить ID сотрудника
int Assignment::getEmployeeId() const {
    return employeeId;
}

// получить роль сотрудника в заказе
const QString& Assignment::getRoleInOrder() const {
    return roleInOrder;
}

// получить дату назначения
const QDate& Assignment::getAssignmentDate() const {
    return assignmentDate;
}

// получить количество часов работы
int Assignment::getWorkloadHours() const {
    return workloadHours;
}

// установить новый ID назначения
void Assignment::setAssignmentId(int newAssignmentId) {
    assignmentId = newAssignmentId;
}

// установить ID заказа
void Assignment::setOrderId(int newOrderId) {
    orderId = newOrderId;
}

// установить ID сотрудника
void Assignment::setEmployeeId(int newEmployeeId) {
    employeeId = newEmployeeId;
}

// установить роль в заказе
void Assignment::setRoleInOrder(const QString& newRoleInOrder) {
    roleInOrder = newRoleInOrder;
}

// установить дату назначения
void Assignment::setAssignmentDate(const QDate& newAssignmentDate) {
    assignmentDate = newAssignmentDate;
}

// установить количество часов
void Assignment::setWorkloadHours(int newWorkloadHours) {
    workloadHours = newWorkloadHours;
}

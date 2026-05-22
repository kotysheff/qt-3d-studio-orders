#include "employeecoststrategy.h"
#include "assignment.h"
#include "employee.h"

// реализация EmployeeCostStrategy - расчёт стоимости по часам работы

// вычислить стоимость заказа по сумме поработанных часов (часы * тариф сотрудника)
double EmployeeCostStrategy::calculate(
    int orderId,
    const QVector<OrderService>& orderServices,
    const QVector<Assignment>& assignments,
    const QVector<Employee>& employees
) const
{
    Q_UNUSED(orderServices);

    double sum = 0;
    for (const Assignment& assignment : assignments) {
        if (assignment.getOrderId() == orderId) {
            for (const Employee& employee : employees) {
                if (employee.getEmployeeId() == assignment.getEmployeeId()) {
                    sum += assignment.getWorkloadHours() * employee.getHourlyRate();
                    break;
                }
            }
        }
    }
    return sum;
}

// получить название стратегии для отображения
QString EmployeeCostStrategy::getName() const
{
    return "По исполнителям";
}

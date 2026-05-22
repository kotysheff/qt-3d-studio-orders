#include "combinedcoststrategy.h"
#include "servicecoststrategy.h"
#include "employeecoststrategy.h"

// реализация CombinedCostStrategy - комбинированный расчёт

// вычислить стоимость заказа по сумме услуг и исполнителей
double CombinedCostStrategy::calculate(
    int orderId,
    const QVector<OrderService>& orderServices,
    const QVector<Assignment>& assignments,
    const QVector<Employee>& employees
) const
{
    ServiceCostStrategy serviceCost;
    EmployeeCostStrategy employeeCost;

    double serviceSum = serviceCost.calculate(orderId, orderServices, assignments, employees);
    double employeeSum = employeeCost.calculate(orderId, orderServices, assignments, employees);

    return serviceSum + employeeSum;
}

// получить название стратегии для отображения
QString CombinedCostStrategy::getName() const
{
    return "Комбинированный";
}

#ifndef EMPLOYEECOSTSTRATEGY_H
#define EMPLOYEECOSTSTRATEGY_H

#include "costcalculationstrategy.h"

// расчёт стоимости по часам работы сотрудников
class EmployeeCostStrategy : public CostCalculationStrategy
{
public:
    double calculate(
        int orderId,
        const QVector<OrderService>& orderServices,
        const QVector<Assignment>& assignments,
        const QVector<Employee>& employees
    ) const override;

    QString getName() const override;
};

#endif // EMPLOYEECOSTSTRATEGY_H

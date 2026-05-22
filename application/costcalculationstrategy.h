#ifndef COSTCALCULATIONSTRATEGY_H
#define COSTCALCULATIONSTRATEGY_H

#include <QString>
#include <QVector>

class OrderService;
class Assignment;
class Employee;

// базовый интерфейс для расчёта стоимости (стратегия)
class CostCalculationStrategy
{
public:
    virtual ~CostCalculationStrategy() = default;

    virtual double calculate(
        int orderId,
        const QVector<OrderService>& orderServices,
        const QVector<Assignment>& assignments,
        const QVector<Employee>& employees
    ) const = 0;

    virtual QString getName() const = 0;
};

#endif // COSTCALCULATIONSTRATEGY_H

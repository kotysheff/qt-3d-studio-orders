#ifndef SERVICECOSTSTRATEGY_H
#define SERVICECOSTSTRATEGY_H

#include "costcalculationstrategy.h"

// расчёт стоимости по услугам
class ServiceCostStrategy : public CostCalculationStrategy
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

#endif // SERVICECOSTSTRATEGY_H

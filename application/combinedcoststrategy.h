#ifndef COMBINEDCOSTSTRATEGY_H
#define COMBINEDCOSTSTRATEGY_H

#include "costcalculationstrategy.h"

// комбинированный расчёт (услуги + сотрудники)
class CombinedCostStrategy : public CostCalculationStrategy
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

#endif // COMBINEDCOSTSTRATEGY_H

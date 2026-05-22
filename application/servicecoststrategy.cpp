#include "servicecoststrategy.h"
#include "orderservice.h"

// реализация ServiceCostStrategy - расчёт стоимости по услугам

// вычислить стоимость заказа по сумме услуг (количество * согласованная цена)
double ServiceCostStrategy::calculate(
    int orderId,
    const QVector<OrderService>& orderServices,
    const QVector<Assignment>& assignments,
    const QVector<Employee>& employees
) const
{
    Q_UNUSED(assignments);
    Q_UNUSED(employees);

    double sum = 0;
    for (const OrderService& os : orderServices) {
        if (os.getOrderId() == orderId) {
            sum += os.getQuantity() * os.getAgreedPrice();
        }
    }
    return sum;
}

// получить названия стратегии для отображения
QString ServiceCostStrategy::getName() const
{
    return "По услугам";
}

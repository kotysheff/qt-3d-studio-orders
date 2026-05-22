#ifndef STUDIOFACADE_H
#define STUDIOFACADE_H

#include <QString>
#include <QVector>

class Client;
class Order;
class Service;
class Employee;
class OrderService;
class Assignment;
class CostCalculationStrategy;

// фасад для упрощённого доступа к данным
class StudioFacade
{
public:
    StudioFacade() = default;

    QString getClientFullNameById(const QVector<Client>& clients, int clientId) const;

    QString getServiceNameById(const QVector<Service>& services, int serviceId) const;

    QString getEmployeeNameById(const QVector<Employee>& employees, int employeeId) const;

    int findClientIndexById(const QVector<Client>& clients, int clientId) const;

    int findOrderIndexById(const QVector<Order>& orders, int orderId) const;

    int findServiceIndexById(const QVector<Service>& services, int serviceId) const;

    int findEmployeeIndexById(const QVector<Employee>& employees, int employeeId) const;

    double calculateOrderCost(
        int orderId,
        const CostCalculationStrategy& strategy,
        const QVector<OrderService>& orderServices,
        const QVector<Assignment>& assignments,
        const QVector<Employee>& employees
    ) const;
};

#endif // STUDIOFACADE_H

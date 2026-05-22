#include "studiofacade.h"
#include "client.h"
#include "order.h"
#include "service.h"
#include "employee.h"
#include "orderservice.h"
#include "assignment.h"
#include "costcalculationstrategy.h"

// реализация StudioFacade - фасад для упрощённого доступа к данным

// получить полное имя клиента по его ID
QString StudioFacade::getClientFullNameById(const QVector<Client>& clients, int clientId) const
{
    for (const Client& client : clients) {
        if (client.getClientId() == clientId) {
            return client.getFirstName() + " " + client.getLastName();
        }
    }
    return "";
}

// получить название услуги по её ID
QString StudioFacade::getServiceNameById(const QVector<Service>& services, int serviceId) const
{
    for (const Service& service : services) {
        if (service.getServiceId() == serviceId) {
            return service.getName();
        }
    }
    return "";
}

// получить ФИО сотрудника по его ID
QString StudioFacade::getEmployeeNameById(const QVector<Employee>& employees, int employeeId) const
{
    for (const Employee& employee : employees) {
        if (employee.getEmployeeId() == employeeId) {
            return employee.getFullName();
        }
    }
    return "";
}

// найти индекс клиента по его ID в векторе
int StudioFacade::findClientIndexById(const QVector<Client>& clients, int clientId) const
{
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].getClientId() == clientId) {
            return i;
        }
    }
    return -1;
}

// найти индекс заказа по его ID в векторе
int StudioFacade::findOrderIndexById(const QVector<Order>& orders, int orderId) const
{
    for (int i = 0; i < orders.size(); ++i) {
        if (orders[i].getOrderId() == orderId) {
            return i;
        }
    }
    return -1;
}

// найти индекс услуги по её ID в векторе
int StudioFacade::findServiceIndexById(const QVector<Service>& services, int serviceId) const
{
    for (int i = 0; i < services.size(); ++i) {
        if (services[i].getServiceId() == serviceId) {
            return i;
        }
    }
    return -1;
}

// найти индекс сотрудника по его ID в векторе
int StudioFacade::findEmployeeIndexById(const QVector<Employee>& employees, int employeeId) const
{
    for (int i = 0; i < employees.size(); ++i) {
        if (employees[i].getEmployeeId() == employeeId) {
            return i;
        }
    }
    return -1;
}

// вычислить стоимость заказа с использованием выбранной стратегии расчёта
double StudioFacade::calculateOrderCost(
    int orderId,
    const CostCalculationStrategy& strategy,
    const QVector<OrderService>& orderServices,
    const QVector<Assignment>& assignments,
    const QVector<Employee>& employees
) const
{
    return strategy.calculate(orderId, orderServices, assignments, employees);
}

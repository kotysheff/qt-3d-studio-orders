#include "order.h"

// реализация Order - представляет заказ студии

// конструктор инициализирует все поля заказа
Order::Order(int orderId, int clientId, const QString& title, const QString& description,
             const QDate& createdDate, const QDate& deadline, double totalCost, OrderStatus status)
    : orderId(orderId), clientId(clientId), title(title), description(description),
      createdDate(createdDate), deadline(deadline), totalCost(totalCost), status(status) {}

// получить ID заказа
int Order::getOrderId() const {
    return orderId;
}

// получить ID клиента
int Order::getClientId() const {
    return clientId;
}

// получить название заказа
const QString& Order::getTitle() const {
    return title;
}

// получить описание заказа
const QString& Order::getDescription() const {
    return description;
}

// получить дату создания заказа
const QDate& Order::getCreatedDate() const {
    return createdDate;
}

// получить дедлайн заказа
const QDate& Order::getDeadline() const {
    return deadline;
}

// получить итоговую стоимость
double Order::getTotalCost() const {
    return totalCost;
}

// получить статус заказа
OrderStatus Order::getStatus() const {
    return status;
}

// установить новый ID заказа
void Order::setOrderId(int newOrderId) {
    orderId = newOrderId;
}

// установить ID клиента
void Order::setClientId(int newClientId) {
    clientId = newClientId;
}

// установить название заказа
void Order::setTitle(const QString& newTitle) {
    title = newTitle;
}

// установить описание заказа
void Order::setDescription(const QString& newDescription) {
    description = newDescription;
}

// установить дату создания
void Order::setCreatedDate(const QDate& newCreatedDate) {
    createdDate = newCreatedDate;
}

// установить дедлайн
void Order::setDeadline(const QDate& newDeadline) {
    deadline = newDeadline;
}

// установить итоговую стоимость
void Order::setTotalCost(double newTotalCost) {
    totalCost = newTotalCost;
}

// установить статус
void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}

// преобразовать статус в строку для отображения
QString orderStatusToString(OrderStatus status)
{
    switch (status) {
    case OrderStatus::New:
        return "Новый";
    case OrderStatus::InProgress:
        return "В работе";
    case OrderStatus::Completed:
        return "Завершен";
    case OrderStatus::Cancelled:
        return "Отменен";
    }

    return "Новый";
}

OrderStatus orderStatusFromString(const QString& statusText)
{
    if (statusText == "Новый") {
        return OrderStatus::New;
    }

    if (statusText == "В работе") {
        return OrderStatus::InProgress;
    }

    if (statusText == "Завершен") {
        return OrderStatus::Completed;
    }

    if (statusText == "Отменен") {
        return OrderStatus::Cancelled;
    }

    return OrderStatus::New;
}

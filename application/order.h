#ifndef ORDER_H
#define ORDER_H

#include <QString>
#include <QDate>

// статусы заказа
enum class OrderStatus {
    New,
    InProgress,
    Completed,
    Cancelled
};

// конвертация статуса между строкой и enum
QString orderStatusToString(OrderStatus status);
OrderStatus orderStatusFromString(const QString& statusText);

// представляет заказ студии
class Order
{
private:
    int orderId;
    int clientId;
    QString title;
    QString description;
    QDate createdDate;
    QDate deadline;
    double totalCost;
    OrderStatus status;

public:
    Order() = default;
    Order(int orderId, int clientId, const QString& title, const QString& description,
          const QDate& createdDate, const QDate& deadline, double totalCost, OrderStatus status);
    ~Order() = default;

    // получить данные заказа
    int getOrderId() const;
    int getClientId() const;
    const QString& getTitle() const;
    const QString& getDescription() const;
    const QDate& getCreatedDate() const;
    const QDate& getDeadline() const;
    double getTotalCost() const;
    OrderStatus getStatus() const;

    // установить данные заказа
    void setOrderId(int newOrderId);
    void setClientId(int newClientId);
    void setTitle(const QString& newTitle);
    void setDescription(const QString& newDescription);
    void setCreatedDate(const QDate& newCreatedDate);
    void setDeadline(const QDate& newDeadline);
    void setTotalCost(double newTotalCost);
    void setStatus(OrderStatus newStatus);
};

#endif // ORDER_H

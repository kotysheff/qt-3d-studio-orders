#include "orderservice.h"

// реализация OrderService - связь заказа и услуги (many-to-many)

// конструктор инициализирует связь между заказом и услугой
OrderService::OrderService(int orderServiceId, int orderId, int serviceId, int quantity, double agreedPrice)
    : orderServiceId(orderServiceId), orderId(orderId), serviceId(serviceId), quantity(quantity), agreedPrice(agreedPrice) {}

// получить ID связи
int OrderService::getOrderServiceId() const {
    return orderServiceId;
}

// получить ID заказа
int OrderService::getOrderId() const {
    return orderId;
}

// получить ID услуги
int OrderService::getServiceId() const {
    return serviceId;
}

// получить количество услуг
int OrderService::getQuantity() const {
    return quantity;
}

// получить согласованную цену
double OrderService::getAgreedPrice() const {
    return agreedPrice;
}

// установить новый ID связи
void OrderService::setOrderServiceId(int newOrderServiceId) {
    orderServiceId = newOrderServiceId;
}

// установить ID заказа
void OrderService::setOrderId(int newOrderId) {
    orderId = newOrderId;
}

// установить ID услуги
void OrderService::setServiceId(int newServiceId) {
    serviceId = newServiceId;
}

// установить количество
void OrderService::setQuantity(int newQuantity) {
    quantity = newQuantity;
}

// установить согласованную цену
void OrderService::setAgreedPrice(double newAgreedPrice) {
    agreedPrice = newAgreedPrice;
}

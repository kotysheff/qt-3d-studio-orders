#ifndef ORDERSERVICE_H
#define ORDERSERVICE_H

// связь заказа и услуги (many-to-many)
class OrderService
{
private:
    int orderServiceId;
    int orderId;
    int serviceId;
    int quantity;
    double agreedPrice;

public:
    OrderService() = default;
    OrderService(int orderServiceId, int orderId, int serviceId, int quantity, double agreedPrice);
    ~OrderService() = default;

    int getOrderServiceId() const;
    int getOrderId() const;
    int getServiceId() const;
    int getQuantity() const;
    double getAgreedPrice() const;

    void setOrderServiceId(int newOrderServiceId);
    void setOrderId(int newOrderId);
    void setServiceId(int newServiceId);
    void setQuantity(int newQuantity);
    void setAgreedPrice(double newAgreedPrice);
};

#endif // ORDERSERVICE_H

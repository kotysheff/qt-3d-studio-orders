#ifndef ORDERSERVICEDIALOG_H
#define ORDERSERVICEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVector>
#include "orderservice.h"
#include "service.h"
#include "studiodialog.h"

// диалог для добавления услуги в заказ
class OrderServiceDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit OrderServiceDialog(QWidget *parent = nullptr);
    ~OrderServiceDialog() = default;

    QString getDialogName() const override;

    void setOrderId(int orderId);
    void setServices(const QVector<Service>& services);
    OrderService getOrderService() const;
    void setOrderService(const OrderService& orderService);

private slots:
    void onSaveClicked();

private:
    QComboBox *comboBoxService;
    QSpinBox *spinBoxQuantity;
    QDoubleSpinBox *doubleSpinBoxAgreedPrice;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    int currentOrderId = -1;
    QVector<Service> services;
};

#endif // ORDERSERVICEDIALOG_H

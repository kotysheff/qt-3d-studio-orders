#include "orderservicedialog.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// реализация OrderServiceDialog - диалог для добавления услуги в заказ

// конструктор создаёт UI с выбором услуги, количества и согласованной цены
OrderServiceDialog::OrderServiceDialog(QWidget *parent)
    : StudioDialog(parent)
{
    setWindowTitle("Добавить услугу в заказ");
    setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("Услуга:"));
    comboBoxService = new QComboBox();
    layout->addWidget(comboBoxService);
    
    layout->addWidget(new QLabel("Количество:"));
    spinBoxQuantity = new QSpinBox();
    spinBoxQuantity->setMinimum(1);
    spinBoxQuantity->setMaximum(1000);
    spinBoxQuantity->setValue(1);
    layout->addWidget(spinBoxQuantity);
    
    layout->addWidget(new QLabel("Согласованная цена:"));
    doubleSpinBoxAgreedPrice = new QDoubleSpinBox();
    doubleSpinBoxAgreedPrice->setMinimum(0);
    doubleSpinBoxAgreedPrice->setMaximum(100000000);
    doubleSpinBoxAgreedPrice->setDecimals(2);
    layout->addWidget(doubleSpinBoxAgreedPrice);
    
    layout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSave = new QPushButton("Сохранить");
    pushButtonCancel = new QPushButton("Отмена");
    buttonLayout->addWidget(pushButtonSave);
    buttonLayout->addWidget(pushButtonCancel);
    layout->addLayout(buttonLayout);
    
    connect(pushButtonSave, &QPushButton::clicked, this, &OrderServiceDialog::onSaveClicked);
    connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(comboBoxService, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        if (index >= 0 && index < services.size()) {
            doubleSpinBoxAgreedPrice->setValue(services[index].getBasePrice());
        }
    });
}

// установить ID заказа для новой связи
void OrderServiceDialog::setOrderId(int orderId) {
    currentOrderId = orderId;
}

// установить список доступных услуг в комбобокс
void OrderServiceDialog::setServices(const QVector<Service>& servicesList) {
    services = servicesList;
    comboBoxService->clear();
    
    for (const Service& service : services) {
        QString displayText = QString::number(service.getServiceId()) + " — " + service.getName();
        comboBoxService->addItem(displayText);
    }

    if (!services.isEmpty()) {
        doubleSpinBoxAgreedPrice->setValue(services[0].getBasePrice());
    }
}

// получить связь заказ-услуга из полей диалога
OrderService OrderServiceDialog::getOrderService() const {
    int serviceId = -1;
    
    if (comboBoxService->currentIndex() >= 0 && comboBoxService->currentIndex() < services.size()) {
        serviceId = services[comboBoxService->currentIndex()].getServiceId();
    }
    
    int quantity = spinBoxQuantity->value();
    double agreedPrice = doubleSpinBoxAgreedPrice->value();
    
    return OrderService(0, currentOrderId, serviceId, quantity, agreedPrice);
}

// установить связь заказ-услуга во все поля диалога для редактирования
void OrderServiceDialog::setOrderService(const OrderService& orderService) {
    for (int i = 0; i < services.size(); ++i) {
        if (services[i].getServiceId() == orderService.getServiceId()) {
            comboBoxService->setCurrentIndex(i);
            break;
        }
    }
    
    spinBoxQuantity->setValue(orderService.getQuantity());
    doubleSpinBoxAgreedPrice->setValue(orderService.getAgreedPrice());
}

// проверить введённые данные и сохранить связь
void OrderServiceDialog::onSaveClicked() {
    if (comboBoxService->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите услугу.");
        return;
    }
    
    if (spinBoxQuantity->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Количество должно быть больше 0.");
        return;
    }
    
    if (doubleSpinBoxAgreedPrice->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Согласованная цена не может быть отрицательной.");
        return;
    }
    
    accept();
}

QString OrderServiceDialog::getDialogName() const
{
    return "OrderServiceDialog";
}

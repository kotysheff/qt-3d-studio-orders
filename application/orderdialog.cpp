#include "orderdialog.h"
#include <QMessageBox>
#include <QDate>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// реализация OrderDialog - диалог для создания/редактирования заказа

// конструктор создаёт UI диалога с выбором клиента и настройкой дат
OrderDialog::OrderDialog(QWidget *parent)
    : StudioDialog(parent)
{
    setWindowTitle("Данные заказа");
    setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("Клиент:"));
    comboBoxClient = new QComboBox();
    layout->addWidget(comboBoxClient);
    
    layout->addWidget(new QLabel("Название:"));
    lineEditTitle = new QLineEdit();
    layout->addWidget(lineEditTitle);
    
    layout->addWidget(new QLabel("Описание:"));
    plainTextEditDescription = new QPlainTextEdit();
    layout->addWidget(plainTextEditDescription);
    
    layout->addWidget(new QLabel("Дата создания:"));
    dateEditCreatedDate = new QDateEdit();
    dateEditCreatedDate->setCalendarPopup(true);
    dateEditCreatedDate->setDate(QDate::currentDate());
    layout->addWidget(dateEditCreatedDate);
    
    layout->addWidget(new QLabel("Дедлайн:"));
    dateEditDeadline = new QDateEdit();
    dateEditDeadline->setCalendarPopup(true);
    dateEditDeadline->setDate(QDate::currentDate().addDays(7));
    layout->addWidget(dateEditDeadline);
    
    layout->addWidget(new QLabel("Стоимость:"));
    doubleSpinBoxTotalCost = new QDoubleSpinBox();
    doubleSpinBoxTotalCost->setMinimum(0);
    doubleSpinBoxTotalCost->setMaximum(100000000);
    doubleSpinBoxTotalCost->setDecimals(2);
    doubleSpinBoxTotalCost->setReadOnly(true);
    layout->addWidget(doubleSpinBoxTotalCost);
    
    layout->addWidget(new QLabel("Статус:"));
    comboBoxStatus = new QComboBox();
    comboBoxStatus->addItem(orderStatusToString(OrderStatus::New));
    comboBoxStatus->addItem(orderStatusToString(OrderStatus::InProgress));
    comboBoxStatus->addItem(orderStatusToString(OrderStatus::Completed));
    comboBoxStatus->addItem(orderStatusToString(OrderStatus::Cancelled));
    layout->addWidget(comboBoxStatus);
    
    layout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSave = new QPushButton("Сохранить");
    pushButtonCancel = new QPushButton("Отмена");
    buttonLayout->addWidget(pushButtonSave);
    buttonLayout->addWidget(pushButtonCancel);
    layout->addLayout(buttonLayout);
    
    connect(pushButtonSave, &QPushButton::clicked, this, &OrderDialog::onSaveClicked);
    connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// получить данные заказа из всех полей диалога
Order OrderDialog::getOrder() const {
    int clientId = -1;
    
    if (comboBoxClient->currentIndex() >= 0 && comboBoxClient->currentIndex() < clients.size()) {
        clientId = clients[comboBoxClient->currentIndex()].getClientId();
    }
    
    QString title = lineEditTitle->text();
    QString description = plainTextEditDescription->toPlainText();
    QDate createdDate = dateEditCreatedDate->date();
    QDate deadline = dateEditDeadline->date();
    double totalCost = doubleSpinBoxTotalCost->value();
    OrderStatus status = orderStatusFromString(comboBoxStatus->currentText());
    
    return Order(0, clientId, title, description, createdDate, deadline, totalCost, status);
}

// установить данные заказа во все поля диалога для редактирования
void OrderDialog::setOrder(const Order& order) {
    for (int i = 0; i < clients.size(); ++i) {
        if (clients[i].getClientId() == order.getClientId()) {
            comboBoxClient->setCurrentIndex(i);
            break;
        }
    }
    
    lineEditTitle->setText(order.getTitle());
    plainTextEditDescription->setPlainText(order.getDescription());
    dateEditCreatedDate->setDate(order.getCreatedDate());
    dateEditDeadline->setDate(order.getDeadline());
    doubleSpinBoxTotalCost->setValue(order.getTotalCost());
    comboBoxStatus->setCurrentText(orderStatusToString(order.getStatus()));
}

// установить список доступных клиентов для выбора в комбобоксе
void OrderDialog::setClients(const QVector<Client>& clientsList) {
    clients = clientsList;
    comboBoxClient->clear();
    
    for (const Client& client : clients) {
        QString displayText = QString::number(client.getClientId()) + " — " + 
                             client.getFirstName() + " " + client.getLastName();
        comboBoxClient->addItem(displayText);
    }
}

// проверить введённые данные и сохранить заказ
void OrderDialog::onSaveClicked() {
    if (comboBoxClient->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите клиента.");
        return;
    }
    
    if (lineEditTitle->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название заказа не может быть пустым.");
        return;
    }
    
    if (plainTextEditDescription->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Описание заказа не может быть пустым.");
        return;
    }
    
    if (doubleSpinBoxTotalCost->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Стоимость не может быть отрицательной.");
        return;
    }

    if (dateEditDeadline->date() < dateEditCreatedDate->date()) {
        QMessageBox::warning(this, "Ошибка", 
            "Дедлайн не может быть раньше даты создания заказа.");
        return;
    }
    
    accept();
}

QString OrderDialog::getDialogName() const
{
    return "OrderDialog";
}

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clientdialog.h"
#include "orderdialog.h"
#include "servicedialog.h"
#include "orderservicedialog.h"
#include "employeedialog.h"
#include "assignmentdialog.h"
#include "servicecoststrategy.h"
#include "employeecoststrategy.h"
#include "combinedcoststrategy.h"

#include <QStringList>
#include <QStandardItem>
#include <QList>
#include <QModelIndexList>
#include <QMessageBox>
#include <QInputDialog>
#include <QHeaderView>
#include <QAbstractItemView>
#include <memory>

// реализация MainWindow - главное окно приложения со всеми CRUD операциями

// конструктор инициализирует UI и устанавливает все подключения сигналов и таблицы
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonAddClient, &QPushButton::clicked, this, &MainWindow::onAddClientClicked);
    connect(ui->pushButtonEditClient, &QPushButton::clicked, this, &MainWindow::onEditClientClicked);
    connect(ui->pushButtonDeleteClient, &QPushButton::clicked, this, &MainWindow::onDeleteClientClicked);
    connect(ui->pushButtonRefreshClients, &QPushButton::clicked, this, &MainWindow::onRefreshClientClicked);
    connect(ui->pushButtonClientOrders, &QPushButton::clicked, this, &MainWindow::onClientOrdersClicked);
    connect(ui->pushButtonFindClient, &QPushButton::clicked, this, &MainWindow::onFindClientClicked);

    clientTableModel = new QStandardItemModel(ui->tableViewClients);
    ui->tableViewClients->setModel(clientTableModel);
    QStringList clientHeaders;
    clientHeaders << "ID" << "Имя" << "Фамилия" << "Телефон" << "Email" << "Страна" << "Дата регистрации";
    clientTableModel->setHorizontalHeaderLabels(clientHeaders);
    setupTableView(ui->tableViewClients);

    connect(ui->pushButtonAddOrder, &QPushButton::clicked, this, &MainWindow::onAddOrderClicked);
    connect(ui->pushButtonEditOrder, &QPushButton::clicked, this, &MainWindow::onEditOrderClicked);
    connect(ui->pushButtonDeleteOrder, &QPushButton::clicked, this, &MainWindow::onDeleteOrderClicked);
    connect(ui->pushButtonRefreshOrders, &QPushButton::clicked, this, &MainWindow::onRefreshOrdersClicked);
    connect(ui->pushButtonFindOrder, &QPushButton::clicked, this, &MainWindow::onFindOrderClicked);
    connect(ui->pushButtonOrderServices, &QPushButton::clicked, this, &MainWindow::onOrderServicesClicked);
    connect(ui->pushButtonOrderEmployees, &QPushButton::clicked, this, &MainWindow::onOrderEmployeesClicked);
    connect(ui->pushButtonCalculateOrderCost, &QPushButton::clicked, this, &MainWindow::onCalculateOrderCostClicked);

    orderTableModel = new QStandardItemModel(ui->tableViewOrders);
    ui->tableViewOrders->setModel(orderTableModel);
    QStringList orderHeaders;
    orderHeaders << "ID" << "Клиент" << "Название" << "Описание" << "Дата создания" << "Дедлайн" << "Стоимость" << "Статус";
    orderTableModel->setHorizontalHeaderLabels(orderHeaders);
    setupTableView(ui->tableViewOrders);

    connect(ui->pushButtonAddService, &QPushButton::clicked, this, &MainWindow::onAddServiceClicked);
    connect(ui->pushButtonEditService, &QPushButton::clicked, this, &MainWindow::onEditServiceClicked);
    connect(ui->pushButtonDeleteService, &QPushButton::clicked, this, &MainWindow::onDeleteServiceClicked);
    connect(ui->pushButtonRefreshServices, &QPushButton::clicked, this, &MainWindow::onRefreshServicesClicked);
    connect(ui->pushButtonFindService, &QPushButton::clicked, this, &MainWindow::onFindServiceClicked);
    connect(ui->pushButtonServiceOrders, &QPushButton::clicked, this, &MainWindow::onServiceOrdersClicked);

    serviceTableModel = new QStandardItemModel(ui->tableViewServices);
    ui->tableViewServices->setModel(serviceTableModel);
    QStringList serviceHeaders;
    serviceHeaders << "ID" << "Название" << "Описание" << "Базовая цена" << "Длительность";
    serviceTableModel->setHorizontalHeaderLabels(serviceHeaders);
    setupTableView(ui->tableViewServices);

    connect(ui->pushButtonAddEmployee, &QPushButton::clicked, this, &MainWindow::onAddEmployeeClicked);
    connect(ui->pushButtonEditEmployee, &QPushButton::clicked, this, &MainWindow::onEditEmployeeClicked);
    connect(ui->pushButtonDeleteEmployee, &QPushButton::clicked, this, &MainWindow::onDeleteEmployeeClicked);
    connect(ui->pushButtonRefreshEmployees, &QPushButton::clicked, this, &MainWindow::onRefreshEmployeesClicked);
    connect(ui->pushButtonFindEmployee, &QPushButton::clicked, this, &MainWindow::onFindEmployeeClicked);
    connect(ui->pushButtonEmployeeOrders, &QPushButton::clicked, this, &MainWindow::onEmployeeOrdersClicked);

    employeeTableModel = new QStandardItemModel(ui->tableViewEmployees);
    ui->tableViewEmployees->setModel(employeeTableModel);
    QStringList employeeHeaders;
    employeeHeaders << "ID" << "ФИО" << "Роль" << "Телефон" << "Email" << "Опыт" << "Ставка" << "Доступен";
    employeeTableModel->setHorizontalHeaderLabels(employeeHeaders);
    setupTableView(ui->tableViewEmployees);

    refreshClientsTable();
    refreshOrdersTable();
    refreshServicesTable();
    refreshEmployeesTable();
}

// деструктор удаляет UI элементы
MainWindow::~MainWindow()
{
    delete ui;
}

// создать нового клиента через диалог
void MainWindow::onAddClientClicked () {
    ClientDialog* dialog = DialogFactory::createClientDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        Client newClient = dialog->getClient();
        newClient.setClientId(nextClientId);
        nextClientId += 1;
        clients.push_back(newClient);
        refreshClientsTable();
    }

    delete dialog;
}

// редактировать выбранного клиента
void MainWindow::onEditClientClicked() {
    int clientId = getSelectedClientId();

    if (clientId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один клиент не выбран.");
        return;
    }

    int clientIndex = facade.findClientIndexById(clients, clientId);

    if (clientIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Клиент не найден.");
        return;
    }

    ClientDialog* dialog = DialogFactory::createClientDialog(this);
    dialog->setClient(clients[clientIndex]);

    if (dialog->exec() == QDialog::Accepted) {
        Client updatedClient = dialog->getClient();
        updatedClient.setClientId(clientId);
        clients[clientIndex] = updatedClient;
        refreshClientsTable();
    }

    delete dialog;
}

// удалить выбранного клиента
void MainWindow::onDeleteClientClicked() {
    int clientId = getSelectedClientId();

    if (clientId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один клиент не выбран.");
        return;
    }

    int clientIndex = facade.findClientIndexById(clients, clientId);

    if (clientIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Клиент не найден.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Вы уверены?", "Вы точно хотите удалить пользователя?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (const Order& order : orders) {
            if (order.getClientId() == clientId) {
                QMessageBox::warning(this, "Ошибка",
                    "Нельзя удалить клиента, у которого есть заказы.\n"
                    "Сначала удалите или переназначьте его заказы.");
                return;
            }
        }

        clients.remove(clientIndex);
        refreshClientsTable();
    }
}

// обновить таблицу клиентов
void MainWindow::onRefreshClientClicked() {
    refreshClientsTable();
}
// найти клиентов по критериям
void MainWindow::onFindClientClicked()
{
    clientTableModel->removeRows(0, clientTableModel->rowCount());
    QString userRequest = getUserRequest().trimmed().toLower();

    if (userRequest.isEmpty()) {
        refreshClientsTable();
        return;
    }

    for (const Client& client : clients) {
        bool matches = false;
        matches |= client.getFirstName().toLower().contains(userRequest);
        matches |= client.getLastName().toLower().contains(userRequest);
        matches |= QString::number(client.getClientId()).contains(userRequest);
        matches |= client.getCountry().toLower().contains(userRequest);
        matches |= client.getEmail().toLower().contains(userRequest);
        matches |= client.getPhone().toLower().contains(userRequest);
        if (matches) {
            appendClientToTable(client);
        }
    }
}

// обновить таблицу клиентов - перезагрузить всех клиентов
void MainWindow::refreshClientsTable() {
    ui->lineEditClientSearch->setText("");
    clientTableModel->removeRows(0, clientTableModel->rowCount());

    for (const Client& client : clients) {
        appendClientToTable(client);
    }
}

QString MainWindow::getUserRequest() const {
    QString userRequest = ui->lineEditClientSearch->text();
    return userRequest;
}

// получить ID выбранного клиента из таблицы
int MainWindow::getSelectedClientId() const {
    QModelIndexList selectedRow = ui->tableViewClients->selectionModel()->selectedRows();

    if (selectedRow.isEmpty()) {
        return -1;
    }

    int rowIndex = selectedRow.first().row();

    QAbstractItemModel* model = ui->tableViewClients->model();
    QModelIndex idIndex = model->index(rowIndex, 0);

    return model->data(idIndex).toInt();
}

// добавить клиента в таблицу клиентов
void MainWindow::appendClientToTable(const Client& client) {
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::number(client.getClientId()));
    row << new QStandardItem(client.getFirstName());
    row << new QStandardItem(client.getLastName());
    row << new QStandardItem(client.getPhone());
    row << new QStandardItem(client.getEmail());
    row << new QStandardItem(client.getCountry());
    row << new QStandardItem(client.getRegistrationDate().toString("dd.MM.yyyy"));
    clientTableModel->appendRow(row);
}

// создать новый заказ через диалог
void MainWindow::onAddOrderClicked() {
    if (clients.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте хотя бы одного клиента.");
        return;
    }

    OrderDialog* dialog = DialogFactory::createOrderDialog(this);
    dialog->setClients(clients);

    if (dialog->exec() == QDialog::Accepted) {
        Order newOrder = dialog->getOrder();
        newOrder.setOrderId(nextOrderId);
        nextOrderId += 1;
        orders.push_back(newOrder);
        refreshOrdersTable();
    }

    delete dialog;
}

void MainWindow::onEditOrderClicked() {
    int orderId = getSelectedOrderId();

    if (orderId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один заказ не выбран.");
        return;
    }

    int orderIndex = facade.findOrderIndexById(orders, orderId);

    if (orderIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Заказ не найден.");
        return;
    }

    OrderDialog* dialog = DialogFactory::createOrderDialog(this);
    dialog->setClients(clients);
    dialog->setOrder(orders[orderIndex]);

    if (dialog->exec() == QDialog::Accepted) {
        Order updatedOrder = dialog->getOrder();
        updatedOrder.setOrderId(orderId);
        orders[orderIndex] = updatedOrder;
        refreshOrdersTable();
    }

    delete dialog;
}

void MainWindow::onDeleteOrderClicked() {
    int orderId = getSelectedOrderId();

    if (orderId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один заказ не выбран.");
        return;
    }

    int orderIndex = facade.findOrderIndexById(orders, orderId);

    if (orderIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Заказ не найден.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Вы уверены?", "Вы точно хотите удалить заказ?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (int i = orderServices.size() - 1; i >= 0; --i) {
            if (orderServices[i].getOrderId() == orderId) {
                orderServices.remove(i);
            }
        }

        for (int i = assignments.size() - 1; i >= 0; --i) {
            if (assignments[i].getOrderId() == orderId) {
                assignments.remove(i);
            }
        }

        orders.remove(orderIndex);
        refreshOrdersTable();
    }
}

void MainWindow::onRefreshOrdersClicked() {
    refreshOrdersTable();
}

void MainWindow::onFindOrderClicked() {
    orderTableModel->removeRows(0, orderTableModel->rowCount());
    QString userRequest = getOrderSearchRequest().trimmed().toLower();

    if (userRequest.isEmpty()) {
        refreshOrdersTable();
        return;
    }

    for (const Order& order : orders) {
        bool matches = false;
        matches |= QString::number(order.getOrderId()).contains(userRequest);
        matches |= facade.getClientFullNameById(clients, order.getClientId()).toLower().contains(userRequest);
        matches |= order.getTitle().toLower().contains(userRequest);
        matches |= order.getDescription().toLower().contains(userRequest);
        matches |= orderStatusToString(order.getStatus()).toLower().contains(userRequest);

        if (matches) {
            appendOrderToTable(order);
        }
    }
}

// добавить услугу в заказ
void MainWindow::onOrderServicesClicked() {
    int orderId = getSelectedOrderId();

    if (orderId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один заказ не выбран.");
        return;
    }

    if (services.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте хотя бы одну услугу.");
        return;
    }

    OrderServiceDialog* dialog = DialogFactory::createOrderServiceDialog(this);
    dialog->setOrderId(orderId);
    dialog->setServices(services);

    if (dialog->exec() == QDialog::Accepted) {
        OrderService newOrderService = dialog->getOrderService();
        newOrderService.setOrderServiceId(nextOrderServiceId);
        nextOrderServiceId += 1;
        orderServices.push_back(newOrderService);

        QString serviceName = facade.getServiceNameById(services, newOrderService.getServiceId());
        QString message = QString(
            "Услуга добавлена в заказ.\n\n"
            "Заказ ID: %1\n"
            "Услуга: %2\n"
            "Количество: %3\n"
            "Цена: %4"
        ).arg(orderId)
         .arg(serviceName)
         .arg(newOrderService.getQuantity())
         .arg(QString::number(newOrderService.getAgreedPrice(), 'f', 2));

        QMessageBox::information(this, "Успешно", message);
        refreshOrdersTable();
    }

    delete dialog;
}

// назначить сотрудника на заказ
void MainWindow::onOrderEmployeesClicked() {
    int orderId = getSelectedOrderId();

    if (orderId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один заказ не выбран.");
        return;
    }

    if (employees.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Сначала добавьте хотя бы одного исполнителя.");
        return;
    }

    AssignmentDialog* dialog = DialogFactory::createAssignmentDialog(this);
    dialog->setOrderId(orderId);
    dialog->setEmployees(employees);

    if (dialog->exec() == QDialog::Accepted) {
        Assignment newAssignment = dialog->getAssignment();
        newAssignment.setAssignmentId(nextAssignmentId);
        nextAssignmentId += 1;
        assignments.push_back(newAssignment);

        QString employeeName = facade.getEmployeeNameById(employees, newAssignment.getEmployeeId());
        QString message = QString(
            "Исполнитель назначен на заказ.\n\n"
            "Заказ ID: %1\n"
            "Исполнитель: %2\n"
            "Роль в заказе: %3\n"
            "Нагрузка: %4 часов"
        ).arg(orderId)
         .arg(employeeName)
         .arg(newAssignment.getRoleInOrder())
         .arg(newAssignment.getWorkloadHours());

        QMessageBox::information(this, "Успешно", message);
        refreshOrdersTable();
    }

    delete dialog;
}

// рассчитать стоимость заказа
void MainWindow::onCalculateOrderCostClicked() {
    int orderId = getSelectedOrderId();

    if (orderId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один заказ не выбран.");
        return;
    }

    int orderIndex = facade.findOrderIndexById(orders, orderId);

    if (orderIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Заказ не найден.");
        return;
    }

    QStringList items;
    items << "По услугам" << "По исполнителям" << "Комбинированный";

    bool ok;
    QString item = QInputDialog::getItem(this, "Выбор способа расчета", "Способ расчета:", items, 0, false, &ok);

    if (!ok || item.isEmpty()) {
        return;
    }

    std::unique_ptr<CostCalculationStrategy> strategy;

    if (item == "По услугам") {
        strategy = std::make_unique<ServiceCostStrategy>();
    } else if (item == "По исполнителям") {
        strategy = std::make_unique<EmployeeCostStrategy>();
    } else if (item == "Комбинированный") {
        strategy = std::make_unique<CombinedCostStrategy>();
    }

    if (!strategy) {
        QMessageBox::warning(this, "Ошибка", "Способ расчета не выбран.");
        return;
    }

    double totalCost = facade.calculateOrderCost(orderId, *strategy, orderServices, assignments, employees);

    orders[orderIndex].setTotalCost(totalCost);
    refreshOrdersTable();

    QString strategyName = strategy->getName();
    QString message = QString(
        "Способ расчета: %1\n"
        "Стоимость заказа: %2"
    ).arg(strategyName)
     .arg(QString::number(totalCost, 'f', 2));

    QMessageBox::information(this, "Итоговая стоимость", message);
}

// обновить таблицу заказов
void MainWindow::refreshOrdersTable() {
    ui->lineEditOrderSearch->setText("");
    orderTableModel->removeRows(0, orderTableModel->rowCount());

    for (const Order& order : orders) {
        appendOrderToTable(order);
    }
}

void MainWindow::appendOrderToTable(const Order& order) {
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::number(order.getOrderId()));
    row << new QStandardItem(facade.getClientFullNameById(clients, order.getClientId()));
    row << new QStandardItem(order.getTitle());
    row << new QStandardItem(order.getDescription());
    row << new QStandardItem(order.getCreatedDate().toString("dd.MM.yyyy"));
    row << new QStandardItem(order.getDeadline().toString("dd.MM.yyyy"));
    row << new QStandardItem(QString::number(order.getTotalCost(), 'f', 2));
    row << new QStandardItem(orderStatusToString(order.getStatus()));
    orderTableModel->appendRow(row);
}

int MainWindow::getSelectedOrderId() const {
    QModelIndexList selectedRow = ui->tableViewOrders->selectionModel()->selectedRows();

    if (selectedRow.isEmpty()) {
        return -1;
    }

    int rowIndex = selectedRow.first().row();
    QAbstractItemModel* model = ui->tableViewOrders->model();
    QModelIndex idIndex = model->index(rowIndex, 0);

    return model->data(idIndex).toInt();
}

QString MainWindow::getOrderSearchRequest() const {
    return ui->lineEditOrderSearch->text();
}

void MainWindow::onAddServiceClicked() {
    ServiceDialog* dialog = DialogFactory::createServiceDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        Service newService = dialog->getService();
        newService.setServiceId(nextServiceId);
        nextServiceId += 1;
        services.push_back(newService);
        refreshServicesTable();
    }

    delete dialog;
}

void MainWindow::onEditServiceClicked() {
    int serviceId = getSelectedServiceId();

    if (serviceId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни одна услуга не выбрана.");
        return;
    }

    int serviceIndex = facade.findServiceIndexById(services, serviceId);

    if (serviceIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Услуга не найдена.");
        return;
    }

    ServiceDialog* dialog = DialogFactory::createServiceDialog(this);
    dialog->setService(services[serviceIndex]);

    if (dialog->exec() == QDialog::Accepted) {
        Service updatedService = dialog->getService();
        updatedService.setServiceId(serviceId);
        services[serviceIndex] = updatedService;
        refreshServicesTable();
    }

    delete dialog;
}

void MainWindow::onDeleteServiceClicked() {
    int serviceId = getSelectedServiceId();

    if (serviceId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни одна услуга не выбрана.");
        return;
    }

    int serviceIndex = facade.findServiceIndexById(services, serviceId);

    if (serviceIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Услуга не найдена.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Вы уверены?", "Вы точно хотите удалить услугу?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (int i = orderServices.size() - 1; i >= 0; --i) {
            if (orderServices[i].getServiceId() == serviceId) {
                orderServices.remove(i);
            }
        }

        services.remove(serviceIndex);
        refreshServicesTable();
        refreshOrdersTable();
    }
}

void MainWindow::onRefreshServicesClicked() {
    refreshServicesTable();
}

void MainWindow::onFindServiceClicked() {
    serviceTableModel->removeRows(0, serviceTableModel->rowCount());
    QString userRequest = getServiceSearchRequest().trimmed().toLower();

    if (userRequest.isEmpty()) {
        refreshServicesTable();
        return;
    }

    for (const Service& service : services) {
        bool matches = false;
        matches |= QString::number(service.getServiceId()).contains(userRequest);
        matches |= service.getName().toLower().contains(userRequest);
        matches |= service.getDescription().toLower().contains(userRequest);
        matches |= QString::number(service.getBasePrice()).contains(userRequest);
        matches |= QString::number(service.getDurationDays()).contains(userRequest);

        if (matches) {
            appendServiceToTable(service);
        }
    }
}

void MainWindow::refreshServicesTable() {
    ui->lineEditServiceSearch->setText("");
    serviceTableModel->removeRows(0, serviceTableModel->rowCount());

    for (const Service& service : services) {
        appendServiceToTable(service);
    }
}

void MainWindow::appendServiceToTable(const Service& service) {
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::number(service.getServiceId()));
    row << new QStandardItem(service.getName());
    row << new QStandardItem(service.getDescription());
    row << new QStandardItem(QString::number(service.getBasePrice(), 'f', 2));
    row << new QStandardItem(QString::number(service.getDurationDays()));
    serviceTableModel->appendRow(row);
}

int MainWindow::getSelectedServiceId() const {
    QModelIndexList selectedRow = ui->tableViewServices->selectionModel()->selectedRows();

    if (selectedRow.isEmpty()) {
        return -1;
    }

    int rowIndex = selectedRow.first().row();
    QAbstractItemModel* model = ui->tableViewServices->model();
    QModelIndex idIndex = model->index(rowIndex, 0);

    return model->data(idIndex).toInt();
}

QString MainWindow::getServiceSearchRequest() const {
    return ui->lineEditServiceSearch->text();
}

void MainWindow::onAddEmployeeClicked() {
    EmployeeDialog* dialog = DialogFactory::createEmployeeDialog(this);

    if (dialog->exec() == QDialog::Accepted) {
        Employee newEmployee = dialog->getEmployee();
        newEmployee.setEmployeeId(nextEmployeeId);
        nextEmployeeId += 1;
        employees.push_back(newEmployee);
        refreshEmployeesTable();
    }

    delete dialog;
}

void MainWindow::onEditEmployeeClicked() {
    int employeeId = getSelectedEmployeeId();

    if (employeeId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один исполнитель не выбран.");
        return;
    }

    int employeeIndex = facade.findEmployeeIndexById(employees, employeeId);

    if (employeeIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Исполнитель не найден.");
        return;
    }

    EmployeeDialog* dialog = DialogFactory::createEmployeeDialog(this);
    dialog->setEmployee(employees[employeeIndex]);

    if (dialog->exec() == QDialog::Accepted) {
        Employee updatedEmployee = dialog->getEmployee();
        updatedEmployee.setEmployeeId(employeeId);
        employees[employeeIndex] = updatedEmployee;
        refreshEmployeesTable();
    }

    delete dialog;
}

void MainWindow::onDeleteEmployeeClicked() {
    int employeeId = getSelectedEmployeeId();

    if (employeeId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один исполнитель не выбран.");
        return;
    }

    int employeeIndex = facade.findEmployeeIndexById(employees, employeeId);

    if (employeeIndex == -1) {
        QMessageBox::warning(this, "Ошибка", "Исполнитель не найден.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Вы уверены?", "Вы точно хотите удалить исполнителя?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        for (int i = assignments.size() - 1; i >= 0; --i) {
            if (assignments[i].getEmployeeId() == employeeId) {
                assignments.remove(i);
            }
        }

        employees.remove(employeeIndex);
        refreshEmployeesTable();
        refreshOrdersTable();
    }
}

void MainWindow::onRefreshEmployeesClicked() {
    refreshEmployeesTable();
}

void MainWindow::onFindEmployeeClicked() {
    employeeTableModel->removeRows(0, employeeTableModel->rowCount());
    QString userRequest = getEmployeeSearchRequest().trimmed().toLower();

    if (userRequest.isEmpty()) {
        refreshEmployeesTable();
        return;
    }

    for (const Employee& employee : employees) {
        bool matches = false;
        matches |= QString::number(employee.getEmployeeId()).contains(userRequest);
        matches |= employee.getFullName().toLower().contains(userRequest);
        matches |= employee.getRole().toLower().contains(userRequest);
        matches |= employee.getPhone().toLower().contains(userRequest);
        matches |= employee.getEmail().toLower().contains(userRequest);

        if (matches) {
            appendEmployeeToTable(employee);
        }
    }
}

void MainWindow::refreshEmployeesTable() {
    ui->lineEditEmployeeSearch->setText("");
    employeeTableModel->removeRows(0, employeeTableModel->rowCount());

    for (const Employee& employee : employees) {
        appendEmployeeToTable(employee);
    }
}

void MainWindow::appendEmployeeToTable(const Employee& employee) {
    QList<QStandardItem*> row;
    row << new QStandardItem(QString::number(employee.getEmployeeId()));
    row << new QStandardItem(employee.getFullName());
    row << new QStandardItem(employee.getRole());
    row << new QStandardItem(employee.getPhone());
    row << new QStandardItem(employee.getEmail());
    row << new QStandardItem(QString::number(employee.getExperienceYears()));
    row << new QStandardItem(QString::number(employee.getHourlyRate(), 'f', 2));
    row << new QStandardItem(employee.getIsAvailable() ? "Да" : "Нет");
    employeeTableModel->appendRow(row);
}

int MainWindow::getSelectedEmployeeId() const {
    QModelIndexList selectedRow = ui->tableViewEmployees->selectionModel()->selectedRows();

    if (selectedRow.isEmpty()) {
        return -1;
    }

    int rowIndex = selectedRow.first().row();
    QAbstractItemModel* model = ui->tableViewEmployees->model();
    QModelIndex idIndex = model->index(rowIndex, 0);

    return model->data(idIndex).toInt();
}

QString MainWindow::getEmployeeSearchRequest() const {
    return ui->lineEditEmployeeSearch->text();
}

// настроить параметры таблицы
void MainWindow::setupTableView(QTableView* tableView)
{
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    QHeaderView* header = tableView->horizontalHeader();
    for (int i = 0; i < tableView->model()->columnCount(); ++i) {
        header->setSectionResizeMode(i, QHeaderView::Stretch);
    }
    header->setStretchLastSection(false);

    tableView->verticalHeader()->setVisible(false);
}

// показать заказы выбранного клиента
void MainWindow::onClientOrdersClicked()
{
    int clientId = getSelectedClientId();

    if (clientId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один клиент не выбран.");
        return;
    }

    QString clientName = facade.getClientFullNameById(clients, clientId);
    QString ordersList;

    bool found = false;
    for (const Order& order : orders) {
        if (order.getClientId() == clientId) {
            found = true;
            ordersList += QString("ID заказа: %1, Название: %2, Статус: %3\n")
                .arg(order.getOrderId())
                .arg(order.getTitle())
                .arg(orderStatusToString(order.getStatus()));
        }
    }

    if (!found) {
        QMessageBox::information(this, "Заказы клиента", 
            "У клиента " + clientName + " заказов нет.");
    } else {
        QMessageBox::information(this, "Заказы клиента " + clientName,
            ordersList);
    }
}

// показать заказы выбранных услуги
void MainWindow::onServiceOrdersClicked()
{
    int serviceId = getSelectedServiceId();

    if (serviceId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни одна услуга не выбрана.");
        return;
    }

    QString serviceName = facade.getServiceNameById(services, serviceId);
    QString ordersList;

    bool found = false;
    for (const OrderService& os : orderServices) {
        if (os.getServiceId() == serviceId) {
            found = true;
            int orderIndex = facade.findOrderIndexById(orders, os.getOrderId());
            if (orderIndex != -1) {
                ordersList += QString("ID заказа: %1, Название: %2, Кол-во: %3\n")
                    .arg(os.getOrderId())
                    .arg(orders[orderIndex].getTitle())
                    .arg(os.getQuantity());
            }
        }
    }

    if (!found) {
        QMessageBox::information(this, "Заказы с услугой", 
            "Услуга \"" + serviceName + "\" пока не используется в заказах.");
    } else {
        QMessageBox::information(this, "Заказы с услугой \"" + serviceName + "\"",
            ordersList);
    }
}

// показать заказы выбранного исполнителя
void MainWindow::onEmployeeOrdersClicked()
{
    int employeeId = getSelectedEmployeeId();

    if (employeeId == -1) {
        QMessageBox::warning(this, "Ошибка", "Ни один исполнитель не выбран.");
        return;
    }

    QString employeeName = facade.getEmployeeNameById(employees, employeeId);
    QString ordersList;

    bool found = false;
    for (const Assignment& assignment : assignments) {
        if (assignment.getEmployeeId() == employeeId) {
            found = true;
            int orderIndex = facade.findOrderIndexById(orders, assignment.getOrderId());
            if (orderIndex != -1) {
                ordersList += QString("ID заказа: %1, Название: %2, Роль: %3, Часов: %4\n")
                    .arg(assignment.getOrderId())
                    .arg(orders[orderIndex].getTitle())
                    .arg(assignment.getRoleInOrder())
                    .arg(assignment.getWorkloadHours());
            }
        }
    }

    if (!found) {
        QMessageBox::information(this, "Заказы исполнителя", 
            "Исполнитель \"" + employeeName + "\" пока не назначен на заказы.");
    } else {
        QMessageBox::information(this, "Заказы исполнителя \"" + employeeName + "\"",
            ordersList);
    }
}
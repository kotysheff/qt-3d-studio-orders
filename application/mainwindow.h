#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include "order.h"
#include "service.h"
#include "orderservice.h"
#include "employee.h"
#include "assignment.h"
#include "costcalculationstrategy.h"
#include "dialogfactory.h"
#include "studiofacade.h"

#include <QMainWindow>
#include <QVector>
#include <QStandardItemModel>
#include <QTableView>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    StudioFacade facade;

    // коллекции сущностей
    QVector<Client> clients;
    int nextClientId = 1;
    QStandardItemModel* clientTableModel;

    QVector<Order> orders;
    int nextOrderId = 1;
    QStandardItemModel* orderTableModel;

    QVector<Service> services;
    int nextServiceId = 1;
    QStandardItemModel* serviceTableModel;

    QVector<OrderService> orderServices;
    int nextOrderServiceId = 1;

    QVector<Employee> employees;
    int nextEmployeeId = 1;
    QStandardItemModel* employeeTableModel;

    QVector<Assignment> assignments;
    int nextAssignmentId = 1;

    void refreshClientsTable();
    QString getUserRequest() const;
    int getSelectedClientId() const;
    void appendClientToTable(const Client& client);

    void refreshOrdersTable();
    void appendOrderToTable(const Order& order);
    int getSelectedOrderId() const;
    QString getOrderSearchRequest() const;

    void refreshServicesTable();
    void appendServiceToTable(const Service& service);
    int getSelectedServiceId() const;
    QString getServiceSearchRequest() const;

    void refreshEmployeesTable();
    void appendEmployeeToTable(const Employee& employee);
    int getSelectedEmployeeId() const;
    QString getEmployeeSearchRequest() const;

    void setupTableView(QTableView* tableView);

private slots:
    void onAddClientClicked();
    void onEditClientClicked();
    void onDeleteClientClicked();
    void onRefreshClientClicked();
    void onClientOrdersClicked();
    void onFindClientClicked();

    void onAddOrderClicked();
    void onEditOrderClicked();
    void onDeleteOrderClicked();
    void onRefreshOrdersClicked();
    void onFindOrderClicked();
    void onOrderServicesClicked();
    void onOrderEmployeesClicked();
    void onCalculateOrderCostClicked();

    void onAddServiceClicked();
    void onEditServiceClicked();
    void onDeleteServiceClicked();
    void onRefreshServicesClicked();
    void onFindServiceClicked();
    void onServiceOrdersClicked();

    void onAddEmployeeClicked();
    void onEditEmployeeClicked();
    void onDeleteEmployeeClicked();
    void onRefreshEmployeesClicked();
    void onFindEmployeeClicked();
    void onEmployeeOrdersClicked();
};
#endif // MAINWINDOW_H

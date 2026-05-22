#ifndef DIALOGFACTORY_H
#define DIALOGFACTORY_H

class QWidget;
class StudioDialog;
class ClientDialog;
class OrderDialog;
class ServiceDialog;
class EmployeeDialog;
class OrderServiceDialog;
class AssignmentDialog;

enum class DialogType {
    Client,
    Order,
    Service,
    Employee,
    OrderService,
    Assignment
};

class DialogFactory
{
public:
    static StudioDialog* createDialog(DialogType type, QWidget* parent = nullptr);

    static ClientDialog* createClientDialog(QWidget* parent = nullptr);
    static OrderDialog* createOrderDialog(QWidget* parent = nullptr);
    static ServiceDialog* createServiceDialog(QWidget* parent = nullptr);
    static EmployeeDialog* createEmployeeDialog(QWidget* parent = nullptr);
    static OrderServiceDialog* createOrderServiceDialog(QWidget* parent = nullptr);
    static AssignmentDialog* createAssignmentDialog(QWidget* parent = nullptr);
};

#endif // DIALOGFACTORY_H
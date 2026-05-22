#include "dialogfactory.h"
#include "studiodialog.h"
#include "clientdialog.h"
#include "orderdialog.h"
#include "servicedialog.h"
#include "employeedialog.h"
#include "orderservicedialog.h"
#include "assignmentdialog.h"

StudioDialog* DialogFactory::createDialog(DialogType type, QWidget* parent)
{
    switch (type) {
    case DialogType::Client:
        return new ClientDialog(parent);

    case DialogType::Order:
        return new OrderDialog(parent);

    case DialogType::Service:
        return new ServiceDialog(parent);

    case DialogType::Employee:
        return new EmployeeDialog(parent);

    case DialogType::OrderService:
        return new OrderServiceDialog(parent);

    case DialogType::Assignment:
        return new AssignmentDialog(parent);
    }

    return nullptr;
}

ClientDialog* DialogFactory::createClientDialog(QWidget* parent)
{
    return static_cast<ClientDialog*>(createDialog(DialogType::Client, parent));
}

OrderDialog* DialogFactory::createOrderDialog(QWidget* parent)
{
    return static_cast<OrderDialog*>(createDialog(DialogType::Order, parent));
}

ServiceDialog* DialogFactory::createServiceDialog(QWidget* parent)
{
    return static_cast<ServiceDialog*>(createDialog(DialogType::Service, parent));
}

EmployeeDialog* DialogFactory::createEmployeeDialog(QWidget* parent)
{
    return static_cast<EmployeeDialog*>(createDialog(DialogType::Employee, parent));
}

OrderServiceDialog* DialogFactory::createOrderServiceDialog(QWidget* parent)
{
    return static_cast<OrderServiceDialog*>(createDialog(DialogType::OrderService, parent));
}

AssignmentDialog* DialogFactory::createAssignmentDialog(QWidget* parent)
{
    return static_cast<AssignmentDialog*>(createDialog(DialogType::Assignment, parent));
}
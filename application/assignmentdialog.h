#ifndef ASSIGNMENTDIALOG_H
#define ASSIGNMENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVector>
#include "assignment.h"
#include "employee.h"
#include "studiodialog.h"

// диалог для назначения сотрудника на заказ
class AssignmentDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit AssignmentDialog(QWidget *parent = nullptr);
    ~AssignmentDialog() = default;

    QString getDialogName() const override;

    void setOrderId(int orderId);
    void setEmployees(const QVector<Employee>& employees);
    Assignment getAssignment() const;
    void setAssignment(const Assignment& assignment);

private slots:
    void onSaveClicked();

private:
    QComboBox *comboBoxEmployee;
    QLineEdit *lineEditRoleInOrder;
    QDateEdit *dateEditAssignmentDate;
    QSpinBox *spinBoxWorkloadHours;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    int currentOrderId = -1;
    QVector<Employee> employees;
};

#endif // ASSIGNMENTDIALOG_H

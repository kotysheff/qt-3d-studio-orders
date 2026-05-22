#ifndef EMPLOYEEDIALOG_H
#define EMPLOYEEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include "employee.h"
#include "studiodialog.h"

// диалог для создания/редактирования сотрудника
class EmployeeDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit EmployeeDialog(QWidget *parent = nullptr);
    ~EmployeeDialog() = default;

    QString getDialogName() const override;

    Employee getEmployee() const;
    void setEmployee(const Employee& employee);

private slots:
    void onSaveClicked();

private:
    QLineEdit *lineEditFullName;
    QLineEdit *lineEditRole;
    QLineEdit *lineEditPhone;
    QLineEdit *lineEditEmail;
    QSpinBox *spinBoxExperienceYears;
    QDoubleSpinBox *doubleSpinBoxHourlyRate;
    QCheckBox *checkBoxIsAvailable;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
};

#endif // EMPLOYEEDIALOG_H

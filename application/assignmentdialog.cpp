#include "assignmentdialog.h"
#include <QMessageBox>
#include <QDate>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// реализация AssignmentDialog - диалог для назначения сотрудника на заказ

// конструктор создаёт UI с выбором сотрудника, роли и нагрузки
AssignmentDialog::AssignmentDialog(QWidget *parent)
    : StudioDialog(parent)
{
    setWindowTitle("Назначить исполнителя на заказ");
    setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("Исполнитель:"));
    comboBoxEmployee = new QComboBox();
    layout->addWidget(comboBoxEmployee);
    
    layout->addWidget(new QLabel("Роль в заказе:"));
    lineEditRoleInOrder = new QLineEdit();
    layout->addWidget(lineEditRoleInOrder);
    
    layout->addWidget(new QLabel("Дата назначения:"));
    dateEditAssignmentDate = new QDateEdit();
    dateEditAssignmentDate->setCalendarPopup(true);
    dateEditAssignmentDate->setDate(QDate::currentDate());
    layout->addWidget(dateEditAssignmentDate);
    
    layout->addWidget(new QLabel("Нагрузка (часы):"));
    spinBoxWorkloadHours = new QSpinBox();
    spinBoxWorkloadHours->setMinimum(1);
    spinBoxWorkloadHours->setMaximum(10000);
    layout->addWidget(spinBoxWorkloadHours);
    
    layout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSave = new QPushButton("Сохранить");
    pushButtonCancel = new QPushButton("Отмена");
    buttonLayout->addWidget(pushButtonSave);
    buttonLayout->addWidget(pushButtonCancel);
    layout->addLayout(buttonLayout);
    
    connect(pushButtonSave, &QPushButton::clicked, this, &AssignmentDialog::onSaveClicked);
    connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// установить ID заказа для нового назначения
void AssignmentDialog::setOrderId(int orderId) {
    currentOrderId = orderId;
}

// установить список доступных сотрудников в комбобокс
void AssignmentDialog::setEmployees(const QVector<Employee>& employeesList) {
    employees = employeesList;
    comboBoxEmployee->clear();
    
    for (const Employee& employee : employees) {
        QString displayText = QString::number(employee.getEmployeeId()) + " — " + 
                             employee.getFullName() + ", " + employee.getRole();
        comboBoxEmployee->addItem(displayText);
    }
}

// получить назначение из полей диалога
Assignment AssignmentDialog::getAssignment() const {
    int employeeId = -1;
    
    if (comboBoxEmployee->currentIndex() >= 0 && comboBoxEmployee->currentIndex() < employees.size()) {
        employeeId = employees[comboBoxEmployee->currentIndex()].getEmployeeId();
    }
    
    QString roleInOrder = lineEditRoleInOrder->text();
    QDate assignmentDate = dateEditAssignmentDate->date();
    int workloadHours = spinBoxWorkloadHours->value();
    
    return Assignment(0, currentOrderId, employeeId, roleInOrder, assignmentDate, workloadHours);
}

// установить назначение во все поля диалога для редактирования
void AssignmentDialog::setAssignment(const Assignment& assignment) {
    for (int i = 0; i < employees.size(); ++i) {
        if (employees[i].getEmployeeId() == assignment.getEmployeeId()) {
            comboBoxEmployee->setCurrentIndex(i);
            break;
        }
    }
    
    lineEditRoleInOrder->setText(assignment.getRoleInOrder());
    dateEditAssignmentDate->setDate(assignment.getAssignmentDate());
    spinBoxWorkloadHours->setValue(assignment.getWorkloadHours());
}

// проверить введённые данные и сохранить назначение
void AssignmentDialog::onSaveClicked() {
    if (comboBoxEmployee->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите исполнителя.");
        return;
    }
    
    if (lineEditRoleInOrder->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Роль в заказе не может быть пустой.");
        return;
    }
    
    if (spinBoxWorkloadHours->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Нагрузка должна быть больше 0.");
        return;
    }
    
    accept();
}

QString AssignmentDialog::getDialogName() const
{
    return "AssignmentDialog";
}

#include "employeedialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// реализация EmployeeDialog - диалог для создания/редактирования сотрудника

// конструктор создаёт UI диалога с полями ФИО, роли, контактов и ставок
EmployeeDialog::EmployeeDialog(QWidget *parent)
    : StudioDialog(parent)
{
    setWindowTitle("Данные исполнителя");
    setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("ФИО:"));
    lineEditFullName = new QLineEdit();
    layout->addWidget(lineEditFullName);
    
    layout->addWidget(new QLabel("Роль:"));
    lineEditRole = new QLineEdit();
    layout->addWidget(lineEditRole);
    
    layout->addWidget(new QLabel("Телефон:"));
    lineEditPhone = new QLineEdit();
    QRegularExpression phoneRegex("^\\+?[0-9\\s\\-\\(\\)]{10,}$");
    lineEditPhone->setValidator(new QRegularExpressionValidator(phoneRegex, this));
    layout->addWidget(lineEditPhone);
    
    layout->addWidget(new QLabel("Email:"));
    lineEditEmail = new QLineEdit();
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    lineEditEmail->setValidator(new QRegularExpressionValidator(emailRegex, this));
    layout->addWidget(lineEditEmail);
    
    layout->addWidget(new QLabel("Опыт (годы):"));
    spinBoxExperienceYears = new QSpinBox();
    spinBoxExperienceYears->setMinimum(0);
    spinBoxExperienceYears->setMaximum(80);
    layout->addWidget(spinBoxExperienceYears);
    
    layout->addWidget(new QLabel("Почасовая ставка:"));
    doubleSpinBoxHourlyRate = new QDoubleSpinBox();
    doubleSpinBoxHourlyRate->setMinimum(0);
    doubleSpinBoxHourlyRate->setMaximum(1000000);
    doubleSpinBoxHourlyRate->setDecimals(2);
    layout->addWidget(doubleSpinBoxHourlyRate);
    
    checkBoxIsAvailable = new QCheckBox("Доступен для новых задач");
    layout->addWidget(checkBoxIsAvailable);
    
    layout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSave = new QPushButton("Сохранить");
    pushButtonCancel = new QPushButton("Отмена");
    buttonLayout->addWidget(pushButtonSave);
    buttonLayout->addWidget(pushButtonCancel);
    layout->addLayout(buttonLayout);
    
    connect(pushButtonSave, &QPushButton::clicked, this, &EmployeeDialog::onSaveClicked);
    connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// получить данные сотрудника из всех полей диалога
Employee EmployeeDialog::getEmployee() const {
    QString fullName = lineEditFullName->text();
    QString role = lineEditRole->text();
    QString phone = lineEditPhone->text();
    QString email = lineEditEmail->text();
    int experienceYears = spinBoxExperienceYears->value();
    double hourlyRate = doubleSpinBoxHourlyRate->value();
    bool isAvailable = checkBoxIsAvailable->isChecked();
    
    return Employee(0, fullName, role, phone, email, experienceYears, hourlyRate, isAvailable);
}

// установить данные сотрудника во все поля диалога для редактирования
void EmployeeDialog::setEmployee(const Employee& employee) {
    lineEditFullName->setText(employee.getFullName());
    lineEditRole->setText(employee.getRole());
    lineEditPhone->setText(employee.getPhone());
    lineEditEmail->setText(employee.getEmail());
    spinBoxExperienceYears->setValue(employee.getExperienceYears());
    doubleSpinBoxHourlyRate->setValue(employee.getHourlyRate());
    checkBoxIsAvailable->setChecked(employee.getIsAvailable());
}

// проверить введённые данные и сохранить сотрудника
void EmployeeDialog::onSaveClicked() {
    if (lineEditFullName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "ФИО не может быть пустым.");
        return;
    }
    
    if (lineEditRole->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Роль не может быть пустой.");
        return;
    }
    
    if (lineEditPhone->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Телефон не может быть пустым.");
        return;
    }
    
    if (!lineEditPhone->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный номер телефона.");
        return;
    }
    
    if (lineEditEmail->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Email не может быть пустым.");
        return;
    }
    
    if (!lineEditEmail->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный email.");
        return;
    }
    
    accept();
}

QString EmployeeDialog::getDialogName() const
{
    return "EmployeeDialog";
}

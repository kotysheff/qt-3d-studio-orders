#include "servicedialog.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// реализация ServiceDialog - диалог для создания/редактирования услуги

// конструктор создаёт UI диалога с полями названия, описания, цены и длительности
ServiceDialog::ServiceDialog(QWidget *parent)
    : StudioDialog(parent)
{
    setWindowTitle("Данные услуги");
    setMinimumWidth(400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    layout->addWidget(new QLabel("Название:"));
    lineEditName = new QLineEdit();
    layout->addWidget(lineEditName);
    
    layout->addWidget(new QLabel("Описание:"));
    plainTextEditDescription = new QPlainTextEdit();
    layout->addWidget(plainTextEditDescription);
    
    layout->addWidget(new QLabel("Базовая цена:"));
    doubleSpinBoxBasePrice = new QDoubleSpinBox();
    doubleSpinBoxBasePrice->setMinimum(0);
    doubleSpinBoxBasePrice->setMaximum(100000000);
    doubleSpinBoxBasePrice->setDecimals(2);
    layout->addWidget(doubleSpinBoxBasePrice);
    
    layout->addWidget(new QLabel("Длительность (дни):"));
    spinBoxDurationDays = new QSpinBox();
    spinBoxDurationDays->setMinimum(1);
    spinBoxDurationDays->setMaximum(365);
    layout->addWidget(spinBoxDurationDays);
    
    layout->addSpacing(10);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    pushButtonSave = new QPushButton("Сохранить");
    pushButtonCancel = new QPushButton("Отмена");
    buttonLayout->addWidget(pushButtonSave);
    buttonLayout->addWidget(pushButtonCancel);
    layout->addLayout(buttonLayout);
    
    connect(pushButtonSave, &QPushButton::clicked, this, &ServiceDialog::onSaveClicked);
    connect(pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// получить данные услуги из всех полей диалога
Service ServiceDialog::getService() const {
    QString name = lineEditName->text();
    QString description = plainTextEditDescription->toPlainText();
    double basePrice = doubleSpinBoxBasePrice->value();
    int durationDays = spinBoxDurationDays->value();
    
    return Service(0, name, description, basePrice, durationDays);
}

// установить данные услуги во все поля диалога для редактирования
void ServiceDialog::setService(const Service& service) {
    lineEditName->setText(service.getName());
    plainTextEditDescription->setPlainText(service.getDescription());
    doubleSpinBoxBasePrice->setValue(service.getBasePrice());
    spinBoxDurationDays->setValue(service.getDurationDays());
}

// проверить введённые данные и сохранить услугу
void ServiceDialog::onSaveClicked() {
    if (lineEditName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Название услуги не может быть пустым.");
        return;
    }
    
    if (doubleSpinBoxBasePrice->value() < 0) {
        QMessageBox::warning(this, "Ошибка", "Базовая цена не может быть отрицательной.");
        return;
    }
    
    if (spinBoxDurationDays->value() <= 0) {
        QMessageBox::warning(this, "Ошибка", "Длительность должна быть больше 0.");
        return;
    }
    
    accept();
}

QString ServiceDialog::getDialogName() const
{
    return "ServiceDialog";
}

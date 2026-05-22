#include "clientdialog.h"
#include "ui_clientdialog.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

// реализация ClientDialog - диалог для создания/редактирования клиента

// конструктор инициализирует UI и устанавливает валидаторы для всех полей ввода
ClientDialog::ClientDialog(QWidget *parent)
    : StudioDialog(parent)
    , ui(new Ui::ClientDialog)
{
    ui->setupUi(this);

    connect(ui->pushButtonSave, &QPushButton::clicked, this, &ClientDialog::onSaveClicked);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);

    QRegularExpression numberRegex("^\\+?\\s*\\d{1,4}\\s*[-.\\s]?\\(?\\d{3,5}\\)?\\s*[-.\\s]?\\d{2,7}(\\s*[-.\\s]?\\d{1,4})*$");
    QRegularExpressionValidator *numberValidator = new QRegularExpressionValidator(numberRegex, this);

    QRegularExpression nameRegex("^[a-zA-Zа-яА-ЯёЁ\\s\\-]{2,50}$");
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(nameRegex, this);

    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6}$",
        QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(emailRegex, this);

    ui->lineEditPhone->setValidator(numberValidator);
    ui->lineEditFirstName->setValidator(nameValidator);
    ui->lineEditLastName->setValidator(nameValidator);
    ui->lineEditEmail->setValidator(emailValidator);
    ui->lineEditCountry->setValidator(nameValidator);
}

// деструктор удаляет UI
ClientDialog::~ClientDialog()
{
    delete ui;
}

// получить данные клиента из всех полей диалога
Client ClientDialog::getClient() const {
    QString firstName = ui->lineEditFirstName->text();
    QString lastName = ui->lineEditLastName->text();
    QString phone = ui->lineEditPhone->text();
    QString email = ui->lineEditEmail->text();
    QString country = ui->lineEditCountry->text();
    QDate registrationDate = ui->dateEditRegistrationDate->date();

    return Client(0, firstName, lastName, phone, email, country, registrationDate);
}

// установить данные клиента во все поля диалога для редактирования
void ClientDialog::setClient(const Client& client) {
    ui->lineEditFirstName->setText(client.getFirstName());
    ui->lineEditLastName->setText(client.getLastName());
    ui->lineEditPhone->setText(client.getPhone());
    ui->lineEditEmail->setText(client.getEmail());
    ui->lineEditCountry->setText(client.getCountry());
    ui->dateEditRegistrationDate->setDate(client.getRegistrationDate());
}

// проверить введённые данные и сохранить клиента
void ClientDialog::onSaveClicked() {
    if (ui->lineEditFirstName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Имя не может быть пустым.");
        return;
    }

    if (ui->lineEditLastName->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Фамилия не может быть пустой.");
        return;
    }

    if (ui->lineEditPhone->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Телефон не может быть пустым.");
        return;
    }

    if (ui->lineEditEmail->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Email не может быть пустым.");
        return;
    }

    if (ui->lineEditCountry->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Страна не может быть пустой.");
        return;
    }

    if (!ui->lineEditFirstName->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректное имя.");
        return;
    }

    if (!ui->lineEditLastName->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректная фамилия.");
        return;
    }

    if (!ui->lineEditPhone->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный телефон.");
        return;
    }

    if (!ui->lineEditEmail->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный email.");
        return;
    }

    if (!ui->lineEditCountry->hasAcceptableInput()) {
        QMessageBox::warning(this, "Ошибка", "Некорректная страна.");
        return;
    }

    accept();
}

QString ClientDialog::getDialogName() const
{
    return "ClientDialog";
}

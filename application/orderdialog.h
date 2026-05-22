#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVector>
#include "order.h"
#include "client.h"
#include "studiodialog.h"

// диалог для создания/редактирования заказа
class OrderDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(QWidget *parent = nullptr);
    ~OrderDialog() = default;

    QString getDialogName() const override;

    Order getOrder() const;
    void setOrder(const Order& order);
    void setClients(const QVector<Client>& clients);


private slots:
    void onSaveClicked();

private:
    QComboBox *comboBoxClient;
    QLineEdit *lineEditTitle;
    QPlainTextEdit *plainTextEditDescription;
    QDateEdit *dateEditCreatedDate;
    QDateEdit *dateEditDeadline;
    QDoubleSpinBox *doubleSpinBoxTotalCost;
    QComboBox *comboBoxStatus;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
    QVector<Client> clients;
};

#endif // ORDERDIALOG_H

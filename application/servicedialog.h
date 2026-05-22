#ifndef SERVICEDIALOG_H
#define SERVICEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include "service.h"
#include "studiodialog.h"

// диалог для создания/редактирования услуги
class ServiceDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit ServiceDialog(QWidget *parent = nullptr);
    ~ServiceDialog() = default;

    QString getDialogName() const override;

    Service getService() const;
    void setService(const Service& service);

private slots:
    void onSaveClicked();

private:
    QLineEdit *lineEditName;
    QPlainTextEdit *plainTextEditDescription;
    QDoubleSpinBox *doubleSpinBoxBasePrice;
    QSpinBox *spinBoxDurationDays;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonCancel;
};

#endif // SERVICEDIALOG_H

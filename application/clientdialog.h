#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include "studiodialog.h"
#include "client.h"

namespace Ui {
class ClientDialog;
}

// диалог для создания/редактирования клиента
class ClientDialog : public StudioDialog
{
    Q_OBJECT

public:
    explicit ClientDialog(QWidget *parent = nullptr);
    ~ClientDialog();

    QString getDialogName() const override;

    Client getClient() const;
    void setClient(const Client& client);

private slots:
    void onSaveClicked();

private:
    Ui::ClientDialog *ui;
};

#endif // CLIENTDIALOG_H

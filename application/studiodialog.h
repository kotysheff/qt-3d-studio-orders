#ifndef STUDIODIALOG_H
#define STUDIODIALOG_H

#include <QDialog>
#include <QString>

class StudioDialog : public QDialog
{
public:
    explicit StudioDialog(QWidget* parent = nullptr)
        : QDialog(parent)
    {
    }

    ~StudioDialog() override = default;

    virtual QString getDialogName() const = 0;
};

#endif // STUDIODIALOG_H
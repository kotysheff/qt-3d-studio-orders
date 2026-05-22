#ifndef SERVICE_H
#define SERVICE_H

#include <QString>

// представляет услугу в каталоге
class Service
{
private:
    int serviceId;
    QString name;
    QString description;
    double basePrice;
    int durationDays;

public:
    Service() = default;
    Service(int serviceId, const QString& name, const QString& description, 
            double basePrice, int durationDays);
    ~Service() = default;

    int getServiceId() const;
    const QString& getName() const;
    const QString& getDescription() const;
    double getBasePrice() const;
    int getDurationDays() const;

    void setServiceId(int newServiceId);
    void setName(const QString& newName);
    void setDescription(const QString& newDescription);
    void setBasePrice(double newBasePrice);
    void setDurationDays(int newDurationDays);
};

#endif // SERVICE_H

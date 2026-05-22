#include "service.h"

// реализация Service - представляет услугу в каталоге

// конструктор инициализирует все поля услуги
Service::Service(int serviceId, const QString& name, const QString& description, 
                 double basePrice, int durationDays)
    : serviceId(serviceId), name(name), description(description), 
      basePrice(basePrice), durationDays(durationDays) {}

// получить ID услуги
int Service::getServiceId() const {
    return serviceId;
}

// получить название услуги
const QString& Service::getName() const {
    return name;
}

// получить описание услуги
const QString& Service::getDescription() const {
    return description;
}

// получить базовую цену услуги
double Service::getBasePrice() const {
    return basePrice;
}

// получить длительность в днях
int Service::getDurationDays() const {
    return durationDays;
}

// установить новый ID услуги
void Service::setServiceId(int newServiceId) {
    serviceId = newServiceId;
}

// установить название услуги
void Service::setName(const QString& newName) {
    name = newName;
}

// установить описание услуги
void Service::setDescription(const QString& newDescription) {
    description = newDescription;
}

// установить базовую цену
void Service::setBasePrice(double newBasePrice) {
    basePrice = newBasePrice;
}

// установить длительность в днях
void Service::setDurationDays(int newDurationDays) {
    durationDays = newDurationDays;
}

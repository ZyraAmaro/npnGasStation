#ifndef GASOLINESTATION_H
#define GASOLINESTATION_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Gasoline class definition
class Gasoline {
public:
    Gasoline(const std::string& type, double pricePerGallon)
        : type(type), pricePerGallon(pricePerGallon) {
    }

    std::string getType() const { return type; }
    double getPricePerGallon() const { return pricePerGallon; }

private:
    std::string type;
    double pricePerGallon;
};

// PaymentMethod class definition
class PaymentMethod {
public:
    virtual bool processPayment(double amount) = 0; // Pure virtual function
    virtual ~PaymentMethod() = default; // Virtual destructor
};

#endif // GASOLINESTATION_H

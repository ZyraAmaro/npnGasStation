// GASOLINESTATION.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "GasolineStation.h"

class CashPayment : public PaymentMethod {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing cash payment of $" << amount << std::endl;
        return true; // Assume payment is always successful for simplicity
    }
};

class CardPayment : public PaymentMethod {
public:
    bool processPayment(double amount) override {
        std::cout << "Processing card payment of $" << amount << std::endl;
        return true; // Assume payment is always successful for simplicity
    }
};

// GasolineStation class definition
class GasolineStation {
public:
    void addGasoline(const Gasoline& gasoline) {
        gasolines.push_back(gasoline);
    }

    void displayGasolines() const {
        std::cout << "Available gasoline types:\n";
        for (const auto& gasoline : gasolines) {
            std::cout << gasoline.getType() << " - $" << gasoline.getPricePerGallon() << " per gallon\n";
        }
    }

    void purchase(const std::string& gasolineType, double gallons, std::unique_ptr<PaymentMethod>& paymentMethod) {
        for (const auto& gasoline : gasolines) {
            if (gasoline.getType() == gasolineType) {
                double totalCost = gallons * gasoline.getPricePerGallon();
                if (paymentMethod->processPayment(totalCost)) {
                    std::cout << "Purchased " << gallons << " gallons of " << gasoline.getType() << std::endl;
                }
                return;
            }
        }
        std::cout << "Gasoline type " << gasolineType << " not found!" << std::endl;
    }

private:
    std::vector<Gasoline> gasolines;
};

// Main function
int main() {
    GasolineStation station;

    // Add gasoline types to the station
    station.addGasoline(Gasoline("Regular", 3.00));
    station.addGasoline(Gasoline("Mid-Grade", 3.50));
    station.addGasoline(Gasoline("Premium", 4.00));

    // Display available gasoline types
    station.displayGasolines();

    std::string gasolineType;
    double gallons;
    int paymentChoice;
    char continueChoice;

    do {
        // Prompt user for gasoline type and amount
        std::cout << "Enter gasoline type to purchase: ";
        std::cin >> gasolineType;
        std::cout << "Enter amount in gallons: ";
        std::cin >> gallons;

        // Choose payment method
        std::cout << "Choose payment method (1: Cash, 2: Card): ";
        std::cin >> paymentChoice;

        std::unique_ptr<PaymentMethod> paymentMethod;
        if (paymentChoice == 1) {
            paymentMethod = std::make_unique<CashPayment>();
        }
        else if (paymentChoice == 2) {
            paymentMethod = std::make_unique<CardPayment>();
        }
        else {
            std::cout << "Invalid payment method!" << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        // Attempt to purchase the gasoline
        station.purchase(gasolineType, gallons, paymentMethod);

        // Ask if the user wants to continue
        std::cout << "Do you want to make another purchase? (y/n): ";
        std::cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    std::cout << "Thank you for using the gasoline station!" << std::endl;

    return 0;
}
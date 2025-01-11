#include <iostream>
#include <string>

// Example 1: Employee Management System
class Employee {
protected:
    std::string name;
    int id;
    double baseSalary;

public:
    Employee(std::string n, int i, double s) : 
        name(n), id(i), baseSalary(s) {}

    virtual double calculateSalary() {
        return baseSalary;
    }

    virtual void displayInfo() {
        std::cout << "Name: " << name << "\nID: " << id 
                 << "\nBase Salary: " << baseSalary << std::endl;
    }
};

class Manager : public Employee {
private:
    double bonus;
    int teamSize;

public:
    Manager(std::string n, int i, double s, double b, int t) : 
        Employee(n, i, s), bonus(b), teamSize(t) {}

    double calculateSalary() override {
        return baseSalary + bonus + (teamSize * 1000); // Extra per team member
    }

    void displayInfo() override {
        Employee::displayInfo();
        std::cout << "Team Size: " << teamSize 
                 << "\nBonus: " << bonus << std::endl;
    }
};

class Developer : public Employee {
private:
    std::string programmingLanguage;
    int overtimeHours;

public:
    Developer(std::string n, int i, double s, std::string lang, int ot) :
        Employee(n, i, s), programmingLanguage(lang), overtimeHours(ot) {}

    double calculateSalary() override {
        return baseSalary + (overtimeHours * 100); // Overtime pay
    }

    void displayInfo() override {
        Employee::displayInfo();
        std::cout << "Programming Language: " << programmingLanguage 
                 << "\nOvertime Hours: " << overtimeHours << std::endl;
    }
};

// Example 2: Vehicle Management System
class Vehicle {
protected:
    std::string brand;
    std::string model;
    int year;
    double basePrice;

public:
    Vehicle(std::string b, std::string m, int y, double p) :
        brand(b), model(m), year(y), basePrice(p) {}

    virtual double calculatePrice() {
        return basePrice;
    }

    virtual void displaySpecs() {
        std::cout << "Brand: " << brand << "\nModel: " << model
                 << "\nYear: " << year << "\nBase Price: " << basePrice << std::endl;
    }
};

class ElectricCar : public Vehicle {
private:
    int batteryCapacity;
    int range;

public:
    ElectricCar(std::string b, std::string m, int y, double p, 
                int bc, int r) :
        Vehicle(b, m, y, p), batteryCapacity(bc), range(r) {}

    double calculatePrice() override {
        return basePrice + (batteryCapacity * 100); // Premium for battery size
    }

    void displaySpecs() override {
        Vehicle::displaySpecs();
        std::cout << "Battery Capacity: " << batteryCapacity << " kWh"
                 << "\nRange: " << range << " miles" << std::endl;
    }
};

class LuxuryCar : public Vehicle {
private:
    bool hasMassageSeats;
    bool hasAutoPilot;

public:
    LuxuryCar(std::string b, std::string m, int y, double p,
              bool ms, bool ap) :
        Vehicle(b, m, y, p), hasMassageSeats(ms), hasAutoPilot(ap) {}

    double calculatePrice() override {
        double price = basePrice;
        if (hasMassageSeats) price += 5000;
        if (hasAutoPilot) price += 8000;
        return price;
    }

    void displaySpecs() override {
        Vehicle::displaySpecs();
        std::cout << "Massage Seats: " << (hasMassageSeats ? "Yes" : "No")
                 << "\nAutoPilot: " << (hasAutoPilot ? "Yes" : "No") << std::endl;
    }
};

int main() {
    // Testing Employee Management System
    Manager manager("John Doe", 1, 100000, 20000, 5);
    Developer developer("Jane Smith", 2, 80000, "C++", 20);

    std::cout << "Manager Information:\n";
    manager.displayInfo();
    std::cout << "Total Salary: " << manager.calculateSalary() << "\n\n";

    std::cout << "Developer Information:\n";
    developer.displayInfo();
    std::cout << "Total Salary: " << developer.calculateSalary() << "\n\n";

    // Testing Vehicle Management System
    ElectricCar tesla("Tesla", "Model 3", 2023, 40000, 75, 350);
    LuxuryCar mercedes("Mercedes", "S-Class", 2023, 90000, true, true);

    std::cout << "Electric Car Information:\n";
    tesla.displaySpecs();
    std::cout << "Final Price: " << tesla.calculatePrice() << "\n\n";

    std::cout << "Luxury Car Information:\n";
    mercedes.displaySpecs();
    std::cout << "Final Price: " << mercedes.calculatePrice() << "\n\n";

    return 0;
}

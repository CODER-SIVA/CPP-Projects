#include <iostream>
#include <vector>
#include <string>

// Example 1: Shape Drawing System (Runtime Polymorphism)
class Shape {
public:
    virtual void draw() const = 0;
    virtual double calculateArea() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    void draw() const override {
        std::cout << "Drawing a Circle with radius " << radius << std::endl;
    }

    double calculateArea() const override {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing a Rectangle with width " << width 
                 << " and height " << height << std::endl;
    }

    double calculateArea() const override {
        return width * height;
    }
};

class Triangle : public Shape {
private:
    double base;
    double height;

public:
    Triangle(double b, double h) : base(b), height(h) {}

    void draw() const override {
        std::cout << "Drawing a Triangle with base " << base 
                 << " and height " << height << std::endl;
    }

    double calculateArea() const override {
        return 0.5 * base * height;
    }
};

// Example 2: Payment Processing System (Both Runtime and Compile-time Polymorphism)
class PaymentProcessor {
public:
    // Method overloading (Compile-time Polymorphism)
    void processPayment(double amount) {
        std::cout << "Processing cash payment of $" << amount << std::endl;
    }

    void processPayment(double amount, std::string creditCardNumber) {
        std::cout << "Processing credit card payment of $" << amount 
                 << " with card " << creditCardNumber << std::endl;
    }

    void processPayment(double amount, std::string bankName, std::string accountNumber) {
        std::cout << "Processing bank transfer of $" << amount 
                 << " from " << bankName << " account " << accountNumber << std::endl;
    }
};

// Runtime Polymorphism for Payment Methods
class PaymentMethod {
public:
    virtual void process(double amount) = 0;
    virtual ~PaymentMethod() {}
};

class CreditCardPayment : public PaymentMethod {
private:
    std::string cardNumber;

public:
    CreditCardPayment(std::string card) : cardNumber(card) {}

    void process(double amount) override {
        std::cout << "Processing Credit Card payment of $" << amount 
                 << " using card ending with " 
                 << cardNumber.substr(cardNumber.length() - 4) << std::endl;
    }
};

class PayPalPayment : public PaymentMethod {
private:
    std::string email;

public:
    PayPalPayment(std::string e) : email(e) {}

    void process(double amount) override {
        std::cout << "Processing PayPal payment of $" << amount 
                 << " using account " << email << std::endl;
    }
};

class CryptoCurrencyPayment : public PaymentMethod {
private:
    std::string walletAddress;

public:
    CryptoCurrencyPayment(std::string wallet) : walletAddress(wallet) {}

    void process(double amount) override {
        std::cout << "Processing Cryptocurrency payment of $" << amount 
                 << " to wallet " << walletAddress << std::endl;
    }
};

int main() {
    // Testing Shape Drawing System
    std::vector<Shape*> shapes;
    shapes.push_back(new Circle(5));
    shapes.push_back(new Rectangle(4, 6));
    shapes.push_back(new Triangle(3, 4));

    std::cout << "Shape Drawing System Demo:\n";
    for (const auto& shape : shapes) {
        shape.draw();
        std::cout << "Area: " << shape.calculateArea() << "\n\n";
    }

    // Cleanup shapes
    for (auto shape : shapes) {
        delete shape;
    }

    // Testing Payment Processing System
    std::cout << "\nPayment Processing System Demo:\n";
    
    // Compile-time Polymorphism (Method Overloading)
    PaymentProcessor processor;
    processor.processPayment(100.0);  // Cash payment
    processor.processPayment(200.0, "1234-5678-9012-3456");  // Credit card payment
    processor.processPayment(300.0, "Chase Bank", "987654321");  // Bank transfer

    // Runtime Polymorphism
    std::vector<PaymentMethod*> paymentMethods;
    paymentMethods.push_back(new CreditCardPayment("4532-7891-2345-6789"));
    paymentMethods.push_back(new PayPalPayment("user@example.com"));
    paymentMethods.push_back(new CryptoCurrencyPayment("0xabc123def456"));

    std::cout << "\nProcessing different payment methods:\n";
    for (const auto& method : paymentMethods) {
        method->process(150.0);
    }

    // Cleanup payment methods
    for (auto method : paymentMethods) {
        delete method;
    }

    return 0;
}

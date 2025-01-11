#include <iostream>
#include <string>

// Without Encapsulation - All data is exposed and can be modified directly
struct BankAccountWithoutEncapsulation {
    double balance;
    std::string accountNumber;
    std::string pin;
};

// Problems:
// 1. Anyone can modify balance directly
// 2. No validation for deposits/withdrawals
// 3. No security checks
void demonstrateProblemWithoutEncapsulation() {
    BankAccountWithoutEncapsulation account;
    account.balance = 1000;
    // Someone can maliciously modify balance
    account.balance = 1000000;  // No protection!
    // Can set invalid values
    account.balance = -50000;   // Shouldn't be possible!
}

// Without Abstraction - Complex implementation details exposed
void playMusicWithoutAbstraction(std::string filename) {
    // User needs to know all these complex steps
    bool audioDriverInitialized = initializeAudioDriver();
    if (!audioDriverInitialized) {
        handleDriverError();
        return;
    }

    AudioBuffer* buffer = allocateAudioBuffer(44100, 16);
    if (!buffer) {
        handleMemoryError();
        return;
    }

    WaveFormat format;
    format.sampleRate = 44100;
    format.bitsPerSample = 16;
    format.channels = 2;

    if (!setAudioFormat(&format)) {
        handleFormatError();
        freeAudioBuffer(buffer);
        return;
    }

    // Many more low-level details...
}

// Without Inheritance - Code duplication
struct Car {
    std::string brand;
    std::string model;
    double price;
    void start() { /* ... */ }
    void stop() { /* ... */ }
};

struct Truck {
    std::string brand;    // Duplicated
    std::string model;    // Duplicated
    double price;         // Duplicated
    void start() { /* ... Duplicated ... */ }
    void stop() { /* ... Duplicated ... */ }
    double cargoCapacity;
};

struct Motorcycle {
    std::string brand;    // Duplicated again
    std::string model;    // Duplicated again
    double price;         // Duplicated again
    void start() { /* ... Duplicated again ... */ }
    void stop() { /* ... Duplicated again ... */ }
    bool hasSidecar;
};

// Without Polymorphism - Complex switch/if-else statements
void drawShapeWithoutPolymorphism(std::string shapeType, double param1, double param2) {
    if (shapeType == "circle") {
        double radius = param1;
        // Draw circle logic
        double area = 3.14159 * radius * radius;
        std::cout << "Drawing circle with area: " << area << std::endl;
    }
    else if (shapeType == "rectangle") {
        double width = param1;
        double height = param2;
        // Draw rectangle logic
        double area = width * height;
        std::cout << "Drawing rectangle with area: " << area << std::endl;
    }
    else if (shapeType == "triangle") {
        double base = param1;
        double height = param2;
        // Draw triangle logic
        double area = 0.5 * base * height;
        std::cout << "Drawing triangle with area: " << area << std::endl;
    }
    // Adding new shapes requires modifying this function
    // Type checking is error-prone
}

// Example of payment processing without polymorphism
void processPaymentWithoutPolymorphism(std::string paymentType, double amount) {
    if (paymentType == "credit_card") {
        // Credit card specific logic
        std::cout << "Processing credit card payment of $" << amount << std::endl;
    }
    else if (paymentType == "paypal") {
        // PayPal specific logic
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
    else if (paymentType == "crypto") {
        // Cryptocurrency specific logic
        std::cout << "Processing crypto payment of $" << amount << std::endl;
    }
    // Adding new payment method requires modifying this function
    // Easy to forget handling a payment type
}

int main() {
    // Demonstrating problems without encapsulation
    BankAccountWithoutEncapsulation account;
    account.balance = -1000;  // Invalid state possible
    
    // Demonstrating problems without abstraction
    playMusicWithoutAbstraction("song.mp3");  // Too complex for users
    
    // Demonstrating problems without inheritance
    Car car;
    Truck truck;
    Motorcycle motorcycle;
    // Lots of duplicated code and maintenance overhead
    
    // Demonstrating problems without polymorphism
    drawShapeWithoutPolymorphism("circle", 5.0, 0.0);
    drawShapeWithoutPolymorphism("rectangle", 4.0, 6.0);
    processPaymentWithoutPolymorphism("credit_card", 100.0);
    
    return 0;
}

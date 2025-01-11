#include <iostream>
#include <string>

// Example 1: Bank Account System
class BankAccount {
private:
    double balance;
    std::string accountNumber;
    std::string pin;

public:
    BankAccount(std::string accNum, std::string initialPin) : 
        balance(0.0), accountNumber(accNum), pin(initialPin) {}

    bool deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            return true;
        }
        return false;
    }

    bool withdraw(double amount, std::string inputPin) {
        if (inputPin == pin && amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    double getBalance(std::string inputPin) {
        if (inputPin == pin) {
            return balance;
        }
        return -1; // Invalid PIN
    }
};

// Example 2: Smartphone System
class Smartphone {
private:
    bool isLocked;
    std::string password;
    int batteryLevel;
    bool isCharging;

public:
    Smartphone(std::string initialPassword) : 
        isLocked(true), password(initialPassword), batteryLevel(100), isCharging(false) {}

    bool unlockPhone(std::string inputPassword) {
        if (inputPassword == password) {
            isLocked = false;
            return true;
        }
        return false;
    }

    void lockPhone() {
        isLocked = true;
    }

    bool makeCall(std::string number) {
        if (!isLocked && batteryLevel > 5) {
            std::cout << "Calling " << number << "...\n";
            batteryLevel -= 2;
            return true;
        }
        return false;
    }

    void chargeBattery() {
        isCharging = true;
        if (batteryLevel < 100) {
            batteryLevel += 10;
            if (batteryLevel > 100) batteryLevel = 100;
        }
    }
};

int main() {
    // Testing BankAccount
    BankAccount account("ACC123", "1234");
    account.deposit(1000);
    std::cout << "Balance: " << account.getBalance("1234") << std::endl;
    account.withdraw(500, "1234");
    std::cout << "New Balance: " << account.getBalance("1234") << std::endl;

    // Testing Smartphone
    Smartphone phone("password123");
    phone.unlockPhone("password123");
    phone.makeCall("123-456-7890");
    phone.chargeBattery();
    phone.lockPhone();

    return 0;
}

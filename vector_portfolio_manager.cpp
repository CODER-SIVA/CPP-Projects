#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <ctime>

// Stock class to represent a single stock investment
class Stock {
private:
    std::string symbol;
    std::string name;
    double purchasePrice;
    double currentPrice;
    int shares;
    std::string purchaseDate;

public:
    Stock(std::string sym, std::string nm, double purPrice, double currPrice, 
          int sh, std::string date) 
        : symbol(sym), name(nm), purchasePrice(purPrice), 
          currentPrice(currPrice), shares(sh), purchaseDate(date) {}
    
    // Getters
    std::string getSymbol() const { return symbol; }
    std::string getName() const { return name; }
    double getPurchasePrice() const { return purchasePrice; }
    double getCurrentPrice() const { return currentPrice; }
    int getShares() const { return shares; }
    std::string getPurchaseDate() const { return purchaseDate; }
    
    // Update current price
    void updatePrice(double newPrice) { currentPrice = newPrice; }
    
    // Add more shares
    void addShares(int additionalShares, double price) {
        // Calculate weighted average price
        double totalValue = purchasePrice * shares + price * additionalShares;
        shares += additionalShares;
        purchasePrice = totalValue / shares;
    }
    
    // Calculate current value
    double getCurrentValue() const { return currentPrice * shares; }
    
    // Calculate purchase value
    double getPurchaseValue() const { return purchasePrice * shares; }
    
    // Calculate profit/loss
    double getProfitLoss() const { return getCurrentValue() - getPurchaseValue(); }
    
    // Calculate profit/loss percentage
    double getProfitLossPercentage() const { 
        return (getProfitLoss() / getPurchaseValue()) * 100.0; 
    }
    
    // Display stock information
    void display() const {
        std::cout << std::left << std::setw(6) << symbol
                  << std::setw(20) << name
                  << std::right << std::setw(8) << shares << " shares"
                  << std::fixed << std::setprecision(2)
                  << " | Bought: $" << std::setw(8) << purchasePrice
                  << " | Current: $" << std::setw(8) << currentPrice
                  << " | P/L: $" << std::setw(9) << getProfitLoss()
                  << " (" << std::setw(6) << getProfitLossPercentage() << "%)"
                  << std::endl;
    }
};

// Portfolio class to manage a collection of stocks
class Portfolio {
private:
    std::vector<Stock> holdings;
    std::string ownerName;

public:
    Portfolio(std::string owner) : ownerName(owner) {}
    
    // Add a new stock to the portfolio
    void addStock(const Stock& stock) {
        // Check if stock already exists
        auto it = std::find_if(holdings.begin(), holdings.end(),
            [&stock](const Stock& s) { return s.getSymbol() == stock.getSymbol(); });
        
        if (it != holdings.end()) {
            // Stock already exists, update shares and average price
            it->addShares(stock.getShares(), stock.getPurchasePrice());
            std::cout << "Added " << stock.getShares() << " shares to existing " 
                      << stock.getSymbol() << " position." << std::endl;
        } else {
            // New stock, add to vector
            holdings.push_back(stock);
            std::cout << "Added new stock: " << stock.getSymbol() << std::endl;
        }
    }
    
    // Remove a stock from the portfolio
    bool sellStock(const std::string& symbol, int sharesToSell) {
        auto it = std::find_if(holdings.begin(), holdings.end(),
            [&symbol](const Stock& s) { return s.getSymbol() == symbol; });
        
        if (it != holdings.end()) {
            if (it->getShares() <= sharesToSell) {
                // Sell all shares (remove from vector)
                std::cout << "Sold all " << it->getShares() << " shares of " 
                          << symbol << std::endl;
                holdings.erase(it);
            } else {
                // Sell partial position (not implemented in this example)
                std::cout << "Partial selling not implemented in this example." << std::endl;
            }
            return true;
        }
        
        std::cout << "Stock " << symbol << " not found in portfolio." << std::endl;
        return false;
    }
    
    // Update stock prices (simulating market changes)
    void updatePrices() {
        // In a real application, this would fetch current prices from an API
        std::cout << "Updating stock prices..." << std::endl;
        
        // Seed random number generator
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        
        for (auto& stock : holdings) {
            // Simulate price change (-5% to +5%)
            double changePercent = (std::rand() % 1000 - 500) / 100.0;
            double oldPrice = stock.getCurrentPrice();
            double newPrice = oldPrice * (1 + changePercent / 100.0);
            
            stock.updatePrice(newPrice);
            
            std::cout << stock.getSymbol() << ": $" << std::fixed << std::setprecision(2) 
                      << oldPrice << " -> $" << newPrice 
                      << " (" << (changePercent >= 0 ? "+" : "") << changePercent << "%)" 
                      << std::endl;
        }
    }
    
    // Sort portfolio by various criteria
    void sortBySymbol() {
        std::sort(holdings.begin(), holdings.end(),
            [](const Stock& a, const Stock& b) { return a.getSymbol() < b.getSymbol(); });
        std::cout << "Portfolio sorted by symbol." << std::endl;
    }
    
    void sortByValue() {
        std::sort(holdings.begin(), holdings.end(),
            [](const Stock& a, const Stock& b) { 
                return a.getCurrentValue() > b.getCurrentValue(); 
            });
        std::cout << "Portfolio sorted by current value (descending)." << std::endl;
    }
    
    void sortByPerformance() {
        std::sort(holdings.begin(), holdings.end(),
            [](const Stock& a, const Stock& b) { 
                return a.getProfitLossPercentage() > b.getProfitLossPercentage(); 
            });
        std::cout << "Portfolio sorted by performance (descending)." << std::endl;
    }
    
    // Calculate total portfolio value
    double getTotalValue() const {
        return std::accumulate(holdings.begin(), holdings.end(), 0.0,
            [](double sum, const Stock& stock) { return sum + stock.getCurrentValue(); });
    }
    
    // Calculate total purchase value
    double getTotalCost() const {
        return std::accumulate(holdings.begin(), holdings.end(), 0.0,
            [](double sum, const Stock& stock) { return sum + stock.getPurchaseValue(); });
    }
    
    // Calculate total profit/loss
    double getTotalProfitLoss() const {
        return getTotalValue() - getTotalCost();
    }
    
    // Display portfolio summary
    void displaySummary() const {
        std::cout << "\n===== Portfolio Summary for " << ownerName << " =====" << std::endl;
        std::cout << "Number of positions: " << holdings.size() << std::endl;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Total investment: $" << getTotalCost() << std::endl;
        std::cout << "Current value: $" << getTotalValue() << std::endl;
        
        double profitLoss = getTotalProfitLoss();
        double profitLossPercent = (profitLoss / getTotalCost()) * 100.0;
        
        std::cout << "Total profit/loss: $" << profitLoss 
                  << " (" << (profitLossPercent >= 0 ? "+" : "") 
                  << profitLossPercent << "%)" << std::endl;
    }
    
    // Display all holdings
    void displayHoldings() const {
        if (holdings.empty()) {
            std::cout << "Portfolio is empty." << std::endl;
            return;
        }
        
        std::cout << "\n===== Current Holdings =====" << std::endl;
        std::cout << std::left << std::setw(6) << "Symbol" 
                  << std::setw(20) << "Name" 
                  << std::right << std::setw(14) << "Shares" 
                  << std::setw(19) << "Buy Price" 
                  << std::setw(19) << "Current Price" 
                  << std::setw(19) << "Profit/Loss" 
                  << std::endl;
        std::cout << std::string(100, '-') << std::endl;
        
        for (const auto& stock : holdings) {
            stock.display();
        }
    }
    
    // Vector size operations demo
    void demonstrateVectorOperations() {
        std::cout << "\n===== Vector Operations Demo =====" << std::endl;
        std::cout << "Current size: " << holdings.size() << " stocks" << std::endl;
        std::cout << "Current capacity: " << holdings.capacity() << std::endl;
        
        // Reserve space
        std::cout << "\nReserving space for 20 stocks..." << std::endl;
        holdings.reserve(20);
        std::cout << "New capacity: " << holdings.capacity() << std::endl;
        std::cout << "Size remains: " << holdings.size() << " (unchanged)" << std::endl;
        
        // Shrink to fit
        std::cout << "\nShrinking capacity to fit size..." << std::endl;
        holdings.shrink_to_fit();
        std::cout << "New capacity after shrink_to_fit: " << holdings.capacity() << std::endl;
        
        // Vector data access
        if (!holdings.empty()) {
            std::cout << "\nDemonstrating element access:" << std::endl;
            std::cout << "First stock (front()): " << holdings.front().getSymbol() << std::endl;
            std::cout << "Last stock (back()): " << holdings.back().getSymbol() << std::endl;
            
            if (holdings.size() > 1) {
                std::cout << "Second stock (index 1): " << holdings[1].getSymbol() << std::endl;
            }
        }
    }
};

// Main function to demonstrate portfolio management
int main() {
    // Create a portfolio
    Portfolio myPortfolio("Investor");
    
    // Add stocks to the portfolio
    myPortfolio.addStock(Stock("AAPL", "Apple Inc.", 150.75, 150.75, 10, "2023-01-15"));
    myPortfolio.addStock(Stock("MSFT", "Microsoft Corp.", 290.35, 290.35, 5, "2023-02-20"));
    myPortfolio.addStock(Stock("GOOGL", "Alphabet Inc.", 2680.70, 2680.70, 2, "2023-03-10"));
    myPortfolio.addStock(Stock("AMZN", "Amazon.com Inc.", 3380.00, 3380.00, 3, "2023-04-05"));
    myPortfolio.addStock(Stock("TSLA", "Tesla Inc.", 710.20, 710.20, 8, "2023-05-12"));
    
    // Display initial portfolio
    std::cout << "\nInitial Portfolio:" << std::endl;
    myPortfolio.displayHoldings();
    myPortfolio.displaySummary();
    
    // Demonstrate vector operations
    myPortfolio.demonstrateVectorOperations();
    
    // Update stock prices (simulate market changes)
    std::cout << "\n===== Market Update =====" << std::endl;
    myPortfolio.updatePrices();
    
    // Display updated portfolio
    std::cout << "\nUpdated Portfolio:" << std::endl;
    myPortfolio.displayHoldings();
    myPortfolio.displaySummary();
    
    // Sort portfolio by different criteria
    std::cout << "\n===== Portfolio Sorting =====" << std::endl;
    
    myPortfolio.sortBySymbol();
    std::cout << "\nSorted by Symbol:" << std::endl;
    myPortfolio.displayHoldings();
    
    myPortfolio.sortByValue();
    std::cout << "\nSorted by Value:" << std::endl;
    myPortfolio.displayHoldings();
    
    myPortfolio.sortByPerformance();
    std::cout << "\nSorted by Performance:" << std::endl;
    myPortfolio.displayHoldings();
    
    // Sell a stock
    std::cout << "\n===== Selling Stocks =====" << std::endl;
    myPortfolio.sellStock("TSLA", 8);
    
    // Display final portfolio
    std::cout << "\nFinal Portfolio:" << std::endl;
    myPortfolio.displayHoldings();
    myPortfolio.displaySummary();
    
    return 0;
}

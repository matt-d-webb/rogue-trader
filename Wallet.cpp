#include <iostream>
#include "Wallet.h"
#include "CSVReader.h"

Wallet::Wallet()
{
}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance = 0.0;

    if (amount < 0)
    {
        throw std::invalid_argument("Amount cannot be negative");
    }

    if (currencies.count(type) == 0)
    {
        balance = 0.0;
    }
    else
    {
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
};

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0)
        return false;

    if (currencies.count(type) == 0)
    {
        std::cout << "Wallet does not contain " << type << std::endl;
        return false;
    }
    else
    {
        if (containsCurrency(type, amount))
        {
            std::cout << "Removing " << amount << " " << type << std::endl;
            currencies[type] -= amount;
            return true;
        }
        else // they have it but not enough
            return false;
    }
};

bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0)
        return false;
    else
        return currencies[type] >= amount;
};

bool Wallet::canFulfillOrder(const OrderBookEntry &order)
{
    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');
    // ask
    if (order.type == OrderBookType::ask)
    {
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Checking if wallet contains " << amount << " " << currency << std::endl;
        return containsCurrency(currency, amount);
    }
    // bid
    if (order.type == OrderBookType::bid)
    {
        double amount = order.amount * order.price;
        std::string currency = currs[1];
        std::cout << "Checking if wallet contains " << amount << " " << currency << std::endl;
        return containsCurrency(currency, amount);
    }
    return false;
}

void Wallet::processSale(OrderBookEntry& sale) {

    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');
    // ask
    if (sale.type == OrderBookType::askSale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    // bid
    if (sale.type == OrderBookType::bidSale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];
       
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

std::string Wallet::toString()
{
    std::string output = "";
    for (std::pair<std::string, double> pair : currencies)
    {
        std::string currency = pair.first;
        double balance = pair.second;

        output += currency + ": " + std::to_string(balance) + "\n";
    }
    return output;
};
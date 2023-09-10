#pragma once
#include <string>

enum class OrderBookType
{
    bid,
    ask,
    unknown,
    sale
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType type;
    static OrderBookType stringToOrderBookType(std::string s);

    static bool compareByTimestamp(OrderBookEntry& obe1, OrderBookEntry& obe2);

    static bool compareByPriceAsc(OrderBookEntry& obe1, OrderBookEntry& obe2);

    static bool compareByPriceDesc(OrderBookEntry& obe1, OrderBookEntry& obe2);

    OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _type);
};
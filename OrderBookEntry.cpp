#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _type)
    : price{_price}, amount(_amount), timestamp(_timestamp), product(_product), type(_type)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
    if(s == "ask") {
        return OrderBookType::ask;
    } else if(s == "bid") {
        return OrderBookType::bid;
    } else if(s == "sale") {
        return OrderBookType::sale;
    } else {
        return OrderBookType::unknown;
    }
};

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& obe1, OrderBookEntry& obe2) {
    return obe1.timestamp < obe2.timestamp;
};

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& obe1, OrderBookEntry& obe2) {
    return obe1.price < obe2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry& obe1, OrderBookEntry& obe2) {
    return obe1.price > obe2.price;
}
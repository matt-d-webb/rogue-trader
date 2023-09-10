#include <string>
#include <vector>
#include <map>

#include "OrderBook.h"
#include "CSVReader.h"
#include "OrderBookEntry.h"

OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
};

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> filteredOrders;
    for (OrderBookEntry &obe : orders)
    {
        if (obe.type == type && obe.product == product && obe.timestamp == timestamp)
        {
            filteredOrders.push_back(obe);
        }
    }
    return filteredOrders;
};

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> knownProducts;
    std::map<std::string, bool> productsMap;

    for (OrderBookEntry &obe : orders)
    {
        productsMap[obe.product] = true;
    }

    for (auto const &e : productsMap)
    {
        knownProducts.push_back(e.first);
    }

    return knownProducts;
};

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for (OrderBookEntry &obe : orders)
    {
        if (obe.price > max)
            max = obe.price;
    }
    return max;
};

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price;
    for (OrderBookEntry &obe : orders)
    {
        if (obe.price < min)
            min = obe.price;
    }
    return min;
};

std::string OrderBook::getEarliestTime()
{
    std::string min = orders[0].timestamp;
    for (OrderBookEntry &obe : orders)
    {
        if (obe.timestamp < min)
            min = obe.timestamp;
    }
    return min;
};

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_time_stamp = "";
    for (OrderBookEntry &obe : orders)
    {
        if (obe.timestamp > timestamp)
        {
            next_time_stamp = obe.timestamp;
            break;
        }
    }
    if (next_time_stamp == "")
    {
        next_time_stamp = orders[0].timestamp;
    }
    return next_time_stamp;
};
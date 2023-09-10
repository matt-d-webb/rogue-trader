#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    //** Initialise the program */
    OrderBook(std::string filename);
    //** return vector of all known products */
    std::vector<std::string> getKnownProducts();
    //** return vector of Orders by filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

    /** returns the earliest time in the OrderBook */
    std::string getEarliestTime();

    /** 
     *  returns the next time after the sent time in the OrderBook
     *  returns the first time stime if no next time is found.
     */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);

private:
    std::vector<OrderBookEntry> orders;

};
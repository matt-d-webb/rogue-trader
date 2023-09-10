#pragma once
#include "OrderBookEntry.h"
#include <vector>

class CSVReader
{
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(std::string filename);
    static std::vector<std::string> tokenise(std::string line, char separator);
    static OrderBookEntry stringsToOBE(std::string price,
                                        std::string amount,
                                        std::string timestamp,
                                        std::string product,
                                        OrderBookType type);
private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};
#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string filename)
{
    std::ifstream csvFile{filename};
    std::vector<OrderBookEntry> entries;

    if (csvFile.is_open())
    {
        std::string line;
        std::getline(csvFile, line);

        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Bad data" << std::endl;
            }
        }
        csvFile.close();
    }
    else
    {
        std::cout << "Could not open CSV file" << std::endl;
    };
    return entries;
};

std::vector<std::string> CSVReader::tokenise(std::string line, char separator)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);
    while (std::getline(tokenStream, token, separator))
    {
        tokens.push_back(token);
    }
    return tokens;
};

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> strings)
{
    double price, amount;

    if (strings.size() != 5)
    {
        std::cout << "Error converting string to OrderBookEntry" << std::endl;
        throw std::exception();
    }

    try
    {
        price = std::stod(strings[3]);
        amount = std::stod(strings[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error converting string to double" << strings[3] << std::endl;
        std::cout << "Error converting string to double" << strings[4] << std::endl;
        throw e;
    }

    OrderBookEntry obe{price, amount, strings[0], strings[1], OrderBookEntry::stringToOrderBookType(strings[2])};
    return obe;
};

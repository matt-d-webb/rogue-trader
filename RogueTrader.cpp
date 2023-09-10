#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "RogueTrader.h"
#include "CSVReader.h"

RogueTrader::RogueTrader()
{
}

void RogueTrader::init()
{
    int input;
    currentTimeFrame = orderBook.getEarliestTime();
    std::cout << "Welcome to Rogue Trader!" << std::endl;
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
        if (input == 7)
        {
            break;
        }
    }
}

void RogueTrader::printHelp()
{
    std::cout << "Help - choose options from the menu options." << std::endl;
}

void RogueTrader::printStats()
{
    std::cout << "======== Statistic ============" << std::endl;
    for (std::string const p : orderBook.getKnownProducts())
    {
        printf("Product: %s\n", p.c_str());

        std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask,
                                                               p,
                                                               currentTimeFrame);

        std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid,
                                                               p,
                                                               currentTimeFrame);

        printf("Asks: ");
        printf("\033[1;34m %lu\033[0m ", asks.size());
        printf("\033[1;31m %f\033[0m ", OrderBook::getLowPrice(asks));
        printf("\033[1;32m %f\033[0m\n", OrderBook::getHighPrice(asks));

        printf("Bids: ");
        printf("\033[1;33m %lu\033[0m ", bids.size());
        printf("\033[1;31m %f\033[0m ", OrderBook::getLowPrice(bids));
        printf("\033[1;32m %f\033[0m\n\n", OrderBook::getHighPrice(bids));
    }
};

void RogueTrader::enterOffer()
{
    std::cout << "Ask - the seller" << std::endl;
}

void RogueTrader::enterBid()
{
    std::cout << "Bid - the buyer" << std::endl;
}

void RogueTrader::printWallet()
{
    std::cout << "Waller" << std::endl;
}

void RogueTrader::gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
    currentTimeFrame = orderBook.getNextTime(currentTimeFrame);
}

void RogueTrader::printMenu()
{
    std::cout << "======== Rogue Trader ============" << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "7: Exit" << std::endl;
    std::cout << "Current time: " << currentTimeFrame << std::endl;
    std::cout << "==================================" << std::endl;
}

int RogueTrader::getUserOption()
{
    int userOption;
    std::cout << "Options: Type in 1-7" << std::endl;
    std::cin >> userOption;
    return userOption;
}

void RogueTrader::processUserOption(int userOption)
{
    if (userOption == 1)
    {
        printHelp();
    }

    if (userOption == 2)
    {
        printStats();
    }

    if (userOption == 3)
    {
        enterOffer();
    }

    if (userOption == 4)
    {
        enterBid();
    }

    if (userOption == 5)
    {
        printWallet();
    }

    if (userOption == 6)
    {
        gotoNextTimeFrame();
    }
    if (userOption == 7)
    {
        std::cout << "Exit: closing trading terminal." << std::endl;
    }
}
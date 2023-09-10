#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "RogueTrader.h"
#include "CSVReader.h"
#include "Wallet.h"

RogueTrader::RogueTrader()
{
}

void RogueTrader::init()
{
    int input;
    currentTimeFrame = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10.0);

    std::cout << "Welcome to Rogue Trader!" << std::endl;
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
        if (input == 7)
            break;
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

void RogueTrader::enterAsk()
{
    std::cout << "Ask - enter amount: product, price, amount e.g ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Invalid input, please try again." << std::endl;
        return;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], currentTimeFrame,
                tokens[0], OrderBookType::ask);

            obe.username = "rogue-trader";

            if (wallet.canFulfillOrder(obe))
            {
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "RogueTrader::enterAsk - Insufficient funds, please try again." << std::endl;
                return;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "RogueTrader::enterAsk - Invalid input, please try again." << std::endl;
            return;
        }
    }

    std::cout << "You entered: " << input << std::endl;
}

void RogueTrader::enterBid()
{
    std::cout << "Bid - enter amount: product, price, amount e.g ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Invalid input, please try again." << std::endl;
        return;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], currentTimeFrame,
                tokens[0], OrderBookType::bid);

            obe.username = "rogue-trader";

            if (wallet.canFulfillOrder(obe))
            {
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "RogueTrader::enterBid - Insufficient funds, please try again." << std::endl;
                return;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "RogueTrader::enterBid - Invalid input, please try again." << std::endl;
            return;
        }
    }

    std::cout << "You entered: " << input << std::endl;
}

void RogueTrader::printWallet()
{
    std::cout << "Wallet" << std::endl;
    std::cout << wallet.toString() << std::endl;
}

void RogueTrader::gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
    currentTimeFrame = orderBook.getNextTime(currentTimeFrame);

    std::cout << "Going to next time frame" << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "Matching orders for " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTimeFrame);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << std::endl;
            if (sale.username == "rogue-trader")
            {
                wallet.processSale(sale);
            }
        }
    }
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
    std::cout << "Enter option: ";
    int input;
    std::cin >> input;
    return input;
}

void RogueTrader::processUserOption(int userOption)
{
    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printStats();
        break;
    case 3:
        enterAsk();
        break;
    case 4:
        enterBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        gotoNextTimeFrame();
        break;
    case 7:
        std::cout << "Exit: closing trading terminal." << std::endl;
        break;
    default:
        std::cout << "Invalid option, please try again." << std::endl;
        break;
    }
}
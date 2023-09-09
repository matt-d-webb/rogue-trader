#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

MerkelMain::MerkelMain() {

}

void MerkelMain::init() {
    int input;
    while(true) {
        loadOrderBook();
        printMenu();
        input = getUserOption();
        processUserOption(input);
        if(input == 7) {
            break;
        }
    }
}

void MerkelMain::loadOrderBook() {
    orders = CSVReader::readCSV("data/20200317.csv");
}

void MerkelMain::printHelp()
{
    std::cout << "Help - choose options from the menu options." << std::endl;
}

void MerkelMain::printStats()
{
    unsigned int bids = 0;
    unsigned int asks = 0;

    std::cout << "======== Statistic ============" << std::endl;
    std::cout << "Orders: " << orders.size() << std::endl;

    for (OrderBookEntry order : orders)
    {
        if (order.type == OrderBookType::ask)
        {
            asks++;
        }
        else if(order.type == OrderBookType::bid)
        {
            bids++;
        }
    }
    std::cout << "Bids: " << bids << std::endl;
    std::cout << "Asks: " << asks << std::endl;
    std::cout << "===============================" << std::endl;
}

void MerkelMain::enterOffer()
{
    std::cout << "Ask - the seller" << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Bid - the buyer" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Waller" << std::endl;
}

void MerkelMain::gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
}

void MerkelMain::printMenu()
{
    std::cout << "======== Rogue Trader ============" << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "7: Exit" << std::endl;
    std::cout << "==================================" << std::endl;
}

int MerkelMain::getUserOption()
{
    int userOption;
    std::cout << "Options: Type in 1-7" << std::endl;
    std::cin >> userOption;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
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
#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class RogueTrader
{
public:
    RogueTrader();
    //** Initialise the program */
    void init();

private:
    void printHelp();
    void printStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeFrame();
    void printMenu();
    int getUserOption();
    void processUserOption(int userOption);

    std::string currentTimeFrame;

    OrderBook orderBook{"data/20200317.csv"};
};
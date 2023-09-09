#pragma once

#include <vector>
#include "OrderBookEntry.h"

class RogueTrader
{
public:
    RogueTrader();
    //** Initialise the program */
    void init();

private:
    void printHelp();
    void loadOrderBook();
    void printStats();
    void enterOffer();
    void enterBid();
    void printWallet();
    void gotoNextTimeFrame();
    void printMenu();
    int getUserOption();
    void processUserOption(int userOption);

    std::vector<OrderBookEntry> orders;
};
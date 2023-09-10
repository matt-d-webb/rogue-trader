#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet
{
    public:
        Wallet();

        /** 
         *  returns the balance of the currency in the wallet
         *  returns 0 if the currency is not in the wallet
         */
        void insertCurrency(std::string type, double amount);

        /**
         * removes the currency from the wallet
        */
        bool removeCurrency(std::string type, double amount);

        /**
         * returns true if the wallet contains the currency
        */
        bool containsCurrency(std::string type, double amount);

        /**
         * checks if the wallet can fulfill the order
        */
        bool canFulfillOrder(const OrderBookEntry& order);

        /**
         * returns a string representation of the wallet
        */
        std::string toString();

    private:
        std::map<std::string, double> currencies;
};
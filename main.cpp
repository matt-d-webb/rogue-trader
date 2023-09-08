#include <iostream>

float average(float x, float y);
void printHelp()
{
    std::cout << "Help - choose options from the menu options." << std::endl;
}
void printStats()
{
    std::cout << "Stats - list of latest analytics" << std::endl;
}
void enterOffer()
{
    std::cout << "Ask - the seller" << std::endl;
}
void enterBid()
{
    std::cout << "Bid - the buyer" << std::endl;
}
void printWallet()
{
    std::cout << "Waller" << std::endl;
}
void gotoNextTimeFrame()
{
    std::cout << "Continue" << std::endl;
}

void printMenu()
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
int getUserOption()
{
    int userOption;
    std::cout << "Options: Type in 1-7" << std::endl;
    std::cin >> userOption;
    return userOption;
}
void processUserOption(int userOption)
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

int main(int argc, char *argv[])
{

    int x{-1};
    while (x)
    {
        std::cout << x << std::endl;
        x--;
    }
    // float a = average(10, 30);
    // std::cout << "The average of 10 and 30 is " << a << std::endl;

    // while (true)
    // {
    //     printMenu();
    //     int userOption = getUserOption();
    //     processUserOption(userOption);
    //     if (userOption == 7)
    //         break;
    // }
}
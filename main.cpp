#include <fstream>
#include "Stockholder.h"

using namespace std;

enum MAIN_MENU { LOGIN=1, DIR=2, ADV=3, EXIT=4, AVAIL=5, MYSTOCKS=6, PURCH=7, SELL=8, LOGOUT=9};

void PrintMain();
void PrintUserMenu();


int main() {
    //Main container variables
    int numStocks = 0;
    map<string, Stock> stockContainer = map<string, Stock>();
    map<string, Stockholder> stockholderContainer = map<string, Stockholder>();
    Stockholder currentHolder;
    //Menu input variables
    int input = 0;
    int anyNumber = 0;
    int currMenu = 0;
    string stockName = "";
    string userName = "";

    ifstream input_file;

    // Get the Stock data
    input_file.open("stocks.txt");
    input_file >> numStocks;

    //Get stocks into the container
    for(int i = 0; i < numStocks; i++){
        Stock newStock = Stock();
        input_file >> newStock;
        stockContainer.insert({newStock.short_name, newStock});
    }

    input_file.close();

    do{
        if(currMenu == 0){
            PrintMain();
            cin >> input;
            while (!cin || input < 1 || input > 4) {
                if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                cout << "Please enter a valid menu item: ";
                cin >> input;
            }
        }
        else{ //User Menu
            PrintUserMenu();
            cin >> input;
            while (!cin || input < 1 || input > 5) {
                if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                cout << "Please enter a valid menu item: ";
                cin >> input;
            }
            //for the correct enum
            input += 4;
        }
        //now we have good input, handle the cases
        switch(input){
            case LOGIN:{
                cout << "Please enter your name: ";
                cin >> userName;
                while (!cin) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid name: ";
                    cin >> userName;
                }
                auto it = stockholderContainer.find(userName);
                if(it != stockholderContainer.end()){
                    currentHolder = it->second;
                }
                else{
                    Stockholder newHolder = Stockholder(userName);
                    stockholderContainer.insert({userName, newHolder});
                    currentHolder = newHolder;
                }
                currMenu = 1;
                break;
            }
            case DIR:{
                //Print all the names of the users
                for(auto it = stockholderContainer.begin(); it != stockholderContainer.end(); it++){
                    cout << it->first << endl;
                }
                break;
            }
            case ADV:{
                for(auto it = stockContainer.begin(); it != stockContainer.end(); it++){
                    it->second.AdvanceDay();
                }
                break;
            }
            case EXIT:{
                break;
            }
            case AVAIL:{
                cout << "The following users are available:" << endl;
                for(auto it = stockContainer.begin(); it != stockContainer.end(); it++){
                    it->second.Print();
                    cout << endl;
                }
                cout << "Please enter any number to return to the main menu: ";
                cin >> anyNumber;
                while (!cin) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid number: ";
                    cin >> anyNumber;
                }
                currMenu = 0;
                break;
            }
            case MYSTOCKS:{
                cout << "This is the current user's stocks:" << endl;
                auto it = stockholderContainer.find(userName);
                it->second.Print();
                cout << "Please enter any number to return to the main menu: ";
                cin >> anyNumber;
                while (!cin) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid number: ";
                    cin >> anyNumber;
                }
                currMenu = 0;
                break;
            }
            case PURCH:{
                cout << "Enter a stock's short name: ";
                cin >> stockName;
                auto it = stockContainer.find(stockName);
                if(it == stockContainer.end()){
                    cout << "This is not a stock you can buy!" << endl;
                    //Return to the userMenu
                    continue;
                }
                cout << "Enter the number of stocks you would like to purchase: ";
                cin >> anyNumber;
                auto it2 = stockholderContainer.find(userName);
                bool purchaseSuccess = it2->second.Purchase(&(it->second), anyNumber);
                if(purchaseSuccess){
                    cout << "Congratulations your purchase went through!" << endl;
                }
                else{
                    cout << "Sorry, you cannot afford this purchase." << endl;
                }
                break;
            }
            case SELL:{
                cout << "Enter a stock's short name: ";
                cin >> stockName;
                auto it = stockholderContainer.find(userName);
                cout << "Enter the number of stocks you would like to sell: ";
                cin >> anyNumber;
                bool sellSuccess = it->second.Sell(stockName, anyNumber);
                if(sellSuccess){
                    cout << "Congratulations on your sale!" << endl;
                }
                else{
                    cout << "Sorry you don't have enough stocks to sell." << endl;
                }
                break;
            }
            case LOGOUT:{
                currMenu = 0;
                break;
            }
        }

    }while(input != EXIT);

    return 0;
}

void PrintMain(){
    cout << "Welcome to the Stock Portfolio Manager!"       << endl
         << "[" << LOGIN << "] Log In"                      << endl
         << "[" << DIR   << "] List Directory"              << endl
         << "[" << ADV   << "] Advance a Day"               << endl
         << "[" << EXIT  << "] Exit Program"                << endl 
         << "Please enter a menu item: ";
}

void PrintUserMenu(){
    cout << "What would you like to do?"                     << endl
         << "[" << AVAIL - 4    << "] List Available Stocks" << endl
         << "[" << MYSTOCKS - 4 << "] List My Stocks"        << endl
         << "[" << PURCH - 4    << "] Purchase Stocks"       << endl
         << "[" << SELL - 4     << "] Sell Stocks"           << endl
         << "[" << LOGOUT - 4   << "] Log Out"               << endl
         << "Please enter a menu item: ";
}
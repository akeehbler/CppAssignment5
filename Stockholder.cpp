#include "Stockholder.h"

using namespace std;

struct PortfolioValue {

    float total_value;

    void operator() (pair<string, pair<Stock*, int>> portfol){
        total_value += portfol.second.first->new_value * portfol.second.second;
    }

};

Stockholder::Stockholder(){

}

Stockholder::Stockholder(string _name){
    name = _name;
    portfolio = map<string, pair<Stock*, int>>();
    //100k start value
    cash = 100000;
}

//Deconstructor
Stockholder::~Stockholder(){
    //May not be used, update this as needed if use dynamically-allocated objects
}

bool Stockholder::Purchase(Stock* stock, int count){
    // total_price = stock price * number of stocks being purchased
    float total_price = stock->new_value * count;
    if(total_price > cash){
        return false;
    }
    else{ // Good to go to buy the stocks wanted
        cash = cash - total_price;
        
        //Check to see if the stock is already in the map
        auto it = portfolio.find(stock->short_name);
        //If it is, then just add to the count rather than add the whole thing
        if(it != portfolio.end()){
            it->second.second += count;
            return true;
        }
        else{
            pair<Stock*, int> valueToAdd (stock, count);
            portfolio.insert({stock->short_name, valueToAdd});
            return true;
        }
    }
}

bool Stockholder::Sell(string short_name, int count){
    int numOwned = 0;
    float totalValue = 0;
    auto it = portfolio.find(short_name);
    //Get the number owned
    if(it != portfolio.end()){
        numOwned = it->second.second;
    }
    if(numOwned >= count){
        // Get pair, first value(stock) the the new_value number
        totalValue = it->second.first->new_value;
        totalValue = totalValue * count;
        cash += totalValue;
        numOwned = numOwned - count;
        // Get the pair, second value (count Owned currently)
        it->second.second = numOwned;
        return true;
    }
    return false;
}

float Stockholder::NetWorth(){
    float netWorth = 0;
    PortfolioValue portValue = for_each(portfolio.begin(), portfolio.end(), PortfolioValue());
    netWorth = portValue.total_value + cash;
    return netWorth;
}

void Stockholder::Print(){
    cout << name << " $" << NetWorth() << endl;
    for(auto it = portfolio.begin(); it != portfolio.end(); it++){
        //Use print method of the stock and then print the count
        it->second.first->Print();
        cout <<  " " << it->second.second << endl;
    }

}
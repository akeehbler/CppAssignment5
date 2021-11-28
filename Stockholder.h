#ifndef STOCKHOLDER_HEADER
#define STOCKHOLDER_HEADER

#include "Stock.h"
#include <map>
#include <algorithm>

using namespace std;

class Stockholder{

    private:
        string name;
        map<string, pair<Stock*, int>> portfolio;
        float cash;

    public:
        Stockholder();
        Stockholder(string _name);
        ~Stockholder();
        bool Purchase(Stock* stock, int count);
        bool Sell(string short_ame, int count);
        float NetWorth();
        void Print();
        //Portfolio Value functor

};

#endif
#ifndef STOCK_HEADER
#define STOCK_HEADER

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

struct Stock {
private:
    int bias;
public:
    string short_name, long_name;
    float old_value, new_value;

    Stock() {
        short_name = long_name = "";
        old_value = new_value = 0.0;
        bias = (rand() % 5) - 2;
    }

    Stock& operator=(const Stock& that) {
        this->short_name = that.short_name;
        this->long_name  = that.long_name;
        this->old_value  = that.old_value;
        this->new_value  = that.new_value;
        this->bias       = that.bias;
        return *this;
    }

    friend istream& operator>>(istream& in, Stock& stock) {
        in >> stock.long_name >> stock.short_name >> stock.old_value >> stock.new_value;

        return in;
    }

    void AdvanceDay() {
        old_value = new_value;
        float delta = 0.0;
        // simple random walk to generate a biased change in value.
        int NUM_STEPS = 1440;
        for (int step = 0; step < NUM_STEPS; step++) {
            int step_val = (rand() % 100) + bias;
            if (step_val >= 50) {
                delta += 1.0;
            }
            else {
                delta -= 1.0;
            }
        }
        new_value = old_value + (delta * 100.0 / float(NUM_STEPS));
    }

    void Print() {
        float delta = new_value - old_value;
        cout << fixed << showpoint << setprecision(2);
        cout << short_name << " " << long_name << " $" << new_value << (delta >= 0 ? " $" : " -$") << abs(delta);
    }
};

#endif

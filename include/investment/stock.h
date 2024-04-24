#pragma once
#include "investment.h"

class Stock: public Investment {
public:
    Stock(): 
        Investment(0){}

    Stock(int val): 
        Investment(val){} 

    virtual void makeLogAndEntry() override;
};
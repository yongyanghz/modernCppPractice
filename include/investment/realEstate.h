#pragma once
#include "investment.h"

class RealEstate: public Investment {
public:
    RealEstate(): 
        Investment(0){}

    RealEstate(int val): 
        Investment(val){} 

    virtual void makeLogAndEntry() override;
};
#include "investment.h"

class Bond : public Investment {
public:
    Bond(): 
        Investment(0){}

    Bond(int val): 
        Investment(val){} 

    virtual void makeLogAndEntry() override;
};
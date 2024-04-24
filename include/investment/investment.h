#pragma once

class Investment {
public:
    Investment(): 
        _amount(0){}

    Investment(int val): 
        _amount(val){} 

    virtual ~Investment(){}

    virtual void makeLogAndEntry();

    int getAmount(){ return _amount;}

private: 
    int _amount;
};
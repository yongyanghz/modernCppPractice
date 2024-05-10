#pragma once

#include <memory>

#include "investment.h"
#include "bond.h"
#include "realEstate.h"
#include "stock.h"

namespace InvestSpace{

void
makeLogEntry(Investment* pInv)
{
    if(pInv){
        printf("Make investment, the amount is %d.\n", pInv->getAmount());
    }
}
enum class InvestmentType {
    NONE = 0,
    BOND,
    REAL_ESTATE,
    STOCK,
};

template <typename... Ts>
auto
makeInvestment(InvestmentType invType, Ts&&... params)
{
    auto delInvmt = [](Investment* pInvestment){
        makeLogEntry(pInvestment);
        delete pInvestment;    
    };

    std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
    if(invType == InvestmentType::BOND){
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }else if(invType == InvestmentType::REAL_ESTATE){
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }else if(invType == InvestmentType::STOCK){
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    return pInv;
}

void 
delInvmt2(Investment* pInvestment)
{
    makeLogEntry(pInvestment);
    delete pInvestment;    
}

template <typename... Ts>
auto
makeInvestment2(InvestmentType invType, Ts&&... params)
{
    std::unique_ptr<Investment, void (*)(Investment*)> pInv(nullptr, &delInvmt2);
    if(invType == InvestmentType::BOND){
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }else if(invType == InvestmentType::REAL_ESTATE){
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }else if(invType == InvestmentType::STOCK){
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    return pInv;
}

}

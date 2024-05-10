#include <iostream>

#include "uniquePtrTest.h"
#include "investmentUtility.h"

void
UniquePtrTest::run(){
    std::cout<<"This is a test for unique_ptr"<<std::endl;
    auto pInv = makeInvestment(InvestSpace::InvestmentType::STOCK, 1000);
    printf("size of pInv is %lu\n", sizeof(pInv));
    
    auto pInv2 = makeInvestment2(InvestSpace::InvestmentType::STOCK, 1100);
    printf("size of pInv2 is %lu\n", sizeof(pInv2));

    // auto pInv3 = pInv2; // Error, std::unique_ptr can only be moved, not be copied
    auto pInv3 = std::move(pInv2);
    std::shared_ptr<Investment> pInvShared = makeInvestment(InvestSpace::InvestmentType::BOND, 1200); 
    printf("size of pInvShared is %lu\n", sizeof(pInvShared));
}
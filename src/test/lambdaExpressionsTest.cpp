#include "lambdaExpressionsTest.h"
#include "widget.h"
#include "alarm.h"

#include <iostream>

void
LambdaExpressionsTest::run()
{
    lamdaExpressionClosure();
    avoidDefaultCaptureModes();
    initCaptureToMoveObjectsIntoClosures();
    preferLamdbaToBind();
}


void 
 LambdaExpressionsTest::lamdaExpressionClosure()
 {
    std::vector<int> vec{1, 3, 5, 7 , 10};
    auto iter = std::find_if(vec.begin(), vec.end(), 
        [](int val){
            return 3 < val && val < 10;
        });
    std::cout<<*iter<<std::endl;

    int x = 10;
    auto c1 = [x](int y){    // c1 is the copy of the closure produced by the lambda
        return x * y > 55;
    };
    std::cout<<c1(5)<<std::endl;
    auto c2 = c1;  // c2 is copy of c1
    std::cout<<c2(6)<<std::endl;
    auto c3 = c2; // c3 is copy ofc2
    std::cout<<c3(7)<<std::endl;
 }
    
void 
LambdaExpressionsTest::avoidDefaultCaptureModes()
{
    FilterContainer filters;
    filters.emplace_back([](int value){
        return value % 5 == 0;
    });
    addDivisorFilter(filters);
   
   std::cout<<filters.at(0)(5)<<std::endl;
   std::cout<<filters.at(0)(6)<<std::endl;

   std::cout<<filters.at(1)(11)<<std::endl;
   std::cout<<filters.at(1)(12)<<std::endl;
    
    // filters.clear();
    // auto myW = WidgetFac::create();
    // myW->addFilter(filters);
    // std::cout<<filters.at(0)(10)<<std::endl;
    // std::cout<<filters.at(0)(11)<<std::endl;

}

void 
LambdaExpressionsTest::addDivisorFilter(FilterContainer & filters)
{
    // int divisor = 10;
    // filters.emplace_back([&](int value){
    //     return value % divisor == 0;   // danger! ref to divisor will dangle!
    // });
    
    // int divisor2 = 17;
    // filters.emplace_back([&divisor2](int value){
    //     return value % divisor2 == 0;   // danger! ref to divisor will dangle!
    // });
    
    // int divisor3 = 19;
    // filters.emplace_back([=](int value){
    //     return value % divisor3 == 0;   // capture by value, divisor3 will not dange 
    // });

    static int staticDivisor = 11;
    filters.emplace_back([=](int value){
        return value % staticDivisor == 0;   // capture nothing, refers to static data 
    });
    ++staticDivisor;
}
    
void 
LambdaExpressionsTest::initCaptureToMoveObjectsIntoClosures()
{
    auto pw = WidgetFac::create();
    auto func = [pw = std::move(pw)]{ // since C++ 14
        return pw->isValidated()
            && pw->isArchived();
    };

    auto func2 = [pw = WidgetFac::create()]{ // since C++ 14
        return pw->isValidated()
            && pw->isArchived();
    };

    std::cout<<func()<<std::endl;
    std::cout<<func2()<<std::endl;
}
    
void 
LambdaExpressionsTest::useDecltypeOnAutoAndAnd()
{
    auto f = [](auto&& x){ 
        return normalize(std::forward<decltype(x)>(x)); 
    };

    std::vector<int>  vec{1, 3, 5, 7};
    auto vec2  = f(vec);
    std::for_each(vec2.begin(), vec2.end(), [](const int & val){
        std::cout<<val<<std::endl;
    });
}
    
void
LambdaExpressionsTest::preferLamdbaToBind()
{
    Alarm a;
    a.test();
}
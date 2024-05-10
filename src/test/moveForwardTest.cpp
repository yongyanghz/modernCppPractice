
#include <chrono>
#include <thread>
#include <ctime>

#include "moveForwardTest.h"
#include "widget.h"

using namespace std::chrono_literals;

void
MoveForwardTest::run()
{
    Widget w;
    logAndProcess(w); // lvalue
    logAndProcess(std::move(w)); // rvalue
    distinguishUniversalRefFromRValueRef();
}


void 
MoveForwardTest::distinguishUniversalRefFromRValueRef()
{
    Widget&& var1 = Widget(); // rvalue reference
    auto&& var2 = var1;      // universal refercene, have tye deduction, not rvalue reference 
    var2.getId();
    Widget w;
    f2(w); // lvalue passed to f2; param's type is Widget&(i.e., an lvalue reference)
    f2(std::move(w)); // rvalue passed to f2; param's type is Widget&& (i.e., an rvalue reference)

    std::vector<int> vec;
    // error: candidate function [with T = int] not viable: expects an rvalue for 1st argument
    // f1(vec);
    auto timeFuncInvocation = 
        [](auto&& func, auto&&... params)
        {
            auto startTime = std::chrono::system_clock::now();
            std::forward<decltype(func)>(func)(            // invoke func
                std::forward<decltype(params)>(params)...  // on params
            );
            auto endTime = std::chrono::system_clock::now();
            auto elaspedTime = std::chrono::system_clock::to_time_t(endTime)
                - std::chrono::system_clock::to_time_t(startTime);
            return elaspedTime;
        };

    auto printSomeThing = 
        [](int v){
            std::cout<<"The number is "<<v<<std::endl;
            std::this_thread::sleep_for(2700ms);
        };
    std::cout<<"printSomething elapsed: "<< timeFuncInvocation(printSomeThing, 999)<<" seconds"<<std::endl;
}






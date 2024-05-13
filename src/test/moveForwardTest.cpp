
#include <chrono>
#include <thread>
#include <ctime>

#include "moveForwardTest.h"
#include "widget.h"
#include "matrix.h"

using namespace std::chrono_literals;

// 1. Apply std::move to rvalue references and std::fowward to universal references 
//    at the last time each is used;
// 2. Do the same above thing for rvalue reference and universal references being returned 
//    from functions that return value;
// 3. Never apply std::move or std::forward to local objects if they woud otherwise be eligible
//    for the RVO(Return Value Optimization).

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
            std::this_thread::sleep_for(900ms);
        };
    std::cout<<"printSomething elapsed: "<< timeFuncInvocation(printSomeThing, 999)<<" seconds"<<std::endl;

    Widget&& rWidget{Widget()};
    std::cout<<"Widget id"<<rWidget.getId()<<std::endl;
    Widget lWidget(std::move(rWidget));
    std::cout<<"Widget id"<<lWidget.getId()<<std::endl;
    lWidget.setName("beautiful widget");
    lWidget.setSignText("bravo");

    Matrix m1(4, 5);
    auto m2 = Matrix(4, 5) + m1;
}






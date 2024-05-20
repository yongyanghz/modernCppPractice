
#include <chrono>
#include <thread>
#include <ctime>
#include <vector>
#include <array>

#include "moveForwardTest.h"
#include "widget.h"
#include "matrix.h"
#include "logger.h"
#include "person.h"

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
    avoidOverloadingUniversalReferences();
    moveMayNotPresentNorCheapNorUsed();
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

void 
MoveForwardTest::avoidOverloadingUniversalReferences()
{
    Logger myLogger;
    std::string petName("Darla");
    myLogger.logAndAdd(petName);
    myLogger.logAndAdd(std::string("Lanado"));
    myLogger.logAndAdd("Rala");
    myLogger.logAndAdd(1001);
    short nameIdx = 1002;
    myLogger.logAndAdd(nameIdx);

    const Person p("Nancy");
    auto cloneofP(p);

    SpecialPerson sp("Lana"); 
    SpecialPerson sp2(sp); 
    SpecialPerson sp3(std::move(sp)); 

   // Person p2(myLogger); // Test static_assert
}


// Sceneraios in which C++11's move semantics do you no good:
// 1. No move operations
// 2. Move not faster than copy
// 3. Move not usable:  the context requires the move operation emits no exceptions, but the move operation 
//    isn't declared noexcept
// 4. Source object is lvalue: With very few exceptions(see e.g., Item 24 use move for rvalue reference...)
//    only rvalues may be used as the source of a move operation


void 
MoveForwardTest::moveMayNotPresentNorCheapNorUsed()
{
    std::vector<Widget> vw1;
    for(int i=0; i<10000; i++){
        vw1.push_back(Widget());
    }
    // move vw1 to vw2. Runs in constant time.
    // Only ptrs in vw1 and vw2 are modified
    auto start= std::chrono::steady_clock::now();
    auto vw2 = std::move(vw1);
    auto end= std::chrono::steady_clock::now();
    std::cout<< "vector move operation elapsted time: " << std::endl;
    std::cout << "Time difference = " << 
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "[µs]" << std::endl;
    std::cout << "Time difference = " << 
        std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count() 
        << "[ns]" << std::endl;
 
    std::array<Widget, 10000> aw1;
    // move aw1 to aw2. Runs in linear time.
    // All elements in aw1 are moved to aw2
    auto start2 = std::chrono::steady_clock::now();
    auto aw2 = std::move(aw1);
    auto end2 = std::chrono::steady_clock::now();
    std::cout<< "array move operation elapsted time: "<< std::endl;
     std::cout << "Time difference = " << 
        std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
        << "[µs]" << std::endl;
    std::cout << "Time difference = " << 
        std::chrono::duration_cast<std::chrono::nanoseconds> (end2 - start2).count() 
        << "[ns]" << std::endl;
}








#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "weakPtrTest.h"
#include "widget.h"
#include "observer.h"


// factory function
std::unique_ptr<const Widget> loadWidget(WidgetId id)
{
    return std::make_unique<const Widget>(id);
}

// caching version of loadWidget
std::shared_ptr<const Widget> fastLoadWidget(WidgetId id)
{
    static std::unordered_map<WidgetId, std::weak_ptr<const Widget>> cache;
    auto objPtr = cache[id].lock();
    if(!objPtr){
        objPtr = loadWidget(id);
        cache[id] = objPtr;
    }
    return objPtr;
}


void
WeakPtrTest::run()
{
    // first example, how to use weak_ptr
    auto spw = std::make_shared<Widget>();
    std::weak_ptr<Widget> wpw(spw);
    if(!wpw.expired()){
        auto spw1 = wpw.lock(); // return a shared_ptr, if wpws epired, spw1 is null
        spw1->makeLogEntry();
        std::shared_ptr<Widget> spw2(wpw);
        spw2->makeLogEntry();
    }

    spw = nullptr;
    if(wpw.expired()){
        printf("The weak pointer wpw doesn't point to an object!\n");
        auto spw3 = wpw.lock();
        if(!spw3.get()){
            printf("spw3 is null!\n");
        }
        // libc++abi: terminating with uncaught exception of type std::__1::bad_weak_ptr: bad_weak_ptr
        // std::shared_ptr<Widget> spw4(wpw);
    } 

    // second example, use weak_ptr in Caching Pattern
    WidgetId id0 = 16;
    WidgetId id1 = 17;
    auto objPtr0 = fastLoadWidget(id0);
    auto objPtr1 = fastLoadWidget(id1);
    auto objPtr2 = fastLoadWidget(id0);
    objPtr0->makeLogEntry();
    objPtr1->makeLogEntry();
    objPtr2->makeLogEntry();


    // third example, use weak_ptr as observer list entry in Observer Pattern
    std::shared_ptr<ISubject> mySubject = std::make_shared<Subject>();
    auto observer0  = std::make_shared<Observer>();
    auto observer1  = std::make_shared<Observer>();
    auto observer2  = std::make_shared<Observer>();
    observer0->Subscribe(mySubject);
    observer1->Subscribe(mySubject);
    observer2->Subscribe(mySubject);
    auto spSubject = std::dynamic_pointer_cast<Subject>(mySubject);
    spSubject->CreateMessage("Hello, every one, welcome to observe me!");
    spSubject->SomeBusinessLogic();
    observer1->RemoveMeFromTheList();
    spSubject->CreateMessage("Hello, every one, we lost one observer, welcome to observe me again!");
}
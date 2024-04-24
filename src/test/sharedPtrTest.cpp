#include <iostream>
#include <memory>
#include <vector>

#include "sharedPtrTest.h"
#include "widget.h"

void makeLogEntry(Widget* pw)
{
    printf("Delete: ");
    pw->makeLogEntry();
}

void
SharedPtrTest::run()
{
    auto loggingDel = [](Widget *pw)
    {
        makeLogEntry(pw);
        delete pw;
    };

    std::unique_ptr<Widget, decltype(loggingDel)> upw(new Widget, loggingDel); // deleter type is part of ptr type
    std::shared_ptr<Widget> spw(new Widget, loggingDel); // deleter type is not part of ptr type

    auto customeDel1 = [](Widget *pw)
    {
        printf("customeDel1\n");
        delete pw;
    };
    auto customeDel2 = [](Widget *pw)
    {
        printf("customeDel2\n");
        delete pw;
    };
    
    std::shared_ptr<Widget> spw1(new Widget, customeDel1);
    std::shared_ptr<Widget> spw2(new Widget, customeDel2);
    std::vector<std::shared_ptr<Widget>> vpw{spw1, spw2};

    auto pw = new Widget;
    std::shared_ptr<Widget> spw3(pw, loggingDel); // create control block for *pw
    // Wrong Usage !!! Lead to run time error: pointer being freed was not allocated!
    // std::shared_ptr<Widget> spw4(pw, loggingDel); // create 2nd control block fro *pw!

    // Recommend usage to create control block for shared_ptr
    // 1. direct use of new
    std::shared_ptr<Widget> spw5(new Widget, loggingDel); // create control block for *pw
    std::shared_ptr<Widget> spw6(spw5); //spw6 uses smae control block as spw5
}
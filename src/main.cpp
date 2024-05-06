#include <iostream>

#include "version.h"
#include "uniquePtrTest.h"
#include "sharedPtrTest.h"
#include "weakPtrTest.h"

int main(int argc, const char * argv[]) {
    // UniquePtrTest upTest;
    // upTest.run(); 
    // SharedPtrTest spTest;
    // spTest.run();  
    WeakPtrTest wpTest;
    wpTest.run();  
    return 0;
}


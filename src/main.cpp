#include <iostream>

#include "version.h"
#include "uniquePtrTest.h"
#include "sharedPtrTest.h"

int main(int argc, const char * argv[]) {
    // UniquePtrTest upTest;
    // upTest.run(); 
    SharedPtrTest spTest;
    spTest.run();    
    return 0;
}


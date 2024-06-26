#include <iostream>

#include "version.h"
#include "uniquePtrTest.h"
#include "sharedPtrTest.h"
#include "weakPtrTest.h"
#include "moveForwardTest.h"
#include "lambdaExpressionsTest.h"

int main(int argc, const char * argv[]) {
    // UniquePtrTest upTest;
    // upTest.run(); 
    // SharedPtrTest spTest;
    // spTest.run();  
    // WeakPtrTest wpTest;
    // wpTest.run();

    // MoveForwardTest mfTest;
    // mfTest.run();  

    LambdaExpressionsTest leTest;
    leTest.run();
    return 0;
}


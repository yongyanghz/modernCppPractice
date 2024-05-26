#pragma once
#include <type_traits>
#include <vector>
#include <iostream>
class Widget;

// std::move does cast, it doesn't move
template <typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}

struct IPv4Header{
    std::uint32_t version: 4,
                  IHL: 4,
                  DSCP: 6,
                  ECN: 2,
                  totalLength: 16;
};


class MoveForwardTest
{
public:
    void run();
    
    void distinguishUniversalRefFromRValueRef();
    
    void avoidOverloadingUniversalReferences();

    void moveMayNotPresentNorCheapNorUsed();

    void perferctForwardFailureCases();

    void f0(Widget&& param){ // rvalue reference
        std::cout<<"Hahahha, f0 have been called!"<<std::endl;
    }
    
    template<typename T>
    void f1(std::vector<T>&& param);  // rvalue referrence

    template<typename T>
    void f2(T&& param);  // universal refercence, type deduction, not rvalue referrence

    void printVector(const std::vector<int>& v);

    template<typename T>
    void print(T&& param){
        std::cout<<param<<std::endl;
    }

    template<typename T>
    void fwd(T&& param){
        printVector(std::forward<T>(param));
    }
    
    template<typename T>
    void fwdPrint(T&& param){
        print(std::forward<T>(param));
    }

    template<typename... Ts>
    void fwdVariadic(Ts&&... param){
        printVector(std::forward<Ts>(param)...);
    }

};


template<typename T>
void 
MoveForwardTest::f1(std::vector<T>&& param)
{
    std::cout<<"Hahahha, f1 have been called!"<<std::endl;
}

template<typename T>
void 
MoveForwardTest::f2(T&& param)
{
    std::cout<<"Hahahha, f2 have been called!"<<std::endl;
}
void funcForCallBackFunc(int (*pf)(int));

void funcForCallBackFunc2(int pf(int));

int processVal(int value);

int processVal(int value, int priority);

template<typename T>
void fwdForCallBackFunc(T&& param){
    funcForCallBackFunc(std::forward<T>(param));
}

template<typename T>
T workOnVal(T param){
    return param + 1;
}

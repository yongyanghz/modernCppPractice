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



class MoveForwardTest
{
public:
    void run();
    
    void distinguishUniversalRefFromRValueRef();
    
    void avoidOverloadingUniversalReferences();

    void f0(Widget&& param){ // rvalue reference
        std::cout<<"Hahahha, f0 have been called!"<<std::endl;
    }
    
    template<typename T>
    void f1(std::vector<T>&& param);  // rvalue referrence

    template<typename T>
    void f2(T&& param);  // universal refercence, type deduction, not rvalue referrence
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
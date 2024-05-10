#pragma once
#include <string>
#include <utility>

class Annotation {
public:
    // don't declare the objects const if you want to move them
    // cause std::move unconditionally casts its argument to an rvalue, whethere it's const or non-const, 
    // and const value can't be put into move ctor like string(string&& rhs),  it will call copy ctor instead
    explicit Annotation(std::string text)
        :_value(std::move(text)){} 

private:
    std::string _value;
};
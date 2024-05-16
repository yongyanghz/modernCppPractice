#pragma once
#include <set>
#include <string>
#include <chrono>
#include <memory>
#include <map>
#include <iostream>

static std::multiset<std::string> s_names;
static const std::map<int, std::string> s_nameTable = {
    {1000, "Darla"},
    {1001, "Lanado"},
    {1002, "Rala"},
    {1003, "Jasmin"},
};

class Logger{
public:
    void log(std::chrono::time_point<std::chrono::system_clock> t, std::string operationName);
    
    template<typename T>
    void logAndAdd(T&& name)
    {
        logAndAddImpl(std::forward<T>(name), 
            std::is_integral<std::remove_reference_t<T>>());
    }
    
    template<typename T>
    void logAndAddImpl(T&& name, std::false_type)
    {
        std::cout<<"logAndAdd unversal reference int false_type were called!"<<std::endl;
        auto now = std::chrono::system_clock::now();
        log(now, "logAndAdd");
        s_names.emplace(std::forward<T>(name));
    }

    void logAndAddImpl(int idx, std::true_type)
    {
        std::cout<<"logAndAdd int true_type were called!"<<std::endl;
        logAndAdd(nameFromIdx(idx));
    }

    std::string nameFromIdx(int idx)
    {
        if(s_nameTable.find(idx) != s_nameTable.end()){
            return s_nameTable.at(idx);
        }else{
            return "Na";
        }
    }

};
#pragma once
#include <memory>
#include <vector>
#include <chrono>
#include <iostream>

using WidgetId = unsigned; 

static WidgetId  currentId;


class Widget: public std::enable_shared_from_this<Widget>{
public:
    static constexpr std::size_t MinVals = 28;

    Widget();
    Widget(WidgetId id);
    Widget(Widget&& rhs):
        _name(std::move(rhs._name)),
        _impl(std::move(rhs._impl)){
            std::cout<<"Widget move constructor was called!"<<std::endl;
    }
    ~Widget();

    template<typename T>
    void setName(T&& newName){              // newName is universal reference
        _name = std::forward<T>(newName);
    }
    template<typename T>
    void setSignText(T&& text){ // text, is universal referrence
        _sign = text; // use text, but don't modify it
        _historySigns += std::forward<T>(text); // foward text the last time use it
    }

    WidgetId getId() const;
    
    void makeLogEntry() const;
    
    void process(); 

    class WidgetImpl;

    static void delWidgetImpl(WidgetImpl* impl);

private:
    std::string _name;
    std::string _sign;
    std::string _historySigns;
    std::unique_ptr<WidgetImpl, void (*)(WidgetImpl*)> _impl; // pimpl idiom
};

class WidgetFac : public std::enable_shared_from_this<WidgetFac> {
public:

    // factory function that perfect-forwards args to a private ctor
    template<typename... Ts>
    static std::shared_ptr<WidgetFac> create(Ts&&... params){
        return std::shared_ptr<WidgetFac>(new WidgetFac(std::forward<Ts>(params)...));
}
    
    int getId() const { return _id; }
    
    void makeLogEntry() const;
    
    void process(); 

private:
    WidgetFac(): _id(currentId++){}

    int _id;
    std::vector<std::shared_ptr<WidgetFac>> _processedWidgets; 
};


using TimePoint = std::__1::chrono::system_clock::time_point;
void makeLogEntry(std::string text, TimePoint time);

void process(Widget& lvalArg); // process lvalues

void process(Widget&& rvalArg); // process rvalues

template<typename T>
void logAndProcess(T&& param)
{
    auto now = std::chrono::system_clock::now();
    makeLogEntry("Calling 'process'", now);
    // std::forwar is a conditional cast: it casts to an rvalue
    // only if the argument was initialized with an rvalue
    process(std::forward<T>(param));
}

constexpr std::size_t Widget::MinVals;


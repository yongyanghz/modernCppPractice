#pragma once
#include <memory>
#include <vector>

using WidgetId = unsigned; 

static int currentId;

class Widget : public std::enable_shared_from_this<Widget> {
public:
    Widget(): _id(currentId++){}
    
    Widget(WidgetId id): _id(id){ currentId = _id; }
    
    int getId() const { return _id; }
    
    void makeLogEntry() const;
    
    void process(); 

private:

    int _id;
    std::vector<std::shared_ptr<Widget>> _processedWidgets; 
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

#pragma once
#include <memory>
#include <vector>

using WidgetId = unsigned; 

static WidgetId  currentId;


class Widget: public std::enable_shared_from_this<Widget>{
public:
    Widget();
    Widget(WidgetId id);
    ~Widget();

    WidgetId getId() const;
    
    void makeLogEntry() const;
    
    void process(); 

private:
    class WidgetImpl;
    std::unique_ptr<WidgetImpl> _impl; // pimpl idiom
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

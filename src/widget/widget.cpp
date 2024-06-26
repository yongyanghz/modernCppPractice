#include <cstdio>
#include "widget.h"


class Widget::WidgetImpl{
public:
    WidgetImpl(): _id(currentId++){}
    WidgetImpl(WidgetId id): _id(id){ currentId = _id; }
    WidgetId getId()const{ return _id; }
    void makeLogEntry() const;
    void process();
private:
    WidgetId  _id;
    std::vector<WidgetId> _processedWidgets; 
};

void
Widget::WidgetImpl::makeLogEntry() const
{
    printf("Widget id: %d\n", _id);
}

void 
Widget::WidgetImpl::process()
{
    _processedWidgets.push_back(getId());
}

Widget::Widget():
    _impl(new WidgetImpl(), &delWidgetImpl)
{ 
}
    
Widget::Widget(WidgetId id):
    _impl(new WidgetImpl(id), &delWidgetImpl)
{
}
 
Widget::~Widget(){}

void 
Widget::delWidgetImpl(WidgetImpl* impl)
{
    delete impl;
}

WidgetId 
Widget::getId() const
{
    return _impl->getId();
}
    
void 
Widget::makeLogEntry() const
{
    _impl->makeLogEntry();
}
    
void 
Widget::process()
{
    _impl->process();
} 


void
WidgetFac::makeLogEntry() const
{
    printf("Widget id: %d\n", _id);
}

void 
WidgetFac::process()
{
    _processedWidgets.emplace_back(shared_from_this());
}

void 
WidgetFac::addFilter(FilterContainer &filters)
{
    // Capture only to non-static local variables

    // error: 'this' cannot be implicitly captured in this context
    // filters.emplace_back([](int value){
    //     return value % _divisor == 0;
    // });
    
    // error: 'this' cannot be implicitly captured in this context
    // filters.emplace_back([_divisor](int value){
    //     return value % _divisor == 0;
    // });

    // filters.emplace_back([=](int value){
    //     return value % _divisor == 0;
    // });
    // What's captured in default by value is this pointer
    // auto currentObjectPtr = this;
    // filters.emplace_back([currentObjectPtr](int value){
    //     return value % currentObjectPtr->_divisor == 0;
    // });

    auto divisor = _divisor;            // copy data memeber
    filters.emplace_back([=](int value){
        return value % divisor == 0;    // capture the copoy
    });


    
}


void makeLogEntry(std::string text, TimePoint time)
{
    std::cout<<text<<" "<<std::chrono::system_clock::to_time_t(time)<<std::endl;
}

void process(Widget& lvalArg) // process lvalues
{
    std::cout<<"Calling lvalue"<<std::endl;
    lvalArg.process();
}


void process(Widget&& rvalArg) // process rvalues
{
    std::cout<<"Calling rvalue"<<std::endl;
    rvalArg.process();
}
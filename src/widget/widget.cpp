#include <cstdio>

#include "widget.h"


class Widget::WidgetImpl{
public:
    WidgetImpl(): _id(currentId++){}
    WidgetImpl(WidgetId id): _id(id){ currentId = _id; }
    WidgetId getId()const{ return _id; }
    void makeLogEntry() const;
    void process();
    void setWidget(Widget * w){ _widget = w;}
private:
    Widget* _widget;
    WidgetId  _id;
    std::vector<std::shared_ptr<Widget>> _processedWidgets; 
};


void
Widget::WidgetImpl::makeLogEntry() const
{
    printf("Widget id: %d\n", _id);
}

void 
Widget::WidgetImpl::process()
{
    _processedWidgets.emplace_back(_widget);
}

Widget::Widget()
{ 
    _impl = std::make_unique<WidgetImpl>();
}
    
Widget::Widget(WidgetId id)
{
    _impl = std::make_unique<WidgetImpl>(id); 
}
 
Widget::~Widget(){}

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
    _impl->setWidget(this);
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
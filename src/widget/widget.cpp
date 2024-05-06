#include <cstdio>

#include "widget.h"

void
Widget::makeLogEntry() const
{
    printf("Widget id: %d\n", _id);
}

void 
Widget::process()
{
    _processedWidgets.emplace_back(shared_from_this());
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
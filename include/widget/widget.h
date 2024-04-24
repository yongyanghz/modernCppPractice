#pragma once

static int currentId;

class Widget{
public:

    Widget(): _id(currentId++){}
    int getId(){ return _id; }
    void makeLogEntry();

private:
    int _id; 
};


#pragma once

#include <vector>
#include <functional>


using FilterContainer = 
    std::vector<std::function<bool(int)>>;


class LambdaExpressionsTest
{
public:
    void run();

    void lamdaExpressionClosure();
    
    void avoidDefaultCaptureModes();
   
    void addDivisorFilter(FilterContainer & filters);

    void initCaptureToMoveObjectsIntoClosures();

    void useDecltypeOnAutoAndAnd();

    void preferLamdbaToBind();
};


template<typename T>
auto normalize(T&& val)
{
    return std::move(val); // move val into return value
}

class SomeCompilerGeneratedClassName{
public:
    template<typename T>
    auto operator()(T x) const { return normalize(x); }
};
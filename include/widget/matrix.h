#pragma once

#include<vector>


class Matrix{
public:
    Matrix(int rowNum, int colNum);


    int getRowNum() const { return _r; } 
    int getColNum() const { return _c; } 
   
    void operator+=(const Matrix& rhs);

private:
    std::vector<std::vector<int>> _m;
    int _r;
    int _c;
};

template<typename T>
Matrix
operator+(T&& lhs,  T& rhs)
{
    lhs += rhs;
    return std::forward<T>(lhs);  // move rvalue into return value, copy lvalue
}
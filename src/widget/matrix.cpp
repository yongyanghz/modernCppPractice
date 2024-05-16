#include "matrix.h"
#include <iostream>

Matrix::Matrix(int rowNum, int colNum)
{
    _r = rowNum;
    _c = colNum;
    for(int i=0; i<rowNum; i++){
        std::vector<int> vec(colNum, 0);
        _m.push_back(vec);
    }
}


// Matrix 
// operator+(Matrix&& lhs, const Matrix& rhs)
// {
//     lhs += rhs;
//     return std::move(lhs); // move lhs into return value
// }

// Matrix 
// operator+(Matrix&& lhs, const Matrix& rhs)
// {
//     lhs += rhs;
//     return lhs; // copy lhs into return value
// }


void
Matrix::operator+=(const Matrix& rhs)
{
    if(this->_r != rhs._r || 
        this->_c != rhs._c){
            return;
    }
    for(int i=0; i<_r; ++i){
        for(int j=0; j<_c; ++j){
            this->_m[i][j] += rhs._m[i][j];
        }
    }
}



#ifndef SYMETRIC_MATRIX_H
#define SYMETRIC_MATRIX_H

#include <iostream>
#include <vector>
#include <iterator>
#include "matrix.h"

template <typename Type, int size>
class Symetric_Matrix : public Matrix<Type, size, size>
{
    public:
        Symetric_Matrix(const Type value = 1);
        virtual ~Symetric_Matrix() = default;

    private:

};

template <typename Type, int size>
Symetric_Matrix<Type, size>::Symetric_Matrix(const Type value) {

    for(int i = 0; i < size; ++i) {
        (*this)(i,i) = value;
    }
    cout << "symetric constractor -> this : " << endl << *this << endl;
}

template <typename Type, int row, int column>
Matrix<Type, row, column> operator *(const Type const_num, const Matrix<Type, row, column>& matrix) {
    cout << "call symetric matrix function -> num * matrix : " << endl;
    Symetric_Matrix<Type, row> temp_sym_mat(const_num);
    return temp_sym_mat * matrix;
}

// not needed no commutative bad mathematics... just for testing
template <typename Type, int row, int column>
Matrix<Type, row, column> operator *(const Matrix<Type, row, column>& matrix, const Type const_num) {
    return const_num * matrix;
}



#endif // SYMETRIC_MATRIX_H

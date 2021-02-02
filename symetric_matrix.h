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
    cout << "this : " << endl << *this << endl;
}

template <typename Type, int row, int column>
Matrix<Type, row, column> operator *(const Type const_num, const Matrix<Type, row, column>& mat) {
    cout << "cal num * mat : " << endl;
    Symetric_Matrix<Type, row> temp_sym_mat(const_num);
    return temp_sym_mat * mat;
}

// not needed no commutative
template <typename Type, int row, int column>
Matrix<Type, row, column> operator *(const Matrix<Type, row, column>& mat, const Type const_num) {
    return const_num * mat;
}



#endif // SYMETRIC_MATRIX_H

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <iterator>
//#include <exception>

using std::vector;
using std::cout;
using std::endl;

template <typename Type = int, int row = 1, int column = 1>
class Matrix
{
    public:
        Matrix(const Type default_value = 0) : row_(row), col_(column), matrix_(row, vector<Type>(column, default_value)) {}
        Matrix(const Matrix<Type, row, column>& other) : row_(other.row_), col_(other.col_), matrix_(other.matrix_) {}
        Matrix(Matrix<Type, row, column>&& other) : row_(other.row_), col_(other.col_), matrix_(other.matrix_) {cout<< "constractor &&" << endl; delete &other; }

        virtual ~Matrix() {} //= default; //{ cout << "destructor Matrix" << endl << *this << endl; }//{ for(auto &it : *this) { /*delete[] &(it); } delete &row_;  delete &col_; }//= default; // { cout << "destructor" << endl; }

// ---------------------------------------------- basic operators  ---------------------------------------------------------

        Matrix<Type, row, column>& operator =(const Matrix& other) { matrix_= other.matrix_; return *this; }
        Matrix<Type, row, column>& operator =(const Matrix&& other) { cout<< " assign  =&&" << endl; return *this = other; }

        bool operator ==(const Matrix& other) const { return (row_ == other.row_) && (col_ == other.col_) && (matrix_ == other.matrix_); }
        bool operator !=(const Matrix& other) const { return !(*this == other); }

        Matrix<Type, row, column>& operator +=(const Matrix<Type, row, column>& other);
        Matrix<Type, row, column>& operator -=(const Matrix<Type, row, column>& other);
        Matrix<Type, row, column>& operator *=(const Matrix<Type, row, column>& other);

// --------------------------------- basic functions and overloading operators  ---------------------------------------------------------

        vector<Type>& operator [](int index) { return matrix_[index]; }
        const vector<Type>& operator [](int index) const { return matrix_[index]; }

        vector<Type>& operator ()(size_t index)  { return matrix_.at(index); }
        const vector<Type>& operator ()(size_t index) const { return matrix_.at(index); }

        Type& operator ()(size_t i, size_t j)  { return matrix_.at(i).at(j); }
        const Type& operator ()(size_t i, size_t j) const { return matrix_.at(i).at(j); }

        Type avg() const;

// --------------------------------------- iterators new 2 - using indexes and operators () -------------------------------------------------------------------------------
/*
        class Iterator {
            public:
                Iterator(Matrix& ref, bool is_end) : ref_(ref), row_index_(is_end? row-1 : 0), col_index_(is_end? column: 0), row_(row),  col_(column) {}
                bool operator==(const Iterator& other) const { return (&ref_ == &other.ref_) && (row_index_ == other.row_index_) && (col_index_ == other.col_index_); }
                bool operator!=(const Iterator& other) const { return !(*this == other); }

                Iterator& operator++(int) {
                    if(row_index_ <  row_-1 && col_index_ < col_-1)  { col_index_++; return *this; }
                    if(row_index_ <  row_-1 && col_index_ == col_-1) { col_index_ = 0; row_index_++; return *this; }
                    col_index_++;
                    return *this;
                }
                Iterator& operator++() { return (*this)++; }
                Type& operator*() { return ref_(row_index_, col_index_); }

            private:
                Matrix& ref_;
                int row_index_;
                int col_index_;
                const int row_;
                const int col_;
        };
        Iterator begin() { return Iterator(*this, false); }
        Iterator end() { return Iterator(*this, true); }


        class const_Iterator {
            public:
                const_Iterator(const Matrix& ref, bool is_end) : ref_(ref), row_index_(is_end? row-1 : 0), col_index_(is_end? column: 0), row_(row),  col_(column) {}
                bool operator==(const const_Iterator& other) const { return (&ref_ == &other.ref_) && (row_index_ == other.row_index_) && (col_index_ == other.col_index_); }
                bool operator!=(const const_Iterator& other) const { return !(*this == other); }

                const_Iterator& operator++(int) {
                    if(row_index_ <  row_-1 && col_index_ < col_-1)  { col_index_++; return *this; }
                    if(row_index_ <  row_-1 && col_index_ == col_-1) { col_index_ = 0; row_index_++; return *this; }
                    col_index_++;
                    return *this;
                }
                const_Iterator& operator++() { return (*this)++; }
                const Type& operator*() const { return ref_(row_index_, col_index_); }

            private:
                const Matrix& ref_;
                int row_index_;
                int col_index_;
                const int row_;
                const int col_;
        };
        const_Iterator begin() const { return const_Iterator(*this, false); }
        const_Iterator end() const { return const_Iterator(*this, true); }

*/
// ------------------------------------------------- iterators new 3 - using vector's class iterators -------------------------------------------------------------------------------

        class Iterator {
            public:
                Iterator(vector<vector<Type>>& ref, int row_length, bool is_begin)
                    : it_row_index(is_begin ? ref.begin() : ref.end()),
                      it_row_end(ref.end()),
                      it_col_index(is_begin ? ref.at(0).begin(): ref.at(row_length - 1).end()),
                      it_col_end(is_begin ? ref.at(0).end() : ref.at(row_length - 1).end())
                {}

                bool operator==(const Iterator& other) const { return (it_row_index == other.it_row_index) ;}
                bool operator!=(const Iterator& other) const { return !(*this == other); }

                Type& operator*() { return *it_col_index; }
                Iterator& operator++() { return (*this)++; }

                Iterator& operator++(int) {
                    if(it_col_index != it_col_end) { if(++it_col_index == it_col_end) NextRow(); }
                    else if(it_row_index != it_row_end) { NextRow(); }
                    return *this;
                }

                void NextRow() {
                    ++it_row_index;
                    if(it_row_index != it_row_end) {
                        it_col_index = (*it_row_index).begin();
                        it_col_end = (*it_row_index).end();
                    }
                }

            private:
                typename vector<vector<Type>>::iterator it_row_index;
                const typename vector<vector<Type>>::iterator it_row_end;
                typename vector<Type>::iterator it_col_index;
                typename vector<Type>::iterator it_col_end;

        };
        Iterator begin() { return Iterator(matrix_, row_, true); }
        Iterator end() { return Iterator(matrix_,  row_, false); }



        class ConstIterator {
            public:
                ConstIterator(const vector<vector<Type>>& ref, int row_length, bool is_begin)
                    : it_row_index(is_begin ? ref.begin() : ref.end()),
                      it_row_end(ref.end()),
                      it_col_index(is_begin ? ref.at(0).begin() : ref.at(row_length - 1).end()),
                      it_col_end(is_begin ? ref.at(0).end() : ref.at(row_length - 1).end())
                {}

                bool operator==(const ConstIterator& other) const { return (it_row_index == other.it_row_index); }
                bool operator!=(const ConstIterator& other) const { return !(*this == other); }

                const Type& operator*() { return *it_col_index; }
                ConstIterator& operator++() { return (*this)++; }

                ConstIterator& operator++(int) {
                    if(it_col_index != it_col_end) { if(++it_col_index == it_col_end) NextRow(); }
                    else if(it_row_index != it_row_end) { NextRow(); }
                    return *this;
                }

                void NextRow() {
                    ++it_row_index;
                    if(it_row_index != it_row_end) {
                        it_col_index = (*it_row_index).begin();
                        it_col_end = (*it_row_index).end();
                    }
                }

            private:
                typename vector<vector<Type>>::const_iterator it_row_index;
                const typename vector<vector<Type>>::const_iterator it_row_end;
                typename vector<Type>::const_iterator it_col_index;
                typename vector<Type>::const_iterator it_col_end;

        };
        ConstIterator begin() const { return ConstIterator(matrix_, row_, true); }
        ConstIterator end() const { return ConstIterator(matrix_,  row_, false); }


// ------------------------------------------------- private -------------------------------------------------------------------------------

    private:
        const int row_;
        const int col_;
        vector<vector<Type>> matrix_;

};



// ***************************************************** implementation of member functions *****************************************************************************************

template <typename Type, int row, int column>
Matrix<Type, row, column>& Matrix<Type, row, column>::operator +=(const Matrix<Type, row, column>& other) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            (*this)(i,j) += other(i,j);
        }
    }
    return *this;
}

template <typename Type, int row, int column>
Matrix<Type, row, column>& Matrix<Type, row, column>::operator -=(const Matrix<Type, row, column>& other) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            (*this)(i,j) -= other(i,j);
        }
    }
    return *this;
}

template <typename Type, int row, int column>
Matrix<Type, row, column>& Matrix<Type, row, column>::operator *=(const Matrix<Type, row, column>& other) {
    return *this = *this * other;
}

// ***************************************************** implementation of none member functions *****************************************************************************

template <typename Type, int row, int column>
std::ostream& operator <<(std::ostream& os, Matrix<Type, row, column>& mat) {
    int col = 0;
    os << endl;
    for(auto& it : mat) {
        os << it << " ";
        if(++col == column) {os << endl; col = 0;}
    }
    os << endl;
    return os;
}

template <typename Type, int row, int column>
std::ostream& operator <<(std::ostream& os, const Matrix<Type, row, column>& mat) {
    int col = 0;
    os << endl;
    for(auto& it : mat) {
        os << it << " " << " at: " << &it << endl;
        if(++col == column) {os << endl; col = 0;}
    }
    os << endl;
    return os;
}

// ------------------------------------------------------------------ implementation of none member functions ---------------------------------------------------------


template <typename Type, int row, int column>
Type min(const Matrix<Type, row, column>& mat) {
    Type temp_min = mat(0, 0);
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            Type temp_value = mat(i,j);
            if(temp_min > temp_value) {
                temp_min = temp_value;
            }
        }
    }
    return temp_min;
}

template <typename Type, int row, int column>
Type Matrix<Type, row, column>::avg() const {
    Type temp_average = 0;
    int count = 0;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            temp_average += (*this)(i,j);
            ++count;
        }
    }
    return (temp_average/count);
}

template <typename Type, int row, int column>
Matrix<Type, row, column> operator +(const Matrix<Type, row, column>& mat1, const Matrix<Type, row, column>& mat2) {
    Matrix<Type, row, column> temp_mat = mat1;
    return temp_mat += mat2;
}

template <typename Type, int row, int column>
Matrix<Type, row, column> operator -(const Matrix<Type, row, column>& mat1, const Matrix<Type, row, column>& mat2) {
    Matrix<Type, row, column> temp_mat = mat1;
    return temp_mat -= mat2;
}

template <typename Type, int row1, int row2, int column1, int column2>
Matrix<Type, row1, column2> operator *(const Matrix<Type, row1, column1>& mat1, const Matrix<Type, row2, column2>& mat2) {
    if(column1 != row2) throw std::exception();
    cout << "operator* -> cal num * mat : " << endl;

    Matrix<Type, row1, column2> temp_mat;

    for(int advence = 0; advence < column2; ++advence) {
        for(int i = 0; i < row1; ++i) {
            for(int j = 0; j < column1; ++j) {
       //         cout << temp_mat << endl;
                temp_mat(i,advence) += mat1(i,j) * mat2(j,advence);
            }
        }
    }
//            cout << "operator* -> cal num * mat : " << temp_mat << endl;

    return temp_mat;
}


#endif // MATRIX_H

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

        virtual ~Matrix() = default; //{ cout << "destructor Matrix" << endl << *this << endl; }//{ for(auto &it : *this) { /*delete[] &(it); } delete &row_;  delete &col_; }//= default; // { cout << "destructor" << endl; }

// ---------------------------------------------- basic operators  ---------------------------------------------------------

        Matrix<Type, row, column>& operator =(const Matrix& other) { matrix_= other.matrix_; return *this; }
        Matrix<Type, row, column>& operator =(const Matrix&& other) { cout<< " assign  =&&" << endl; return *this = (other); }

        bool operator ==(const Matrix& other) const { return (&this->matrix_ == &other.matrix_) && (row_ == other.row_) && (col_ == other.col_); }
        bool operator !=(const Matrix& other) const { return !(*this == other); }

        Matrix<Type, row, column>& operator +=(const Matrix<Type, row, column>& other);
        Matrix<Type, row, column>& operator -=(const Matrix<Type, row, column>& other);
        Matrix<Type, row, column>& operator *=(const Matrix<Type, row, column>& other);

// --------------------------------- basic functions and overloading operators  ---------------------------------------------------------

        vector<Type>& operator [](int index) { return matrix_[index]; }
        const vector<Type>& operator[](int index) const { return matrix_[index]; }

        vector<Type>& operator ()(size_t index)  { return matrix_.at(index); }
        const vector<Type>& operator ()(size_t index) const { return matrix_.at(index); }

        Type& operator ()(size_t i, size_t j)  { return matrix_.at(i).at(j); }
        const Type& operator ()(size_t i, size_t j) const { return matrix_.at(i).at(j); }

        Type avg() const;

// ------------------------------------------------- iterators old -------------------------------------------------------------------------------
/*
         typename vector<vector<Type>>::iterator begin() {
            cout << (&matrix_) << " begin() at -> " << &matrix_ << endl;
            return matrix_.begin();
        }

        const typename vector<vector<Type>>::const_iterator begin() const {
            cout << (*this)(0,0) << " const_begin() at -> " << &(*this)(0,0) << endl;
            return matrix_.begin();
        }

        typename vector<vector<Type>>::iterator end() {
            cout << &matrix_[row_-1] << " end() at -> " << &matrix_[row_-1] << endl;
            return matrix_.end();
        }
        const typename vector<vector<Type>>::const_iterator end() const {
             cout << (*this)(row_-1,col_-1) << " const end() at -> " << &(*this)(row_-1,col_-1) << endl;
             return matrix_.end();
        }

// ------------------------------------------------- iterators new 1 -------------------------------------------------------------------------------
        class Iterator {
            public:
                Iterator(Matrix& ref, int index) : ref_(ref), index_(index) {}
                bool operator==(const Iterator& other) { return (&ref_ == &other.ref_) && (index_ == other.index_); }
                bool operator!=(const Iterator& other) { return !(*this == other); }
                Iterator& operator++(int) {
                    index_++;
                    return *this;
                }
                vector<Type>& operator*() { return ref_(index_); }

            private:
                Matrix& ref_;
                int index_;
        };

         Iterator begin() {
            cout << (&matrix_) << " begin() at -> " << &matrix_ << endl;
            return Iterator(*this, 0); //matrix_.begin();
        }

        Iterator end() {
            cout << &matrix_[row_-1] << " end() at -> " << &matrix_[row_-1] << endl;
            return Iterator(*this, row_);  //matrix_.end();
        }

*/
// ------------------------------------------------- iterators new 2 -------------------------------------------------------------------------------
        class Iterator {
            public:
                Iterator(Matrix& ref, bool is_end) : ref_(ref), row_index_(is_end? row-1 : 0), col_index_(is_end? column: 0), row_(row),  col_(column) {}
                bool operator==(const Iterator& other) { return (&ref_ == &other.ref_) && (row_index_ == other.row_index_) && (col_index_ == other.col_index_); }
                bool operator!=(const Iterator& other) { return !(*this == other); }

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

         Iterator begin() {
         //   cout << "first matrix value: " << matrix_(0)(0) << " begin() at -> " << &matrix_ << endl;
            return Iterator(*this, false);
        }

        Iterator end() {
         //   cout << "last matrix value: " << matrix_(col_-1)(row_-1) << " end() at -> " << &matrix_[row_-1] << endl;
            return Iterator(*this, true);
        }


        class const_Iterator {
            public:
                const_Iterator(const Matrix& ref, bool is_end) : ref_(ref), row_index_(is_end? row-1 : 0), col_index_(is_end? column: 0), row_(row),  col_(column) {}
                bool operator==(const const_Iterator& other) { return (&ref_ == &other.ref_) && (row_index_ == other.row_index_) && (col_index_ == other.col_index_); }
                bool operator!=(const const_Iterator& other) { return !(*this == other); }

                const_Iterator& operator++(int) {
                    if(row_index_ <  row_-1 && col_index_ < col_-1)  { col_index_++; return *this; }
                    if(row_index_ <  row_-1 && col_index_ == col_-1) { col_index_ = 0; row_index_++; return *this; }
                    col_index_++;
                    return *this;
                }
                const_Iterator& operator++() { return (*this)++; }
                const Type& operator*() { return ref_(row_index_, col_index_); }

            private:
                const Matrix& ref_;
                int row_index_;
                int col_index_;
                const int row_;
                const int col_;
        };

         const_Iterator begin() const {
         //   cout << "first matrix value: " << matrix_(0)(0) << " begin() at -> " << &matrix_ << endl;
            return const_Iterator(*this, false);
        }

        const_Iterator end() const {
         //   cout << "last matrix value: " << matrix_(col_-1)(row_-1) << " end() at -> " << &matrix_[row_-1] << endl;
            return const_Iterator(*this, true);
        }

// ------------------------------------------------- private -------------------------------------------------------------------------------

    private:
        const int row_;
        const int col_;
        vector<vector<Type>> matrix_;
//        vector<Type> vec_ = vector<Type> (row_, 55);

        bool compareEach() const;

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

/*
template <typename Type, int row, int column>
std::ostream& operator <<(std::ostream& os, const Matrix<Type, row, column>& mat) {
    os << endl << "matrix operator << this is matix (vector<vector<Type>>) = " << endl;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            os << mat(i,j) << " ";
        }
        os << endl;
    }
    os << "matrix address: " << &mat << endl;

    return os;
}

*/

template <typename Type, int row, int column>
std::ostream& operator <<(std::ostream& os, const Matrix<Type, row, column>& mat) {
    int col = 0;
    os << endl;
    for(auto& it : mat) {
        os << it << " ";
        if(++col == column) {os << endl; col = 0;}
    }
    os << endl;
    return os;
}

/*
template <typename Type, int row, int column>
std::ostream& operator <<(std::ostream& os, const Matrix<Type, row, column>& mat) {
    os << "this is matix (vector<vector<Type>>) = " << endl;
    for(typename vector<vector<Type>>::const_iterator mat_it = mat.const_begin(); mat_it < mat.const_end(); ++mat_it) {
        os << mat_it;

    }
            os << endl;

    os << "matrix address: " << &mat << endl;

    return os;
}
*/

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
Type Matrix<Type, row, column> :: avg() const {
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
/*
template <typename Type, int row, int column>
Matrix<Type, row1, column2> operator *(const Matrix<Type, row1, column1>& mat1, const Matrix<Type, row2, column2>& mat2) {
    Matrix<Type, row1, column2> temp_mat;

    for(int advence = 0; advence < column2; ++advence) {
        for(int i = 0; i < row1; ++i) {
            for(int j = 0; j < column1; ++j) {
       //         cout << temp_mat << endl;
                temp_mat(i,advence) += mat1(i,j) * mat2(j,advence);
            }
        }
    }
    return temp_mat;
}

template <typename Type, int row, int column>
Matrix<Type, row, column>&& operator +(const Matrix<Type, row, column>& mat1, const Matrix<Type, row, column>& mat2) {
    Matrix<Type, row, column> temp_mat;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            Type temp_value = mat.getValue(i,j);
            if(temp_min > temp_value) {
                temp_min = temp_value;
            }
        }
    }
    return (&this->matrix_ == &other.matrix_) && (row_ == other.row_) && (col_ == other.col_);
}
*/


#endif // MATRIX_H

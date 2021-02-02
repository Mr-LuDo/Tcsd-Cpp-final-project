#include <iostream>
#include <memory>
#include "matrix.h"
#include "symetric_matrix.h"
#include <iterator>
#include <vector>
//#include <stdlib.h>


using namespace std;

void Clear();


int main () {
    const Matrix<int, 3, 2> m1(7); // Creates 3*2 matrix, with all the default elements set to 0;
    cout << m1 << endl;
    Matrix<int, 3, 3> m2(4); // Creates 3*3 matrix, with the default elements equals to 4;
    cout << m2 << endl;
    const Matrix<int, 3, 3> m3 = m2; // C-py constructor may take O(MN) and not O(1).
    cout << m3 << endl;
    const Matrix<int> m0; // Creates 3*2 matrix, with all the default elements set to 0;
    cout << m0 << endl;

    try { m2(50,1) = 3; }
    catch(const std::exception& e) { cerr << e.what() << endl; }
    m2[1][2] = 15;
    cout << m2 << endl;

    cout << "min(m2) = " << min(m2) << endl;


    // min() returns the minimal value in the matrix.
    if (min(m1) < min(m3))
        cout << "Min value of m3(" << min(m3) << ") is bigger than min value of m1(" << min(m1) << ")" << endl;



    if (m1.avg() < m3.avg()) // Compares the average of the elements
        cout << "Average value of m3(" << m3.avg() << ") is bigger than average value of m1(" << m1.avg() << ")" << endl;


    m2(0, 0) = 13;
    cout << m2[0][0] << " " << m2[1][0] << endl; // Should print "13 4"

    cout << "printing matrix memory locationl" << endl;
    cout << "int size: " << sizeof(int) << endl;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            cout << &m2(i,j) << endl;
        }
    }


    int arr[2] = {16};
    cout << endl << "printing iterator to int arr auto code:" << endl;
    for(auto &it_arr : arr){
        cout << it_arr << " at -> " << &it_arr << endl;
    }

    cout << endl << "printing iterator to vector<int> auto code:" << endl;
    vector<int> vec(10,33);
    for(auto &it : vec){
        cout << it << " at -> " << &it << endl;
    }

    vector<int> vec2(7, 3);
    vec2[2] = 12;
    cout << endl << "printing iterator to vector<int> manual code:" << endl;
    for(vector<int>::iterator it3 = vec2.begin() ; it3 != vec2.end(); ++it3){
        cout << *it3 << " at -> " << &(*it3) << endl;
    }

    Matrix<int, 3, 3> mv1(4);
    cout << endl << "printing iterator to Matrix object vector<int> auto code: " << endl;
//    for(auto &it2 : mv1.get_vector()){
//        cout << it2 << " at -> " << &it2 << endl;
//    }

/*
    cout << endl << "printing iterator to Matrix object vector<int> manual code: " << endl;
    try {
        vector<int>::iterator temp = mv1.begin();
        cout << *temp << " main() begin() at -> " << &(*temp) << endl;

        vector<int>::iterator temp2 = mv1.end();
        cout << *temp2 << " main() end() at -> " << &(*temp2) << endl;
    }
    catch(const std::exception& e) { cerr << e.what() << endl; }

    for(vector<int>::iterator temp3 = mv1.begin() ; temp3 != mv1.end(); ++temp3){
        cout << *temp3 << " at -> " << &(*temp3) << endl;
    }

*/    cout << endl << "printing iterator to Matrix object vector<int> auto code: " << endl;
  //  vector<int>::iterator it2_7 = mv1.begin();   cout << &it2_7 << endl;
    auto it2_6 = begin(mv1);  cout << &(*it2_6) << endl;
    auto it2_2 = mv1.begin(); cout << &(*it2_2) << endl;

    Matrix<int, 3, 3> mv2(4);
    mv2(0,2) = 1;
    mv2(1,1) = 2;
    mv2(2,2) = 6;
    mv2(2,0) = 7;
    for(auto &it_mv2_1 : mv2){
        for(auto &it_mv2_2 : it_mv2_1){
            cout << "mv2: " << it_mv2_2 << " at -> " << &it_mv2_2 << endl;
        }
    }
/*    for(auto &it2_5 : mv1){
        cout << it2_5 << " at -> " << &(it2_5) << endl;
    }


    cout << endl << "testing on full matrix: " << endl;
    Matrix<int, 3, 3> m6(4);
    cout << "m6 : " << m6 << "at -> " << &(m6) << endl;

*/


//    Matrix<int, 3,3> mv3 = mv2 + mv1;
//    cout << "mv3 = mv2 + mv1" << endl <<  mv2 <<  mv1 << mv3 << endl;

//    mv2 = mv1;

    Matrix<int, 3,3> mt1(1);
    mt1(0,0)= 5;
    mt1(1,1)= 12;
    mt1(2,2)= 7;
    mt1(0,1)= 6;
    mt1(1,2)= 9;
    mt1(2,0)= 2;

    Matrix<int, 3,3> mt2(2);
    mt2(0,0)= 0;
    mt2(1,1)= 5;
    mt2(2,2)= 3;

    mt2(0,1)= 0;
    mt2(1,2)= 5;
    mt2(2,0)= 3;

    Matrix<int, 3,3> mt3 = mt1 * mt2;

    cout << "mt3 = mt1 + mt2" << endl <<  mt1 <<  mt2 << mt3 << endl;


    Symetric_Matrix<int, 3> s_mat(2);
    cout << "symetric matrix" << endl << s_mat << endl;
    cout << "2 * mt1 = " << mt1 << 2 * mt1 << " mt1 * 2 = " << mt1 * 2 << endl ;


    cout << "m1 = " << m1 << " before deleting at -> " << &(m1) << endl;

    for(auto &it_m1 : m1){
        cout << "m1 = " << &it_m1 << " at -> " << &(it_m1) << endl;
    }
    for(auto &it_m2 : m2){
        cout << "m2 = " << &it_m2 << " at -> " << &(it_m2) << endl;
      //  &it_m2 = 45;
    }
    cout << "new m2 after changes: " << m2 << endl;

    Matrix<int, 3, 3> m8(34);
    m2 = move(m8);
    cout << "new m2 after changes&&: " << m2 << "old m8 after deletion: " << endl << m8 << endl;

//    try {
//        delete &m1;
        //cout << "m1 after deleted: " << m1 << endl;
//    }
//    catch(const std::exception& e) { cerr << e.what() << endl; }

//    cout << "this is m1" << m1 << endl;
//    const Matrix<int, 3, 2> m1(7); // Creates 3*2 matrix, with all the default elements set to 0;
//    cout << "this is m1" << m1 << endl;



        cout << "m1" << m1 << endl;
        cout << "m2" << m2 << endl;
        cout << "m3" << m3 << endl;

    try {
        cout << "m2 + m3" << m2 + m3 << endl;
        cout << "m3 * m1" << m3 * m1 << endl;    // You can choose the format of matrix printing;
        cout << "m1 * m2" << m1 * m2 << endl;            // This should throw an exception
    } catch (const std::exception& e){//const Matrix<int, 3, 2>::IllegalOperation& e) {
        cout << e.what() << endl;
    }



    Matrix<int, 3, 3> m4;
    m4 = m3;
    cout << m4 << endl;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            m4(i, j) = i+j;
    cout << m4 << endl;

    cout << "m4[1][1] = " << m4[1][1] << endl;

    cout << "m4[1][1] = " << m4(1,1) << endl; // m4(1,1) same result as m4[1][1]


    Matrix<int, 3, 3> m5(3);
    m5 = 2 * m4;
    cout << m5 << endl;
    Matrix<int, 3, 3> m6(m4);
    cout << m6 << endl;
    m5 += m4;
    cout << m5 << endl;

    if (m6 != m5)
      cout << "m6 != m5" << endl;

    Matrix<Matrix<int, 3, 2>, 4, 4> composite(m1); // Creates matrix, where each element is m1;

    cout << composite;


    unique_ptr<Matrix<int, 3, 3>> symetric_matrix(new Symetric_Matrix<int, 3>(5)); // SymetricMatrix matrix 3*3 with default element equals to 5;

    (*symetric_matrix)(1, 2) = 8;
    cout << "this is unique pointer to symetric matrix: " << endl << *symetric_matrix << endl;

    cout << (*symetric_matrix)(1, 2) << " " << (*symetric_matrix)(2, 1) << endl;; // Should print "8 8"
    cout << (*symetric_matrix)[1][2] << " " << (*symetric_matrix)[2][1] << endl;; // Should print "8 8"

//------------------------------------ testing stuff ----------------------------------------------------
    Clear();

    Matrix<int, 3, 3> tm1(5);
    cout << "this is tm1: " << tm1 << endl;
    cout << "tm1[1].size() :" << tm1[1].size() << endl;

    cout << "tm1[1] print :" << endl;
    tm1(1,0) = 1;
    tm1(1,1) = 2;
    tm1(1,2) = 3;
    for(auto& it : tm1[1]) {
        cout << "tm1[1][it] print :" << it << endl;
    }





//--------------------------------------- end  ----------------------------------------------------


    return 0;
}


void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}

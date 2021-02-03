#include <iostream>
#include <memory>
#include "matrix.h"
#include "symetric_matrix.h"
#include <iterator>
#include <vector>
//#include <stdlib.h>


using namespace std;

void Clear();
void GoDown();


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

    GoDown();
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
    auto it2_6 = begin(mv1);  cout << &(*it2_6) << endl;
    auto it2_2 = mv1.begin(); cout << &(*it2_2) << endl;

    Matrix<int, 3, 3> mv2(4);
    mv2(0,2) = 1;
    mv2(1,1) = 2;
    mv2(2,2) = 6;
    mv2(2,0) = 7;


   for(auto& it2_5 : mv1){
        cout << &it2_5 << " at -> " << &(it2_5) << endl;
    }


    cout << endl << "testing on full matrix: " << endl;
    Matrix<int, 3, 3> m6(4);
    cout << "m6 : " << m6 << "at -> " << &(m6) << endl;




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
    Matrix<int, 3, 3> m7(m4);
    cout << m7 << endl;
    m5 += m4;
    cout << m5 << endl;

    if (m7 != m5)
        cout << "m7 != m5" << endl;








    GoDown();
    cout << "------------------ composite ----------------------" << endl;
    Matrix<Matrix<int, 3, 3>, 4, 4> composite(m5); // Creates matrix, where each element is m5;
    cout << "this is m5: " << m5 << endl;
    cout << composite;
    cout << composite(3,3);

    GoDown();











    unique_ptr<Matrix<int, 3, 3>> symetric_matrix(new Symetric_Matrix<int, 3>(5)); // SymetricMatrix matrix 3*3 with default element equals to 5;

    (*symetric_matrix)(1, 2) = 8;
    cout << "this is unique pointer to symetric matrix: " << endl << *symetric_matrix << endl;

    cout << (*symetric_matrix)(1, 2) << " " << (*symetric_matrix)(2, 1) << endl;; // Should print "8 8"
    cout << (*symetric_matrix)[1][2] << " " << (*symetric_matrix)[2][1] << endl;; // Should print "8 8"

//------------------------------------ testing stuff ----------------------------------------------------
    //Clear();
    GoDown();

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


    cout << "tm1[1] print :" << endl;
    tm1(1,0) = 1;
    tm1(1,1) = 2;
    tm1(1,2) = 3;
    for(auto& it : tm1[1]) {
        cout << "tm1[1][it] print :" << it << endl;
    }

//--------------------------------------- end  ----------------------------------------------------
    GoDown();

    cout << "tm1[1] print :" << endl;
    tm1(1,0) = 1;
    tm1(1,1) = 2;
    tm1(1,2) = 3;
    tm1(0) = {7,8,9};
    cout << "this is tm1: " << tm1 << endl;

    for(auto& it : tm1(1)) {
        cout << "tm1[1][it] print :" << it << " at address: " << &it << endl;
    }


    for(auto& it : tm1) {
        cout << "tm1[it] print :" << it << " at address: " << &it << endl;
    }



//--------------------------------------- end  ----------------------------------------------------


//--------------------------------------- end  ----------------------------------------------------
    GoDown();

    Matrix<int, 3, 3> tm3(5);
    cout << "tm3[1] print :" << endl;
    tm3(1,0) = 1;
    tm3(1,1) = 2;
    tm3(1,2) = 3;
    tm3(0) = {7,8,9};
    cout << "this is tm3: " << tm3 << endl;

    for(auto& it : tm3(0)) {
        cout << "tm3[1][it] print :" << it << " at address: " << &it << endl;
    }

    for(typename Matrix<int,3,3>::Iterator it = tm3.begin(); it != tm3.end(); it++) {
        cout << "tm3[it] print :" << *it << " at address: " << &it << endl;
    }

    for(auto& it : tm3) {
        cout << "tm3[it] print :" << it << " at address: " << &it << endl;
    }

//--------------------------------------- end  ----------------------------------------------------

    GoDown();

    Matrix<int, 3, 3> tm4(12);
    cout << "tm4[1] print :" << endl;
    cout << tm4 << endl;

    int temp = 1;
    for(auto& it : tm4(1)) {
        it = temp++;
        cout << it << endl;
    }
    cout << tm4 << endl;

    for(auto& it : tm4) {
        cout << it << " at address: " << &it << endl;
    }
        GoDown();

    for(Matrix<int, 3,3>::Iterator it = tm4.begin(); it != tm4.end(); ++it) {
        cout << *it << " at address: " << &*it << endl;
    }

//--------------------------------------- end  ----------------------------------------------------
    Matrix<int, 3, 3> tm5 = tm4;
    cout << "tm5 == tm4" << (tm5 == tm4 ? " true " : " false ") << endl;



//--------------------------------------- end  ----------------------------------------------------




    return 0;
}









void GoDown()
{
    for(int i = 0; i < 10; ++i)
        cout << endl;
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

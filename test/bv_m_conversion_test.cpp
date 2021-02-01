#include "transforms/b_vector/b_vector.hpp"
#include "transforms/matrix/matrix.hpp"
using namespace bcg;

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "*******************************************" << endl;
    cout << "blacker-cglib/test/bv_m_conversion_test.cpp" << endl;
    cout << "*******************************************" << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test converting b_vector to matrix
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==================================" << endl;
    cout << "test converting b_vector to matrix" << endl;
    cout << "==================================" << endl;
    {
        b_vector<4> obj = { 1, 2, 3, 1 };
        cout << "We set obj = " << obj << endl;
        matrix<4, 1> m_obj = static_cast<matrix<4, 1>>(obj);
        cout << "After convert obj to m_obj:" << endl;
        cout << "m_obj = " << endl << m_obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test converting matrix to b_vector
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==================================" << endl;
    cout << "test converting matrix to b_vector" << endl;
    cout << "==================================" << endl;
    {
        matrix<3, 1> m_obj = { 22, 11, 44 };
        cout << "We set m_obj = " << endl << m_obj << endl;
        b_vector<3> obj = static_cast<b_vector<3>>(m_obj);
        cout << "After convert m_obj to obj:" << endl;
        cout << "obj = " << obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test multiplication
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "===================" << endl;
    cout << "test multiplication" << endl;
    cout << "===================" << endl;
    {
        // transform (x, y, z, 1) to (x+1, y+1, z+1, 1)
        matrix<4> trans = {
            1, 0, 0, 1,
            0, 1, 0, 1,
            0, 0, 1, 1,
            0, 0, 0, 1
        };
        b_vector<4> obj = { 10, 20, 30, 1 };
        b_vector<4> after_obj = static_cast<b_vector<4>>(trans * static_cast<matrix<4, 1>>(obj));
        cout << "after transform (10, 20, 30) with (x+1, y+1, z+1):" << endl;
        cout << "after_obj = " << after_obj << endl;
    }
}
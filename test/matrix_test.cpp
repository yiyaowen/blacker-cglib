#include "transforms/matrix/matrix.hpp"
using namespace bcg;

#include <iostream>
using std::cout;
using std::endl;
#include <string>

int main()
{
    cout << "**********************************" << endl;
    cout << "blacker-cglib/test/matrix_test.cpp" << endl;
    cout << "**********************************" << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test default instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=======================" << endl;
    cout << "test default instructor" << endl;
    cout << "=======================" << endl;
    {
        matrix<3> trans;
        cout << "matrix<3> trans: " << endl << trans << endl;
        matrix<3, 3, double> d_trans;
        cout << "matrix<3, 3, double> d_trans: " << endl << d_trans << endl;
        matrix<2, 4, int> i_trans;
        cout << "matrix<2, 4, int> i_trans: " << endl << i_trans << endl;
        matrix<2, 2, float> f_trans;
        cout << "matrix<2, 2, float> f_trans: " << endl << f_trans << endl;
        matrix<3, 3, std::string> s_trans;
        // Attention: s_trans does not support +, - etc. operators
        cout << "matrix<3, 3, string> s_trans: " << endl << s_trans << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test initializer_list instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "================================" << endl;
    cout << "test initializer_list instructor" << endl;
    cout << "================================" << endl;
    {
        matrix<3> trans = {
            11, 12, 13,
            21, 22, 23,
            31, 32, 33
        };
        cout << "We set matrix<3> trans = {" << endl;
        cout << "11, 12, 13\n21, 22, 23\n31, 32, 33\n}" << endl;
        cout << "and its output<3> is: " << endl << trans << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test std::array instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==========================" << endl;
    cout << "test std::array instructor" << endl;
    cout << "==========================" << endl;
    {
        std::array<double, 3 * 4> t_array = {
            100, 21, 22, 3.43,
            99.1, 31, 32.3, 9.3,
            1, 2, 3, 4.009
        };
        matrix<3, 4> trans(t_array);
        cout << "We set t_array = {" << endl;
        cout << "100, 21, 22, 3.43\n99.1, 31, 32.3, 9.3\n1, 2, 3, 4.009\n}" << endl;
        cout << "and its output<3, 4> is: " << endl << trans << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test native array instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "============================" << endl;
    cout << "test native array instructor" << endl;
    cout << "============================" << endl;
    {
        int i_array[4] = {
            2, 2,
            2, 2
        };
        matrix<4, 1, int> trans(i_array, 4);
        cout << "We set i_array = {" << endl;
        cout << "2, 2\n2, 2\n}" << endl;
        cout << "and its output<4, 1, int> is: " << endl << trans << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test copy instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "====================" << endl;
    cout << "test copy instructor" << endl;
    cout << "====================" << endl;
    {
        matrix<3> trans1 = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        matrix<3> trans2 = trans1;
        trans2[2][2] = 0;
        cout << "After copy trans1 to trans2, and do trans2[2][2] = 0:" << endl;
        cout << "trans1 = " << endl << trans1 << endl;
        cout << "trans2 = " << endl << trans2 << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test trace
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==========" << endl;
    cout << "test trace" << endl;
    cout << "==========" << endl;
    {
        matrix<3> trans = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9
        };
        cout << "matrix<3> trans = " << endl << trans << endl;
        cout << "Its trace = " << trans.trace() << endl;
        matrix<2, 4> ns_trans = {
            2, 2, 33, 1,
            33, 1, 4, 1
        };
        cout << "matrix<2, 4> ns_trans = " << endl << ns_trans << endl;
        cout << "Its trace = " << ns_trans.trace() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test determinant
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "================" << endl;
    cout << "test determinant" << endl;
    cout << "================" << endl;
    {
        matrix<3> trans = {
            3, 1, 5.2,
            2.1, 3, 1,
            3.9, 3, 11
        };
        cout << "matrix<3> trans = " << endl << trans << endl;
        cout << "Its determinant = " << trans.determinant() << endl;
        matrix<2> nsingle_trans = {
            1, 1,
            2, 2
        };
        cout << "matrix<2> non-singular trans = " << endl << nsingle_trans << endl;
        cout << "Its determinant = " << nsingle_trans.determinant() << endl;
        matrix<2, 3> nsquare_trans = {
            1, 1, 1,
            2, 2, 2
        };
        cout << "matrix<2, 3> non-square trans = " << endl << nsquare_trans << endl;
        cout << "Its determinant = " << nsquare_trans.determinant() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test min_elem, max_elem, is_dirty
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=================================" << endl;
    cout << "test min_elem, max_elem, is_dirty" << endl;
    cout << "=================================" << endl;
    {
        matrix<3> trans = {
            22.2, 1, 2,
            99, 12, 94,
            99.9, 1, 3
        };
        cout << "We set trans = " << endl << trans << endl;
        cout << "Here are its properties:" << endl;
        cout << "min_elem = " << trans.min_elem() << ", max_elem = " << trans.max_elem() << endl;
        cout << "is_dirty [should be false] = " << trans.is_dirty() << endl;
        matrix<2> dirty_trans = {
            1, 1,
            3
        };
        cout << "Here is a dirty_trans = " << endl << dirty_trans << endl;
        cout << "invoke is_dirty() [should be true] returns: " << dirty_trans.is_dirty() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test M, A (Minor matrix, cofactor determinant), adjoint
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=======================================================" << endl;
    cout << "test M, A (Minor matrix, cofactor determinant), adjoint" << endl;
    cout << "=======================================================" << endl;
    {
        matrix<4> trans = {
            1, 0, 0, 0,
            1, 1, 0, 0,
            1, 1, 1, 0,
            1, 1, 1, 1
        };
        cout << "We set trans = " << endl << trans << endl;
        cout << "trans.M(2, 2) = " << endl << trans.M(2, 2) << endl;
        cout << "trans.M(1, 2) = " << endl << trans.M(1, 2) << endl;
        cout << "trans.M(0, 0) = " << endl << trans.M(0, 0) << endl;
        cout << "trans.A(1, 1) = " << trans.A(1, 1) << endl;
        cout << "trans.A(0, 2) = " << trans.A(0, 2) << endl;
        cout << "trans.A(2, 0) = " << trans.A(2, 0) << endl;
        cout << "trans.adjoint() = " << endl << trans.adjoint() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test T (Transpose), inverse
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "===========================" << endl;
    cout << "test T (Transpose), inverse" << endl;
    cout << "===========================" << endl;
    {
        matrix<3> trans = {
            1, 0, 0,
            1, 1, 0,
            1, 1, 1,
        };
        cout << "We set trans = " << endl << trans << endl;
        cout << "trans.T = " << endl << trans.T() << endl;
        cout << "trans.adjoint() = " << endl << trans.adjoint() << endl;
        cout << "trans.determinant() = " << trans.determinant() << endl;
        cout << "trans.inverse() = " << endl << trans.inverse() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test access and set operator: [], get and set
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=============================================" << endl;
    cout << "test access and set operator: [], get and set" << endl;
    cout << "=============================================" << endl;
    {
        matrix<3> trans = {
            11, 12, 13,
            21, 22, 23,
            31, 32, 33
        };
        cout << "We set trans = " << endl << trans << endl;
        cout << "trans[0] = " << trans[0] << endl;
        cout << "trans[0][2] = " << trans[0][2] << endl;
        cout << "trans[1][1] = " << trans[1][1] << endl;
        cout << "trans.get_col(2) = " << trans.get_col(2) << endl;
        cout << "trans.get_row(1) = " << trans.get_row(1) << endl;
        cout << "trans.get_cell(1, 2) = " << trans.get_cell(1, 2) << endl;
        trans[0][1] = 99;
        trans.set_cell(1, 2, 9);
        trans[2] = { 1, 1, 1 };
        cout << "Now we do trans[0][1] = 99, trans.set_cell<1, 2>(9), and trans[2] = { 1, 1, 1 }:" << endl;
        cout << "trans = " << endl << trans << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test +, -, *, /, ^ operator
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "===========================" << endl;
    cout << "test +, -, *, /, ^ operator" << endl;
    cout << "===========================" << endl;
    {
        matrix<3> trans1 = {
            1, 0, 0,
            1, 1, 0,
            1, 1, 1
        };
        matrix<3> trans2 = {
            1, 1, 1,
            0, 1, 1,
            0, 0, 1
        };
        cout << "We set trans1 = " << endl << trans1 << endl;
        cout << "and trans2 = " << endl << trans2 << endl;
        cout << "trans1 + trans2 = " << endl << trans1 + trans2 << endl;
        cout << "trans1 - trans2 = " << endl << trans1 - trans2 << endl;
        cout << "trans2 - trans1 = " << endl << trans2 - trans1 << endl;
        cout << "trans1 * trans2 = " << endl << trans1 * trans2 << endl;
        cout << "trans1 / 0.5 = " << endl << trans1 / 0.5 << endl;
        cout << "trans2 * 2 = " << endl << trans2 * 2 << endl;
        cout << "3.0 * trans1 = " << endl << 3.0 * trans1 << endl;
        cout << "trans1^-1 = " << endl << (trans1^-1) << endl;
        cout << "trans1^2 = " << endl << (trans1^2) << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test io
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=======" << endl;
    cout << "test io" << endl;
    cout << "=======" << endl;
    {
        matrix<3> trans = {
            1, 22, 333,
            4444, 55555, 666666,
            7777, 888, 99
        };
        cout << "We set trans = " << endl << trans << endl;
        cout << "trans.print_cell_width() = " << trans.print_cell_width() << endl;
        trans.set_print_cell_width(10);
        cout << "Now we do trans.set_print_cell_width(10), and trans = " << endl << trans << endl;
        cout << "and trans.print_cell_width() = " << trans.print_cell_width() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // test global matrix utils
    //////////////////////////////////////////////////////////////////////////////////////////////////
    cout << "========================" << endl;
    cout << "test global matrix utils" << endl;
    cout << "========================" << endl;
    {
        auto trans1 = make_identity_matrix<3>();
        cout << "auto trans1 = make_identity_matrix<3>(), trans1 = " << endl << trans1 << endl;
        auto trans2 = make_zero_matrix<2>();
        cout << "auto trans2 = make_zero_matrix<2>(), trans2 = " << endl << trans2 << endl;
    }
}
#include "transforms/b_vector/b_vector.hpp"
using namespace bcg;

#include <iostream>
using  std::cout;
using std::endl;

int main()
{
    cout << "*************************************" << endl;
    cout << "blacker-cglib/test/b_vector_test.cpp:" << endl;
    cout << "*************************************" << endl;
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test default instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=======================" << endl;
    cout << "test default instructor" << endl;
    cout << "=======================" << endl;
    {
        b_vector<3> obj;
        cout << "b_vector<3> obj: " << obj << endl;
        b_vector<3, double> d_obj;
        cout << "b_vector<3, double> d_obj: " << d_obj << endl;
        b_vector<2, int> i_obj;
        cout << "b_vector<2, int> i_obj: " << i_obj << endl;
        b_vector<4, float> f_obj;
        cout << "b_vector<4, float> f_obj: " << f_obj << endl;
//        b_vector<3, b_vector<3>> v_obj;
//        cout << "b_vector<3, b_vector<3>> v_obj: " << v_obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test initializer_list instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "================================" << endl;
    cout << "test initializer_list instructor" << endl;
    cout << "================================" << endl;
    {
        b_vector<3> obj = { 3, 3, 2 };
        cout << "b_vector<3> obj = { 3, 3, 2 }: " << obj << endl;
        b_vector<3, double> d_obj { 2.2, 1.2222, 3.3 };
        cout << "b_vector<3, double> d_obj { 2.2, 1.2222, 3.3 }: " << d_obj << endl;
        b_vector<2, int> i_obj = { 9, 999, 100 };
        cout << "b_vector<2, int> i_obj = { 9, 999, 100 }: " << i_obj << endl;
        b_vector<4, float> f_obj { 88.8, 0.01, 0.4 };
        cout << "b_vector<4, float> f_obj { 88.8, 0.01, 0.4 }: " << f_obj << endl;
//        b_vector<3, b_vector<3>> v_obj = { {0,0,0}, {1,1,1}, {2,2,2} };
//        cout << "b_vector<3, b_vector<3>> v_obj = = { {0,0,0}, {1,1,1}, {2,2,2} }: " << v_obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test std::array instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==========================" << endl;
    cout << "test std::array instructor" << endl;
    cout << "==========================" << endl;
    {
        // b_vector<3> obj(std::array<int, 3>{});
        // this statement will result a error, since the default [elem_type] for [b_vector] is [double]
        b_vector<3> obj(std::array<double, 3>{});
        cout << "b_vector<3> obj(std::array<double, 3>{}): " << obj << endl;
        std::array<double, 3> d_arr = { 2.0, 2.0, 33.0 };
        b_vector<3, double> d_obj(d_arr);
        cout << "b_vector<3, double> d_obj(d_arr) where d_arr = { 2.0, 2.0, 33.0 }: " << d_obj << endl;
        b_vector<2, int> i_obj(std::array<int, 2>{});
        cout << "b_vector<2, int> i_obj(std::array<int, 2>{}): " << i_obj << endl;
        b_vector<4, float> f_obj { std::array<float, 4> { 2.0, 0.001, 22.2, 3 } };
        cout << "b_vector<4, float> f_obj { std::array<float, 4> { 2.0, 0.001, 22.2, 3 } }: " << f_obj << endl;
        // b_vector<3, b_vector<3>> v_obj = { std::array<b_vector<3>, 3> {} };
        // this statement will result a error, since explicit constructor will not receive a '= {...}'
//        b_vector<3, b_vector<3>> v_obj { std::array<b_vector<3>, 3> {} };
//        cout << "b_vector<3, b_vector<3>> v_obj { std::array<b_vector<3>, 3> {} }: " << v_obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test native array instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "============================" << endl;
    cout << "test native array instructor" << endl;
    cout << "============================" << endl;
    {
        int n_array[4] = { 1, 2, 3, 4 };
        double d_array[4] = { 1, 2, 3, 4 };
        float f_array[4] = { 1, 2, 3, 4 };
        b_vector<3, double> v_array[4] = { b_vector<3>{}, b_vector<3>{}, b_vector<3>{}, b_vector<3>{} };
        cout << "n_array = { 1, 2, 3, 4 } ; d_array = { 1, 2, 3, 4 } ; f_array = { 1, 2, 3, 4 }" << endl;
        cout << "v_array = { b_vector<3>{}, b_vector<3>{}, b_vector<3>{}, b_vector<3>{} }" << endl;
        // b_vector<3> obj(n_array, 3);
        // this statement will result a error, since native constructor will not receive implicit conversion
        b_vector<3> obj(d_array, 3);
        cout << "b_vector<3> obj(d_array, 3): " << obj << endl;
        b_vector<3, double> d_obj(d_array, 3);
        cout << "b_vector<3, double> d_obj(d_array, 3): " << d_obj << endl;
        b_vector<2, int> i_obj(n_array, 2);
        cout << "b_vector<2, int> i_obj(n_array, 2): " << i_obj << endl;
        b_vector<4, float> f_obj(f_array, 4);
        cout << "b_vector<4, float> f_obj(f_array, 4): " << f_obj << endl;
//        b_vector<3, b_vector<3>> v_obj(v_array, 3);
//        cout << "b_vector<3, b_vector<3>> v_obj(v_array, 3): " << v_obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test copy instructor
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "====================" << endl;
    cout << "test copy instructor" << endl;
    cout << "====================" << endl;
    {
        b_vector<3> obj1 = { 1, 2, 3 };
        b_vector<3> obj2 = obj1;
        obj2[2] = 0;
        cout << "After copy obj1 to obj2, and do obj2[2] = 0:" << endl;
        cout << "obj1 = " << obj1 << endl;
        cout << "obj2 = " << obj2 << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test max_elem, min_elem, magnitude, magnitude2, is_dirty
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "========================================================" << endl;
    cout << "test max_elem, min_elem, magnitude, magnitude2, is_dirty" << endl;
    cout << "========================================================" << endl;
    {
        b_vector<3> obj = { 1, 2, 3, 4 };
        cout << "obj<3, double> = { 1, 2, 3, 4 }" << endl;
        cout << "obj.max_elem = " << obj.max_elem() << ", obj.min_elem = " << obj.min_elem() << endl;
        cout << "obj.magnitude = " << obj.magnitude() << ", obj.magnitude2 = " << obj.magnitude2() << endl;
        b_vector<3, int> i_obj = { 1, 2, 3, 4 };
        cout << "i_obj<3, int> = { 1, 2, 3, 4 }" << endl;
        cout << "i_obj.max_elem = " << i_obj.max_elem() << ", i_obj.min_elem = " << i_obj.min_elem() << endl;
        cout << "i_obj.magnitude = " << i_obj.magnitude() << ", i_obj.magnitude2 = " << i_obj.magnitude2() << endl;
        cout << std::boolalpha << "obj.is_dirty() [should be false] = " << obj.is_dirty() << endl;
        cout << "i_obj.is_dirty() [should be false] = " << i_obj.is_dirty() << endl;
        b_vector<3> dirty_obj = { 1, 2 };
        cout << "dirty_obj<3> = { 1, 2 }" << endl;
        cout << "dirty_obj.is_dirty() [should be true] = " << dirty_obj.is_dirty() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test +, - operator
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==================" << endl;
    cout << "test +, - operator" << endl;
    cout << "==================" << endl;
    {
        b_vector<3> obj = { 2, 3, 4 };
        b_vector<3> obj2 = { 3, 1, 1 };
        cout << "obj = { 2, 3, 4 } ; obj2 = { 3, 1, 1 }" << endl;
        cout << "+obj: " << +obj << endl << "-obj: " << -obj << endl;
        cout << "+obj2: " << +obj2 << endl << "-obj2: " << -obj << endl;
        cout << "obj + obj2 = " << obj + obj2 << endl;
        cout << "obj - obj2 = " << obj - obj2 << endl;
        cout << "obj2 + obj = " << obj2 + obj << endl;
        cout << "obj2 - obj = " << obj2 - obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test scalar multiplication
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==========================" << endl;
    cout << "test scalar multiplication" << endl;
    cout << "==========================" << endl;
    {
        b_vector<3> obj = { 6, 12, 9 };
        cout << "obj = { 6, 12, 9 }" << endl;
        cout << "obj * 2 = " << obj * 2 << endl;
        cout << "3.0 * obj = " << 3.0 * obj << endl;
        cout << "obj / 3 = " << obj / 3 << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test dot product, cross product
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "===============================" << endl;
    cout << "test dot product, cross product" << endl;
    cout << "===============================" << endl;
    {
        b_vector<3> obj = { 4, 8, 3 };
        b_vector<3> obj2 = { 2, 1, 3 };
        cout << "obj = { 4, 8, 3 } ; obj2 = { 2, 1, 3 }" << endl;
        // cout << "obj , obj2 = " << obj , obj2;
        // this statement will not work normally, since [<<] has a higher priority than [,]
        cout << "obj , obj2 = " << (obj , obj2) << endl;
        cout << "obj2 , obj = " << (obj2 , obj) << endl;
        cout << "obj * obj2 = " << obj * obj2 << endl;
        cout << "obj2 * obj = " << obj2 * obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test access and set operator: [], get, set
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==========================================" << endl;
    cout << "test access and set operator: [], get, set" << endl;
    cout << "==========================================" << endl;
    {
        b_vector<3> obj = { 2, 3, 1 };
        cout << "now obj: " << obj << endl;
        cout << "obj[2] = " << obj[2] << ", obj.get<2>() = " << obj.get(2) << endl;
        obj[1] = 999;
        cout << "after obj[1] = 999, obj: " << obj << endl;
        obj.set(1, 100);
        cout << "after obj.set<1>(100), obj: " << obj << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test normalize
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "==============" << endl;
    cout << "test normalize" << endl;
    cout << "==============" << endl;
    {
        b_vector<3> obj = { 2, 3, 1 };
        cout << "now obj: " << obj << endl;
        cout << "obj.magnitude = " << obj.magnitude() << endl;
        obj.normalize();
        cout << "after normalized, obj: " << obj << endl;
        cout << "and now obj.magnitude = " << obj.magnitude() << endl;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    // test io
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "=======" << endl;
    cout << "test io" << endl;
    cout << "=======" << endl;
    {
        b_vector<3> obj_4 = { 111, 3033, 222 };
        cout << "default io for obj_4 = { 111, 3033, 222 }: " << obj_4 << endl;
        obj_4.set_print_cell_width(8);
        cout << "after set print cell width to 8, obj_4: " << obj_4 << endl;
        cout << "now obj_4.print_cell_width returns: " << obj_4.print_cell_width() << endl;
        obj_4.set_print_cell_width(12);
        cout << "after set print cell width to 12, obj_4: " << obj_4 << endl;
    }
}
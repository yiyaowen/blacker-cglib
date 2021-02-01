#include "transforms/translation.hpp"
#include "transforms/point.hpp"
using namespace bcg;

#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "***************************************" << endl;
    cout << "blacker-cglib/test/translation_test.cpp" << endl;
    cout << "***************************************" << endl;

    translation trans = { 1, 2, 3,};
    point p = { 2, 2, 3 };
    cout << "translation is " << trans << endl;
    cout << "point is " << p << endl;
    trans.apply_to(p);
    cout << "after apply translation to point:" << endl;
    cout << "point is " << p << endl;
}
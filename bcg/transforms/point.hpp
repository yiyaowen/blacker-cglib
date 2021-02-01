#ifndef BCG_POINT_HPP
#define BCG_POINT_HPP

#include "transforms/b_vector/b_vector.hpp"

#include <iostream>

namespace bcg
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // point
    //////////////////////////////////////////////////////////////////////////////////////////////////

    class point
    {
    public:
        point(float x, float y, float z);
        ~point() = default;

    public:
        friend std::ostream& operator <<(std::ostream& out, const point& p);

    public:
        inline float x() { return _data[0]; }
        inline void set_x(float new_x) { _data[0] = new_x; }
        inline float y() { return _data[1]; }
        inline void set_y(float new_y) { _data[1] = new_y; }
        inline float z() { return _data[2]; }
        inline void set_z(float new_z) { _data[2] = new_z; }

        inline b_vector<4, float>& data() { return _data; }
        inline const b_vector<4, float>& data() const { return _data; }

    private:
        b_vector<4, float> _data;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // point implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    point::point(float x, float y, float z)
    {
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = 1;
    }

    std::ostream& operator <<(std::ostream& out, const point& p)
    {
        out << p.data();
        return out;
    }
}

#endif // BCG_POINT_HPP

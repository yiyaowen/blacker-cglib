#ifndef BCG_VECTOR_HPP
#define BCG_VECTOR_HPP

#include "transforms/b_vector/b_vector.hpp"

#include <iostream>

namespace bcg
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // vector
    //////////////////////////////////////////////////////////////////////////////////////////////////

    class vector
    {
    public:
        vector(float x, float y, float z);
        ~vector() = default;

    public:
        // magnitude & magnitude^2
        inline float magnitude() { return _data.magnitude(); }
        inline float magnitude2() { return _data.magnitude2(); }

        // normalization
        inline void normalize() { _data.normalize(); }

        friend std::ostream& operator <<(std::ostream& out, const vector& v);

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
    // vector implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    vector::vector(float x, float y, float z){
        _data[0] = x;
        _data[1] = y;
        _data[2] = z;
        _data[3] = 0;
    }

    std::ostream& operator <<(std::ostream& out, const vector& v)
    {
        out << v.data();
        return out;
    }
}

#endif // BCG_VECTOR_HPP
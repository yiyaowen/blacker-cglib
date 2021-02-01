#ifndef BCG_TRANSLATION_HPP
#define BCG_TRANSLATION_HPP

#include "transforms/matrix/matrix.hpp"
#include "transforms/point.hpp"

#include <cmath>
#include <iostream>

namespace bcg
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // translation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    class translation
    {
    public:
        translation(float dx, float dy, float dz);

        ~translation() = default;

    public:
        float distance();

        void apply_to(point& p) const;

        friend std::ostream& operator<<(std::ostream& out, const translation& trans);

    public:
        float dx() const;

        void set_dx(float new_dx);

        float dy() const;

        void set_dy(float new_dy);

        float dz() const;

        void set_dz(float new_dz);

    private:
        matrix<4, 4, float> _trans = make_identity_matrix<4, float>();

        bool _is_distance_updated = false;
        float _distance = {};
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // translation implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    translation::translation(float dx, float dy, float dz)
    {
        _trans[0][3] = dx;
        _trans[1][3] = dy;
        _trans[2][3] = dz;
    }

    float translation::distance()
    {
        if (_is_distance_updated) return _distance;

        _is_distance_updated = true;

        return (_distance = std::sqrt(
            _trans[0][3] * _trans[0][3] +
            _trans[1][3] * _trans[1][3] +
            _trans[2][3] * _trans[2][3]));
    }

    void translation::apply_to(point& p) const
    {
        matrix<4, 1, float> obj = static_cast<matrix<4, 1, float>>(p.data());
        p.data() = static_cast<b_vector<4, float>>(_trans * obj);
    }

    std::ostream& operator<<(std::ostream& out, const translation& trans)
    {
        out << "{ dx: " << trans.dx() << " dy: " << trans.dy() << " dz: " << trans.dz() << " }";
        return out;
    }

    float translation::dx() const
    {
        return _trans[0][3];
    }

    void translation::set_dx(float new_dx)
    {
        _trans[0][3] = new_dx;
        _is_distance_updated = false;
    }

    float translation::dy() const
    {
        return _trans[1][3];
    }

    void translation::set_dy(float new_dy)
    {
        _trans[1][3] = new_dy;
        _is_distance_updated = false;
    }

    float translation::dz() const
    {
        return _trans[2][3];
    }

    void translation::set_dz(float new_dz)
    {
        _trans[2][3] = new_dz;
        _is_distance_updated = false;
    }
}

#endif // BCG_TRANSLATION_HPP
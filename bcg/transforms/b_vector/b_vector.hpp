#ifndef BCG_B_VECTOR_HPP
#define BCG_B_VECTOR_HPP

#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <ostream>

namespace bcg {

    // forward declarations
    template<size_t row_count, size_t col_count, typename elem_type>
    class matrix;

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // b_vector (prefix 'b_' means 'blacker')
    //////////////////////////////////////////////////////////////////////////////////////////////////

    template<size_t dim, typename elem_type=double>
    class b_vector
    {
    public:
        b_vector(); // zero vector
        b_vector(std::initializer_list<elem_type> elems);
        explicit b_vector(std::array<elem_type, dim> elems);
        b_vector(elem_type* elems, size_t elem_count);
        b_vector(const b_vector<dim, elem_type>& v);
        ~b_vector() = default;

        // conversion between matrix and column vector
        explicit b_vector(const matrix<dim, 1, elem_type>& m);
        explicit operator matrix<dim, 1, elem_type>();

    public:
        const elem_type& min_elem() const;
        const elem_type& max_elem() const;
        elem_type magnitude() const;
        elem_type magnitude2() const; // magnitude^2

        // addition and subtraction
        b_vector<dim, elem_type> operator +(const b_vector<dim, elem_type>& r_vector) const;
        b_vector<dim, elem_type> operator -(const b_vector<dim, elem_type>& r_vector) const;
        b_vector<dim, elem_type> operator +() const;
        b_vector<dim, elem_type> operator -() const;

        // scalar multiplication
        b_vector<dim, elem_type> operator *(const elem_type& lambda) const;
        // TODO: Fix error while using "3 * b_vector<3>", i.e. b_vector's elem_type is [double], and lambda's type is [int]
        template<size_t _dim, typename _elem_type>
        friend b_vector<_dim, _elem_type> operator *(const _elem_type& lambda, const b_vector<_dim, _elem_type>& self);

        b_vector<dim, elem_type> operator /(const elem_type& lambda) const;

        // dot product (use comma instead)
        elem_type operator ,(const b_vector<dim, elem_type>& r_vector) const;
        // cross product
        b_vector<dim, elem_type> operator *(const b_vector<dim, elem_type>& r_vector) const;

        elem_type& operator [](size_t idx);
        const elem_type& operator [](size_t idx) const;

        template<size_t _dim, typename _elem_type>
        friend std::ostream& operator <<(std::ostream& out, const b_vector<_dim, _elem_type>& self);

    public:
        int print_cell_width() const;
        void set_print_cell_width(int cell_w);

        void set(size_t d_idx, const elem_type& value);
        const elem_type& get(size_t d_idx) const;

        bool is_dirty() const;

    private:
        bool _is_dirty = false;
        std::array<elem_type, dim> _elems;

        mutable bool _is_magnitude_updated = false;
        mutable elem_type _magnitude2 = {}; // magnitude^2

        mutable bool _is_min_elem_updated = false;
        mutable elem_type _min_elem = {};
        mutable bool _is_max_elem_updated = false;
        mutable elem_type _max_elem = {};

        int _print_cell_width = 6;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // b_vector implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO: How to invoke another instructor in this situation?
    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector()
    {
        elem_type def_value = {};
        for (size_t i = 0; i < dim; ++i) {
            _elems[i] = def_value;
        }
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector(std::initializer_list<elem_type> elems)
    {
        size_t i = 0;
        for (auto p_elem = elems.begin(); i < dim && p_elem != elems.end(); ++i, ++p_elem) {
            _elems[i] = *p_elem;
        }
        _is_dirty = (i != dim);
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector(std::array<elem_type, dim> elems)
    {
        _elems = elems;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector(elem_type *elems, size_t elem_count)
    {
        size_t i;
        for (i = 0; i < dim && i < elem_count; ++i) {
            _elems[i] = elems[i];
        }
        _is_dirty = (i != dim);
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector(const b_vector& v)
    {
        _is_dirty = v._is_dirty;
        _elems = v._elems;
        _is_magnitude_updated = v._is_magnitude_updated;
        _magnitude2 = v._magnitude2;
        _is_min_elem_updated = v._is_min_elem_updated;
        _min_elem = v._min_elem;
        _is_max_elem_updated = v._is_max_elem_updated;
        _max_elem = v._max_elem;
        _print_cell_width = v._print_cell_width;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::b_vector(const matrix<dim, 1, elem_type>& m)
    {
        (*this) = m.get_col(0);
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type>::operator matrix<dim, 1, elem_type>()
    {
        matrix<dim, 1, elem_type> m { _elems };
        return m;
    }

    template<size_t dim, typename elem_type>
    const elem_type& b_vector<dim, elem_type>::min_elem() const
    {
        if (_is_min_elem_updated) return _min_elem;
        return _min_elem = (*std::min_element(_elems.begin(), _elems.end()));
    }

    template<size_t dim, typename elem_type>
    const elem_type& b_vector<dim, elem_type>::max_elem() const
    {
        if (_is_max_elem_updated) return _max_elem;
        return _max_elem = (*std::max_element(_elems.begin(), _elems.end()));
    }

    template<size_t dim, typename elem_type>
    elem_type b_vector<dim, elem_type>::magnitude() const
    {
        return std::sqrt(magnitude2());
    }

    template<size_t dim, typename elem_type>
    elem_type b_vector<dim, elem_type>::magnitude2() const
    {
        if (_is_magnitude_updated) return _magnitude2;

        _magnitude2 = {};
        for (auto elem : _elems) {
            _magnitude2 = _magnitude2 + (elem * elem);
        }
        _is_magnitude_updated = true;
        return _magnitude2;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator +(const b_vector<dim, elem_type>& r_vector) const
    {
        b_vector<dim, elem_type> sum_vector;
        for (size_t i = 0; i < dim; ++i) {
            sum_vector[i] = _elems[i] + r_vector[i];
        }
        return sum_vector;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator -(const b_vector<dim, elem_type>& r_vector) const
    {
        return *this + (-r_vector);
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator +() const
    {
        return *this;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator -() const
    {
        b_vector<dim, elem_type> opposite_vector;
        for (size_t i = 0; i < dim; ++i) {
            opposite_vector[i] = -_elems[i];
        }
        return opposite_vector;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator *(const elem_type& lambda) const
    {
        b_vector<dim, elem_type> l_vector;
        for (size_t i = 0; i < dim; ++i) {
            l_vector[i] = lambda * _elems[i];
        }
        return l_vector;
    }

    template<size_t _dim, typename _elem_type>
    b_vector<_dim, _elem_type> operator *(const _elem_type& lambda, const b_vector<_dim, _elem_type>& self)
    {
        return self * lambda;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator /(const elem_type& lambda) const
    {
        return (*this) * (1 / lambda);
    }

    template<size_t dim, typename elem_type>
    elem_type b_vector<dim, elem_type>::operator ,(const b_vector<dim, elem_type>& r_vector) const
    {
        elem_type dot_p = {};
        for (size_t i = 0; i < dim; ++i) {
            dot_p = dot_p + _elems[i] * r_vector[i];
        }
        return dot_p;
    }

    template<size_t dim, typename elem_type>
    b_vector<dim, elem_type> b_vector<dim, elem_type>::operator *(const b_vector<dim, elem_type>& r_vector) const
    {
        b_vector<dim, elem_type> cross_vector;
        if (dim == 3) {
            cross_vector[0] = _elems[1] * r_vector[2] - _elems[2] * r_vector[1];
            cross_vector[1] = _elems[2] * r_vector[0] - _elems[0] * r_vector[2];
            cross_vector[2] = _elems[0] * r_vector[1] - _elems[1] * r_vector[0];
        }
        return cross_vector;
    }

    template<size_t dim, typename elem_type>
    elem_type& b_vector<dim, elem_type>::operator[](size_t idx)
    {
        if (idx >= dim) {
            return _elems[dim - 1];
        }
        _is_magnitude_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        return _elems[idx];
    }

    template<size_t dim, typename elem_type>
    const elem_type& b_vector<dim, elem_type>::operator [](size_t idx) const
    {
        if (idx >= dim) {
            return _elems[dim - 1];
        }
        return _elems[idx];
    }

    template<size_t _dim, typename _elem_type>
    std::ostream& operator <<(std::ostream& out, const b_vector<_dim, _elem_type>& self)
    {
        // TODO: This output should be handled as an unitary [<<]
        // For example: b_vector<3> A = { b_vector<3>{}, b_vector<3>{}, b_vector<3>{} }
        // Should be: [[     0,     0,     0,],[     0,     0,     0,],[     0,     0,     0,]]
        // Rather than: [     [     0,     0,     0,],     [     0,     0,     0,],     [     0,     0,     0,]]
        out << "[";
        for (size_t i = 0; i < _dim - 1; ++i) {
            out << std::setw(self.print_cell_width()) << self[i] << ",";
        }
        out << std::setw(self.print_cell_width()) << self[_dim - 1] << "]";
        return out;
    }

    template<size_t dim, typename elem_type>
    int b_vector<dim, elem_type>::print_cell_width() const
    {
        return _print_cell_width;
    }

    template<size_t dim, typename elem_type>
    void b_vector<dim, elem_type>::set_print_cell_width(int cell_w)
    {
        _print_cell_width = cell_w;
    }

    template<size_t dim, typename elem_type>
    void b_vector<dim, elem_type>::set(size_t d_idx, const elem_type& value)
    {
        if (d_idx >= dim) return;
        _is_magnitude_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        _elems[d_idx] = value;
    }

    template<size_t dim, typename elem_type>
    const elem_type& b_vector<dim, elem_type>::get(size_t d_idx) const
    {
        if (d_idx >= dim) {
            _elems[d_idx];
        }
        return _elems[d_idx];
    }

    template<size_t dim, typename elem_type>
    bool b_vector<dim, elem_type>::is_dirty() const
    {
        return _is_dirty;
    }

}

#endif // BCG_B_VECTOR_HPP

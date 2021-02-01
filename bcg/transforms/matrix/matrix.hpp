#ifndef BCG_MATRIX_HPP
#define BCG_MATRIX_HPP

#include "transforms/b_vector/b_vector.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>

namespace bcg
{
    //////////////////////////////////////////////////////////////////////////////////////////////////
    // matrix
    //////////////////////////////////////////////////////////////////////////////////////////////////

    template<size_t row_count, size_t col_count=row_count, typename elem_type=double>
    class matrix
    {
    public:
        matrix(); // zero matrix
        matrix(std::initializer_list<elem_type> elems);
        explicit matrix(std::array<elem_type, row_count * col_count> elems);
        matrix(elem_type* elems, size_t elem_count);
        matrix(const matrix<row_count, col_count, elem_type>& m);
        ~matrix() = default;

    public:
        // addition & subtraction
        matrix<row_count, col_count, elem_type>
            operator +(const matrix<row_count, col_count, elem_type>& r_matrix) const;
        matrix<row_count, col_count, elem_type>
            operator -(const matrix<row_count, col_count, elem_type>& r_matrix) const;
        matrix<row_count, col_count, elem_type> operator +() const;
        matrix<row_count, col_count, elem_type> operator -() const;

        // scalar multiplication
        matrix<row_count, col_count, elem_type> operator *(const elem_type& lambda) const;
        matrix<row_count, col_count, elem_type> operator /(const elem_type& lambda) const;

        // TODO: Fix error while using "3 * matrix<3>", i.e. matrix's elem_type is [double], and lambda'type is [int]
        template<size_t _row_count, size_t _col_count, typename _elem_type>
        friend matrix<_row_count, _col_count, _elem_type>
            operator *(const _elem_type& lambda, const matrix<_row_count, _col_count, _elem_type>& self);

        // matrix multiplication
        template<size_t r_col_count>
        matrix<row_count, r_col_count, elem_type> operator *
            (const matrix<col_count, r_col_count, elem_type>& r_matrix) const;

        matrix<row_count, col_count, elem_type> operator ^(int power) const;

        // access operator
        b_vector<col_count, elem_type>& operator [](size_t row_idx);
        const b_vector<col_count, elem_type>& operator [](size_t row_idx) const;

        // transpose
        matrix<col_count, row_count, elem_type> transpose() const;
        matrix<col_count, row_count, elem_type> T() const;

        // inverse
        matrix<row_count, col_count, elem_type> inverse() const;

        // minor matrix
        matrix<row_count-1, col_count-1, elem_type> minor_matrix(size_t row_idx, size_t col_idx) const;
        matrix<row_count-1, col_count-1, elem_type> M(size_t row_idx, size_t col_idx) const;

        // adjoint
        matrix<col_count, row_count, elem_type> adjoint() const;

        // min & max values
        const elem_type& min_elem() const;
        const elem_type& max_elem() const;

        // trace
        elem_type trace() const;

        // determinant
        elem_type determinant() const;

        // cofactor expansion
        elem_type cofactor(size_t row_idx, size_t col_idx) const;
        elem_type A(size_t row_idx, size_t col_idx) const;

        // output format
        template<size_t __row_count, size_t __col_count, typename _elem_type>
        friend std::ostream& operator <<
            (std::ostream& out, const matrix<__row_count, __col_count, _elem_type>& self);

    public:
        size_t print_cell_width() const;
        void set_print_cell_width(int cell_w);

        void set_row(size_t row_idx, const b_vector<col_count, elem_type>& row);
        void set_col(size_t col_idx, const b_vector<row_count, elem_type>& col);
        void set_cell(size_t row_idx, size_t col_idx, const elem_type& value);
        const b_vector<col_count, elem_type>& get_row(size_t row_idx) const;
        b_vector<row_count, elem_type> get_col(size_t col_idx) const;
        const elem_type& get_cell(size_t row_idx, size_t col_idx) const;

        bool is_dirty() const;

    private:
        bool _is_dirty = false;
        size_t _total_elem_count = {};
        bool _is_square = false;
        std::array<b_vector<col_count, elem_type>, row_count> _rows;

        mutable bool _is_min_elem_updated = false;
        mutable elem_type _min_elem = {};
        mutable bool _is_max_elem_updated = false;
        mutable elem_type _max_elem = {};

        mutable bool _is_trace_updated = false;
        mutable elem_type _trace = {};
        mutable bool _is_determinant_updated = false;
        mutable elem_type _determinant = {};

        int _print_cell_width = 6;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // global matrix utils
    //////////////////////////////////////////////////////////////////////////////////////////////////

    template<size_t row_count, size_t col_count=row_count, typename elem_type=double>
    matrix<row_count, col_count, elem_type> make_zero_matrix()
    {
        matrix<row_count, col_count, elem_type> zero_matrix;
        return zero_matrix;
    }

    template<size_t order, typename elem_type=double>
    matrix<order, order, elem_type> make_identity_matrix()
    {
        matrix<order, order, elem_type> e_matrix;
        for (size_t i = 0; i < order; ++i) {
            e_matrix[i][i] = 1;
        }
        return e_matrix;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////
    // matrix implementation
    //////////////////////////////////////////////////////////////////////////////////////////////////

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>::matrix()
    {
        _is_square = (row_count == col_count);
        _total_elem_count = row_count * col_count;

        elem_type zero = {};
        for (size_t i = 0; i < row_count; ++i) {
            for (size_t j = 0; j < col_count; ++j) {
                _rows[i][j] = zero;
            }
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>::matrix(std::initializer_list<elem_type> elems)
    {
        _is_square = (row_count == col_count);
        _total_elem_count = row_count * col_count;

        size_t i = 0;
        for (auto p_elem = elems.begin(); i < _total_elem_count && p_elem != elems.end(); ++i, ++p_elem)
        {
            _rows[i / col_count][i % col_count] = *p_elem;
        }

        _is_dirty = (i != _total_elem_count);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>::matrix(std::array<elem_type, row_count * col_count> elems)
    {
        _is_square = (row_count == col_count);
        _total_elem_count = row_count * col_count;

        for (size_t i = 0; i < row_count; ++i) {
            for (size_t j = 0; j < col_count; ++j) {
                _rows[i][j] = elems[i * col_count + j];
            }
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>::matrix(elem_type* elems, size_t elem_count)
    {
        _total_elem_count = row_count * col_count;
        _is_dirty = (elem_count < _total_elem_count);
        _is_square = (row_count == col_count);

        size_t tmp_count = 0;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            for (size_t col_idx = 0; col_idx < col_count; ++col_idx) {
                _rows[row_idx][col_idx] = elems[row_idx * col_count + col_idx];
                if (++tmp_count >= _total_elem_count) return;
            }
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>::matrix(const matrix<row_count, col_count, elem_type>& m)
    {
        _is_dirty = m._is_dirty;
        _total_elem_count = m._total_elem_count;
        _is_square = m._is_square;
        _rows = m._rows;
        _is_min_elem_updated = m._is_min_elem_updated;
        _min_elem = m._min_elem;
        _is_max_elem_updated = m._is_max_elem_updated;
        _max_elem = m._max_elem;
        _is_trace_updated = m._is_trace_updated;
        _trace = m._trace;
        _is_determinant_updated = m._is_determinant_updated;
        _determinant = m._determinant;
        _print_cell_width = m._print_cell_width;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    const elem_type& matrix<row_count, col_count, elem_type>::min_elem() const
    {
        if (_is_min_elem_updated) return _min_elem;

        _is_min_elem_updated = true;

        std::array<elem_type, row_count> row_min_elems;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            row_min_elems[row_idx] = _rows[row_idx].min_elem();
        }
        return _min_elem = (*std::min_element(row_min_elems.begin(), row_min_elems.end()));
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    const elem_type& matrix<row_count, col_count, elem_type>::max_elem() const
    {
        if (_is_max_elem_updated) return _max_elem;

        _is_max_elem_updated = true;

        std::array<elem_type, row_count> row_max_elems;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            row_max_elems[row_idx] = _rows[row_idx].max_elem();
        }
        return _max_elem = (*std::max_element(row_max_elems.begin(), row_max_elems.end()));
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    elem_type matrix<row_count, col_count, elem_type>::trace() const
    {
        if (!_is_square) {
            elem_type def_value = {};
            return def_value;
        }

        if (_is_trace_updated) return _trace;

        _is_trace_updated = true;

        _trace = {};
        for (size_t i = 0; i < row_count; ++i) {
            _trace += _rows[i][i];
        }

        return _trace;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    elem_type matrix<row_count, col_count, elem_type>::determinant() const
    {
        if (!_is_square) {
            elem_type def_value = {};
            return def_value;
        }

        if (_is_determinant_updated) return _determinant;

        _is_determinant_updated = true;

        switch (row_count)
        {
            case 0:
            {
                elem_type def_value = {};
                return def_value;
            }
            case 1:
                return (_determinant = _rows[0][0]);

            case 2:
                return (_determinant = _rows[0][0] * _rows[1][1] - _rows[0][1] * _rows[1][0]);

            case 3:
                return (_determinant =
                    _rows[0][0] * _rows[1][1] * _rows[2][2] +
                    _rows[0][1] * _rows[1][2] * _rows[2][0] +
                    _rows[1][0] * _rows[2][1] * _rows[0][2] -
                    _rows[0][2] * _rows[1][1] * _rows[2][0] -
                    _rows[0][1] * _rows[1][0] * _rows[2][2] -
                    _rows[0][0] * _rows[1][2] * _rows[2][1]);

            default:
            {
                // TODO: How to calculate determinant of high order matrix efficiently here?
                _determinant = {};
//                // expand in first column
//                for (size_t i = 0; i < row_count; ++i) {
//                    _determinant = _determinant + _rows[i][0] * A(i, 0);
//                }
                return _determinant;
            }
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>
    matrix<row_count, col_count, elem_type>::operator +
    (const matrix<row_count, col_count, elem_type>& r_matrix) const
    {
        matrix<row_count, col_count, elem_type> sum_matrix;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            sum_matrix[row_idx] = _rows[row_idx] + r_matrix[row_idx];
        }
        return sum_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>
    matrix<row_count, col_count, elem_type>::operator -
    (const matrix<row_count, col_count, elem_type>& r_matrix) const
    {
        return (*this)+(-r_matrix);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type> matrix<row_count, col_count, elem_type>::operator +() const
    {
        return (*this);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>matrix<row_count, col_count, elem_type>::operator -() const
    {
        matrix<row_count, col_count, elem_type> op_matrix;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            op_matrix[row_idx] = -_rows[row_idx];
        }
        return op_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>
    matrix<row_count, col_count, elem_type>::operator *(const elem_type& lambda) const
    {
        matrix<row_count, col_count, elem_type> l_matrix;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            for (size_t col_idx = 0; col_idx < col_count; ++col_idx) {
                l_matrix[row_idx][col_idx] = lambda * _rows[row_idx][col_idx];
            }
        }
        return l_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type>
    matrix<row_count, col_count, elem_type>::operator /(const elem_type& lambda) const
    {
        return (*this) * (1 / lambda);
    }

    template<size_t _row_count, size_t _col_count, typename _elem_type>
    matrix<_row_count, _col_count, _elem_type>
    operator *(const _elem_type& lambda, const matrix<_row_count, _col_count, _elem_type>& self)
    {
        return self * lambda;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    template<size_t r_col_count>
    matrix<row_count, r_col_count, elem_type>
    matrix<row_count, col_count, elem_type>::operator *(const matrix<col_count, r_col_count, elem_type>& r_matrix) const
    {
        matrix<row_count, r_col_count, elem_type> prod_matrix;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            for (size_t col_idx = 0; col_idx < r_col_count; ++col_idx) {
                elem_type tmp_elem = {};
                for (size_t i = 0; i < col_count; ++i) {
                    tmp_elem = tmp_elem + _rows[row_idx][i] * r_matrix[i][col_idx];
                }
                prod_matrix[row_idx][col_idx] = tmp_elem;
            }
        }
        return prod_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type> matrix<row_count, col_count, elem_type>::operator ^(int power) const
    {
        if (!_is_square) {
            return (*this);
        }
        matrix<row_count, col_count, elem_type> base_matrix = make_identity_matrix<row_count, elem_type>();
        matrix<row_count, col_count, elem_type> i_matrix = power > 0 ? (*this) : inverse();
        for (int i = 0; i < power; ++i) {
            base_matrix = base_matrix * i_matrix;
        }
        return base_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    b_vector<col_count, elem_type>& matrix<row_count, col_count, elem_type>::operator [](size_t row_idx)
    {
        _is_determinant_updated = _is_trace_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        return _rows[row_idx];
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    const b_vector<col_count, elem_type>&
    matrix<row_count, col_count, elem_type>::operator [](size_t row_idx) const
    {
        return _rows[row_idx];
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<col_count, row_count, elem_type> matrix<row_count, col_count, elem_type>::transpose() const
    {
        matrix<col_count, row_count, elem_type> t_matrix;
        for (size_t i = 0; i < row_count; ++i) {
            for (size_t j = 0; j < col_count; ++j) {
                t_matrix[j][i] = _rows[i][j];
            }
        }
        return t_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<col_count, row_count, elem_type> matrix<row_count, col_count, elem_type>::T() const
    {
        return transpose();
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count, col_count, elem_type> matrix<row_count, col_count, elem_type>::inverse() const
    {
        return adjoint() / determinant();
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count-1, col_count-1, elem_type>
    matrix<row_count, col_count, elem_type>::minor_matrix(size_t row_idx, size_t col_idx) const
    {
        matrix<row_count-1, col_count-1, elem_type> m_matrix;
        for (size_t i = 0; i < row_idx; ++i) {
            for (size_t j = 0; j < col_idx; ++j) {
                m_matrix[i][j] = _rows[i][j];
            }
        }
        for (size_t i = 0; i < row_idx; ++i) {
            for (size_t j = col_idx+1; j < col_count; ++j) {
                m_matrix[i][j-1] = _rows[i][j];
            }
        }
        for (size_t i = row_idx+1; i < row_count; ++i) {
            for (size_t j = 0; j < col_idx; ++j) {
                m_matrix[i-1][j] = _rows[i][j];
            }
        }
        for (size_t i = row_idx+1; i < row_count; ++i) {
            for (size_t j = col_idx+1; j < col_count; ++j) {
                m_matrix[i-1][j-1] = _rows[i][j];
            }
        }
        return m_matrix;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<row_count-1, col_count-1, elem_type>
    matrix<row_count, col_count, elem_type>::M(size_t row_idx, size_t col_idx) const
    {
        return minor_matrix(row_idx, col_idx);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    elem_type matrix<row_count, col_count, elem_type>::cofactor(size_t row_idx, size_t col_idx) const
    {
        return M(row_idx, col_idx).determinant() * ((row_idx + col_idx) % 2 == 0 ? 1 : -1);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    elem_type matrix<row_count, col_count, elem_type>::A(size_t row_idx, size_t col_idx) const
    {
        return cofactor(row_idx, col_idx);
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    matrix<col_count, row_count, elem_type> matrix<row_count, col_count, elem_type>::adjoint() const
    {
        matrix<col_count, row_count, elem_type> a_matrix;
        for (size_t i = 0; i < col_count; ++i) {
            for (size_t j = 0; j < row_count; ++j) {
                a_matrix[i][j] = A(j, i);
            }
        }
        return a_matrix;
    }

    template<size_t __row_count, size_t __col_count, typename _elem_type>
    std::ostream& operator <<(std::ostream& out, const matrix<__row_count, __col_count, _elem_type>& self)
    {
        for (size_t row_idx = 0; row_idx < __row_count - 1; ++row_idx) {
            out << self[row_idx] << std::endl;
        }
        out << self[__row_count - 1];
        return out;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    size_t matrix<row_count, col_count, elem_type>::print_cell_width() const
    {
        return _print_cell_width;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    void matrix<row_count, col_count, elem_type>::set_print_cell_width(int cell_w)
    {
        _print_cell_width = cell_w;
        for (size_t row_idx = 0; row_idx < row_count; ++row_idx) {
            _rows[row_idx].set_print_cell_width(cell_w);
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    void matrix<row_count, col_count, elem_type>::set_row(size_t row_idx, const b_vector<col_count, elem_type>& row)
    {
        _is_determinant_updated = _is_trace_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        _rows[row_idx] = row;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    void matrix<row_count, col_count, elem_type>::set_col(size_t col_idx, const b_vector<row_count, elem_type>& col)
    {
        _is_determinant_updated = _is_trace_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        for (size_t i = 0; i < row_count; ++i) {
            _rows[i][col_idx] = col[i];
        }
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    void matrix<row_count, col_count, elem_type>::set_cell(size_t row_idx, size_t col_idx, const elem_type& value)
    {
        _is_determinant_updated = _is_trace_updated = false;
        _is_min_elem_updated = _is_max_elem_updated = false;
        _rows[row_idx][col_idx] = value;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    const b_vector<col_count, elem_type>& matrix<row_count, col_count, elem_type>::get_row(size_t row_idx) const
    {
        return _rows[row_idx];
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    b_vector<row_count, elem_type> matrix<row_count, col_count, elem_type>::get_col(size_t col_idx) const
    {
        b_vector<row_count, elem_type> c_vector;
        for (size_t i = 0; i < row_count; ++i) {
            c_vector[i] = _rows[i][col_idx];
        }
        return c_vector;
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    const elem_type& matrix<row_count, col_count, elem_type>::get_cell(size_t row_idx, size_t col_idx) const
    {
        return _rows[row_idx][col_idx];
    }

    template<size_t row_count, size_t col_count, typename elem_type>
    bool matrix<row_count, col_count, elem_type>::is_dirty() const
    {
        return _is_dirty;
    }

}

#endif // BCG_MATRIX_HPP
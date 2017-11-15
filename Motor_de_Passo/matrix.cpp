#include "matrix.h"


adrone::matrix::matrix() : _rows(0), _cols(0)
{ }


adrone::matrix::matrix(const uint8_t &rows, const uint8_t &cols)
{
    create_matrix(rows, cols);
}


adrone::matrix::matrix(const uint8_t &rows, const uint8_t &cols, const double &element)
{
    create_matrix(rows, cols);
    set_values(element);
}


adrone::matrix::matrix(const adrone::matrix &other)
{
    create_matrix(other._rows, other._cols);

    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] = other._matrix[i][j];
}


adrone::matrix& adrone::matrix::operator=(const adrone::matrix &other)
{
    if (this != &other)
    {
        if ((_rows != other._rows) || (_cols != other._cols))
        {
            delete_matrix();
            create_matrix(other._rows, other._cols);
        }

        for(uint8_t i = 0; i < _rows; ++i)
            for(uint8_t j = 0; j < _cols; ++j)
                _matrix[i][j] = other._matrix[i][j];
    }

    return *this;
}


adrone::matrix::~matrix()
{
    delete_matrix();
}


double& adrone::matrix::operator()(const uint8_t &row, const uint8_t &col)
{
    return _matrix[row][col];
}


const double& adrone::matrix::operator()(const uint8_t &row, const uint8_t &col) const
{
    return _matrix[row][col];
}


void adrone::matrix::set_values(const double &element)
{
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] = element;
}


void adrone::matrix::set_values(int num, ...)
{
    va_list valist;
    // initialize valist for num number of arguments
    va_start(valist, num);
    // access all the arguments assigned to valist
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] = va_arg(valist, double);

    // clean memory reserved for valist *
    va_end(valist);
}


uint8_t adrone::matrix::get_num_rows() const
{
    return _rows;
}


uint8_t adrone::matrix::get_num_cols() const
{
    return _cols;
}


void adrone::matrix::swap_rows(const uint8_t &from, const uint8_t &to)
{
    double *tempRow = _matrix[from];
    _matrix[from]   = _matrix[to];
    _matrix[to]     = tempRow;
}


void adrone::matrix::swap_cols(const uint8_t &from, const uint8_t &to)
{
    for (uint8_t i = 0; i < _rows; ++i)
    {
        double tempCol   = _matrix[i][from];
        _matrix[i][from] = _matrix[i][to];
        _matrix[i][to]   = tempCol;
    }
}


adrone::matrix& adrone::matrix::operator+=(const double &rhs)
{
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] += rhs;

    return *this;
}


adrone::matrix& adrone::matrix::operator+=(const adrone::matrix &rhs)
{
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] += rhs._matrix[i][j];

    return *this;
}


adrone::matrix& adrone::matrix::operator-=(const double &rhs)
{
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] -= rhs;

    return *this;
}


adrone::matrix& adrone::matrix::operator-=(const adrone::matrix &rhs)
{
    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < _cols; ++j)
            _matrix[i][j] -= rhs._matrix[i][j];

    return *this;
}


adrone::matrix& adrone::matrix::operator*=(const double &rhs)
{
   for(uint8_t i = 0; i < _rows; ++i)
       for(uint8_t j = 0; j < _cols; ++j)
           _matrix[i][j] *= rhs;

    return *this;
}


adrone::matrix& adrone::matrix::operator*=(const adrone::matrix &rhs)
{
    //assert (!(_cols == rhs._rows) && "Wrong dimension!");

    adrone::matrix result(_rows, rhs._cols);

    for(uint8_t i = 0; i < _rows; ++i)
        for(uint8_t j = 0; j < rhs._cols; ++j)
            for(uint8_t k = 0; k < _cols; ++k)
                result(i,j) += _matrix[i][k] * rhs._matrix[k][j];

    (*this) = result;
    return *this;
}


/*adrone::matrix& adrone::matrix::operator/=(const double &rhs)
{
   for(uint8_t i = 0; i < _rows; ++i)
       for(uint8_t j = 0; j < _cols; ++j)
           _matrix[i][j] /= rhs;

    return *this;
}*/


adrone::matrix adrone::matrix::operator~()
{
    adrone::matrix result(_cols, _rows);

    for(uint8_t i = 0; i < _rows; ++i)
        for (uint8_t j = 0; j < _cols; ++j)
            result(j,i) = _matrix[i][j];

    return result;
}


adrone::matrix adrone::matrix::operator^(const int8_t &rhs)
{
    adrone::matrix result(_rows, _cols);
    
    if (_rows == 1 && _cols == 1 && rhs == -1)
    {
        result(0,0) = 1 / _matrix[0][0];
    }
    else if (_rows == 2 && _cols == 2 && rhs == -1)
    {
        double det = (_matrix[0][0] * _matrix[1][1]) - (_matrix[0][1] * _matrix[1][0]);

        result(0,0)  = _matrix[1][1] / det;
        result(0,1) -= _matrix[0][1] / det;
        result(1,0) -= _matrix[1][0] / det;
        result(1,1)  = _matrix[0][0] / det;
    }

    return result;
}


void adrone::matrix::create_matrix(const uint8_t &rows, const uint8_t &cols)
{
    _rows = rows;
    _cols = cols;

    _matrix = new double*[_rows];

    for(uint8_t i = 0; i < _rows; ++i)
        _matrix[i] = new double[_cols]();
}


void adrone::matrix::delete_matrix()
{
    for(uint8_t i = 0; i < _rows; ++i)
        delete[] _matrix[i];

    if (_cols != 0)
        delete[] _matrix;

    _rows = 0;
    _cols = 0;
}
#ifndef ADRONE_MATRIX_H
#define ADRONE_MATRIX_H

#include <stdint.h>  // uint8_t; uint16_t; 
#include <stdbool.h> // bool
#include <stdarg.h>


namespace adrone {

    class matrix
    {
    public:
        // constructor
        matrix();
        matrix(const uint8_t &rows, const uint8_t &cols);
        matrix(const uint8_t &rows, const uint8_t &cols, const double &element);

        // copy & move constructor
        matrix(const matrix &other);
        //matrix(const matrix &&other) = delete;

        // copy & move assignment operator
        matrix& operator=(const matrix &other);
        //matrix& operator=(const matrix &&other) = delete;

        // destructor
        ~matrix();

        // access the individual elements
        double& operator()(const uint8_t &row, const uint8_t &col);
        const double& operator()(const uint8_t &row, const uint8_t &col) const;

        // define matrix values
        void set_values(const double &element);
        void set_values(int num, ...);

        // get the number of rows & columns
        uint8_t get_num_rows() const;
        uint8_t get_num_cols() const;

        // swap rows and columns
        void swap_rows(const uint8_t &from, const uint8_t &to);
        void swap_cols(const uint8_t &from, const uint8_t &to);

        // matrix operations
        matrix& operator+=(const double &rhs);
        matrix& operator+=(const matrix &rhs);
        matrix& operator-=(const double &rhs);
        matrix& operator-=(const matrix &rhs);
        matrix& operator*=(const double &rhs);
        matrix& operator*=(const matrix &rhs);
        //matrix& operator/=(const double &rhs);

        // transposed
        matrix operator~();

        // inverse
        matrix operator^(const int8_t &rhs);

        // A + cte
        friend matrix operator+(matrix lhs, const double &rhs) { return lhs += rhs; }
        // cte + A
        friend matrix operator+(const double &lhs, matrix rhs) { return rhs += lhs; }
        // A + B
        friend matrix operator+(matrix lhs, const matrix &rhs) { return lhs += rhs; }
        // A - cte
        friend matrix operator-(matrix lhs, const double &rhs) { return lhs -= rhs; }
        // cte - A
        friend matrix operator-(const double &lhs, matrix rhs) { return rhs -= lhs; }
        // A - B
        friend matrix operator-(matrix lhs, const matrix &rhs) { return lhs -= rhs; }
        // A * cte
        friend matrix operator*(matrix lhs, const double &rhs) { return lhs *= rhs; }
        // cte * A
        friend matrix operator*(const double &lhs, matrix rhs) { return rhs *= lhs; }
        // A * B
        friend matrix operator*(matrix lhs, const matrix &rhs) { return lhs *= rhs; }
    
    private:
        uint8_t _rows;
        uint8_t _cols;
        double **_matrix;

        void create_matrix(const uint8_t &rows, const uint8_t &cols);
        void delete_matrix();
    };

}

/*
// A / cte
//matrix operator/(matrix lhs, const double &rhs) { return lhs /= rhs; }
// cte / A
//template<typename Ta, typename Tb>
//matrix<Ta> operator/(const Tb &lhs, matrix<Ta> rhs) { return rhs /= lhs; }
*/




#endif

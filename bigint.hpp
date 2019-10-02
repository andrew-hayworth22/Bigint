/**
 * Michael Hayworth
 * bigint.hpp
 * CS 23001
 */

/**
 * Bigint Header:
 * Defines methods and functions for bigint.
 */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

const int CAPACITY = 400;

class bigint {
    public:
        bigint();
        bigint(int);
        bigint(char[]);
        
        int valueAt(int) const;
        void set(int, int);
        void debugPrint(std::ostream&) const;
        bool operator==(const bigint&) const;

        bigint operator+(const bigint&) const;
        int operator[](int) const;

        bigint timesDigit(int) const;
        bigint times10(int) const;
        bigint operator*(const bigint&) const;
    ;

    private:
        int num[CAPACITY];
    ;
};

std::ostream& operator<<(std::ostream&, const bigint&);
std::istream& operator>>(std::istream&, bigint&);

#endif

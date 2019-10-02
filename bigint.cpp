/**
 * Michael Hayworth
 * bigint.hpp
 * CS 23001
 */

/**
 * Bigint Implementation:
 * Defines methods and functions for bigint.
 */

#include "bigint.hpp"

//Default Constructor
bigint::bigint() {
    for(int i = 0; i < CAPACITY; ++i) {
        num[i] = 0;
    }
}

//Integer Constructor: creates bigint out of an int.
//REQUIRES: nnum 400 digits or less.
bigint::bigint(int nnum) {
    for(int i = 0; i < CAPACITY; ++i) {
        num[i] = nnum % 10;
        nnum /= 10;
    }
}

//Character Array Constructor: creates bigint out of an array of chars.
//REQUIRES: nnum has 400 elements or less.
bigint::bigint(char nnum[]) {
    for(int i = 0; i < CAPACITY; ++i) {
        num[i] = 0;
    }

    int arrayLength = 0;

    while(nnum[arrayLength] != 0) {
        ++arrayLength;
    }

    int j = arrayLength - 1;

    for(int i = 0; i < arrayLength; ++i) {
        num[i] = nnum[j] - '0';
        j--;
    }
}

//ValueAt: returns value of bigint at a certain digit(index).
//REQUIRES: 0 <= index < 400
int bigint::valueAt(int index) const {
    return num[index];
}

//Set: sets the value(value) of bigint at a certain digit(index).
//REQUIRES: 0 <= index < 400, 0 <= value <= 9
void bigint::set(int index, int value) {
    num[index] = value;
}

//DebugPrint: prints every value of the bigint; used for debugging.
void bigint::debugPrint(std::ostream& out) const {
    for(int i = CAPACITY - 1; i >= 0; --i) {
        out << num[i] << " | ";
    }
}

//IsEqual Overload: allows us to logically compare bigints with ==.
bool bigint::operator==(const bigint& rhs) const {
    for(int i = 0; i < CAPACITY; ++i) {
        if(num[i] != rhs.valueAt(i)) {
            return false;
        }
    }
    return true;
}

//Addition Overload: allows the addition of bigints using the + operator.
//REQUIRES: The sum of the bigints must have >= 400 digits.
bigint bigint::operator+(const bigint& rhs) const {
    bigint result = bigint();
    int newDigit = 0;

    for (int i = 0; i < CAPACITY - 1; ++i) {
        newDigit = num[i] + rhs.num[i];

        result.num[i] += newDigit;
        newDigit = result.num[i];
        if(result.num[i] >= 10) {
            result.num[i] %= 10;
            result.num[i + 1] += newDigit / 10;
        }
    }

    return result;
}

//Bracket Overload: returns integer at a bigint's index(index).
//REQUIRES: 0 <= index < CAPACITY.
int bigint::operator[](int index) const {
    return num[index];
}

//Times Digit: returns this bigint multiplied by an integer(0-9).
//REQUIRES: 0 <= m <= 9.
bigint bigint::timesDigit(int m) const {
    bigint result = bigint();

    int temp;
    for(int i = 0; i < CAPACITY - 1; ++i) {
        temp = result.num[i] + (num[i] * m);

        if(temp >= 10) {
            result.num[i] = temp % 10;
            result.num[i + 1] = temp / 10;
        }
        else {
            result.num[i] = temp;
        }
    }

    return result;
}

//Times 10: returns this bigint times 10^n.
//REQUIRES: 0 <= n.
bigint bigint::times10(int n) const {
    bigint result = bigint();
    int j = 0;

    for(int i = n; i < CAPACITY; ++i) {
        result.num[i] = num[j];
        ++j;
    }

    return result;
}

//Multiply Overload: allows the multiplication of two bigints via *.
bigint bigint::operator*(const bigint& rhs) const {
    bigint result = bigint();
    bigint temp = bigint();

    for(int i = 0; i < CAPACITY; ++i) {
        temp = timesDigit(rhs.num[i]);
        result = result + temp.times10(i);
    }
    
    return result;
}

//Output Overload: prints a clean, readable verson of bigint.
std::ostream& operator<<(std::ostream& out, const bigint& print) {
    bool isNum = false;
    int printedInLine = 0;

    for(int i = CAPACITY - 1; i >= 1; --i) {
        if(print.valueAt(i) != 0)
            isNum = true;
        if(isNum) {
            out << print.valueAt(i);
            ++printedInLine;
        }
        if(printedInLine >= 80) {
            out << std::endl;
            printedInLine = 0;
        }
    }
    out << print.valueAt(0);

    return out;
}

//Input Overload: reads in a bigint from a stream; ends read at ';'.
std::istream& operator>>(std::istream& in, bigint& read) {
    read = bigint();

    bigint flip = bigint();
    int index = 0;
    char digit;
    in >> digit;

    while(digit != ';' && !in.eof()) {
        flip.set(index, (digit - '0'));
        ++index;
        in >> digit;
    }
    
    int k = index - 1;
    for(int i = 0; i < index; ++i) {
        read.set(i, flip[k]);
        --k;
    }

    return in;
}
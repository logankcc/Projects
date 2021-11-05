/*
File: fractionCalculator.cpp
Author: Logan Copeland
Description: Fraction class implementation file
*/

#include "fractionCalculator.h"

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

Fraction::Fraction() {
    num = 0;
    denom = 1;
}

Fraction::Fraction(int num) {
    this->num = num;
    denom = 1;
}

Fraction::Fraction(int num, int denom) {
    // throw exception if fraction is undefined
    if (denom == 0) {
        throw FractionException("Undefined!");
    }

    // simplify fraction
    if (num == 0) {
        this->num = 0;
        this->denom = 1;
    }
    else {
        int factor = gcd(num, denom);
        this->num = num / factor;
        this->denom = denom / factor;
    }

    // handle negative integers
    if (((this->num < 0) && (this->denom < 0)) || (denom < 0)) {
        this->num *= -1;
        this->denom *= -1;
    }
}

int Fraction::numerator() const {
    return num;
}

int Fraction::denominator() const {
    return denom;
}

int Fraction::gcd(int x, int y) {
    if (x == 0) {
        return 1;
    }

    if (x < 0) {
        x *= -1;
    }

    if (y < 0) {
        y *= -1;
    }

    if ((y <= x) && (x % y == 0)) {
        return y;
    } else if (x < y) {
        return gcd(y, x);
    } else {
        return gcd(y, (x % y));
    }
}

Fraction &Fraction::operator+=(const Fraction &right) {
    if (denominator() == right.denominator()) {
        num += right.numerator();
    } else {
        num = numerator() * right.denominator() + right.numerator() * denominator();
        denom = denominator() * right.denominator();
    }

    int factor = gcd(num, denom);
    num = num / factor;
    denom = denom / factor;
    return *this;
}

Fraction &Fraction::operator++() {
    num += denom;
    return *this;
}

Fraction Fraction::operator++(int unused) {
    Fraction clone(num, denom);
    num += denom;
    return clone;
}

bool digitCheck(string input) {
    if (input[0] == '\0') {
        return false;
    }
    
    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

ostream &operator<<(ostream &out, const Fraction &fraction) {
    out << fraction.numerator() << "/" << fraction.denominator();
    return out;
}

istream &operator>>(istream &in, Fraction &fraction) {
    string input;
    in.clear();
    in >> input;
    size_t found = input.find('/');

    // handle '/' input case
    if (found != string::npos) {
        string numString = input.substr(0, (found));
        string denomString = input.substr((found + 1), input.length());

    // check if input contains only digits zero to nine inclusive
        if (digitCheck(numString) && digitCheck(denomString)) {
            // convert string to integer
            Fraction fractionReturn(stoi(numString), stoi(denomString));
            fraction = fractionReturn;
        } else {
            throw FractionException("Invalid input!");
        }
    // handle integer input case
    } else {
        // check if input contains only digits zero to nine inclusive
        if (digitCheck(input)) {
            // convert string to integer
            Fraction fractionReturn(stoi(input));
            fraction = fractionReturn;
        } else {
            throw FractionException("Invalid input!");
        }
    }

    return in;
}

Fraction operator+(const Fraction &left, const Fraction &right) {
    if (left.denominator() == right.denominator()) {
        return Fraction(left.numerator() + right.numerator(), left.denominator());
    } else {
        return Fraction((left.numerator() * right.denominator() + right.numerator() * left.denominator()), (left.denominator() * right.denominator()));
    }
}

Fraction operator-(const Fraction &left, const Fraction &right) {
    if (left.denominator() == right.denominator()) {
        return Fraction(left.numerator() - right.numerator(), left.denominator());
    } else {
        return Fraction((left.numerator() * right.denominator() - right.numerator() * left.denominator()), (left.denominator() * right.denominator()));
    }
}

Fraction operator*(const Fraction &left, const Fraction &right) {
    return Fraction((left.numerator() * right.numerator()), (left.denominator() * right.denominator()));
}

Fraction operator/(const Fraction &left, const Fraction &right) {
    return Fraction((left.numerator() * right.denominator()), (left.denominator() * right.numerator()));
}

Fraction operator-(const Fraction &fraction) {
    return Fraction(((-1) * fraction.numerator()), (fraction.denominator()));
}

bool operator==(const Fraction &left, const Fraction &right) {
    if ((left.numerator() == right.numerator()) && (left.denominator() == right.denominator())) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const Fraction &left, const Fraction &right) {
    if ((left.numerator() != right.numerator()) || (left.denominator() != right.denominator())) {
        return true;
    } else {
        return false;
    }
}

bool operator<(const Fraction &left, const Fraction &right) {
    double leftFraction = (double)left.numerator() / (double)left.denominator();
    double rightFraction = (double)right.numerator() / (double)right.denominator();

    if (leftFraction < rightFraction) {
        return true;
    } else {
        return false;
    }
}

bool operator<=(const Fraction &left, const Fraction &right) {
    double leftFraction = (double)left.numerator() / (double)left.denominator();
    double rightFraction = (double)right.numerator() / (double)right.denominator();

    if (leftFraction <= rightFraction) {
        return true;
    } else {
        return false;
    }
}

bool operator>(const Fraction &left, const Fraction &right) {
    double leftFraction = (double)left.numerator() / (double)left.denominator();
    double rightFraction = (double)right.numerator() / (double)right.denominator();

    if (leftFraction > rightFraction) {
        return true;
    } else {
        return false;
    }
}

bool operator>=(const Fraction &left, const Fraction &right) {
    double leftFraction = (double)left.numerator() / (double)left.denominator();
    double rightFraction = (double)right.numerator() / (double)right.denominator();

    if (leftFraction >= rightFraction) {
        return true;
    } else {
        return false;
    }
}

FractionException::FractionException(const string &message) {
    errorMessage = message;
}

string FractionException::what() const
{
    return errorMessage;
}
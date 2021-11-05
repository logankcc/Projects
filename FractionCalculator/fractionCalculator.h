/*
File: fractionCalculator.h
Author: Logan Copeland
Description: Fraction class header file
*/

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Fraction {
public:
    Fraction(); // default constructor
    Fraction(int num); // constructor
    Fraction(int num, int denom); // constructor
    int numerator() const; // num getter
    int denominator() const; // denom getter

    // unary operators:

    Fraction &operator+=(const Fraction &right); // += operator overloading
    Fraction &operator++(); // ++ (pre-increment) operator overloading
    Fraction operator++(int unused); // ++ (post-increment) operator overloading

private:
    int num; // numerator
    int denom; // denominator
    int gcd(int num, int denom); // greatest common divisor method
};

// function that checks if a string only contains digits zero to nine inclusive
bool digitCheck(string input);

// binary operators:

ostream &operator<<(ostream &out, const Fraction &fraction); // << operator overloading
istream &operator>>(istream &in, Fraction &fraction); // >> operator overloading

Fraction operator+(const Fraction &left, const Fraction &right); // + operator overloading
Fraction operator-(const Fraction &left, const Fraction &right); // - (subtraction) operator overloading
Fraction operator*(const Fraction &left, const Fraction &right); // * operator overloading
Fraction operator/(const Fraction &left, const Fraction &right); // / operator overloading
Fraction operator-(const Fraction &fraction); // - (negation) operator overloading

bool operator==(const Fraction &left, const Fraction &right); // == operator overloading
bool operator!=(const Fraction &left, const Fraction &right); // != operator overloading
bool operator<(const Fraction &left, const Fraction &right); // < operator overloading
bool operator<=(const Fraction &left, const Fraction &right); // <= operator overloading
bool operator>(const Fraction &left, const Fraction &right); // > operator overloading
bool operator>=(const Fraction &left, const Fraction &right); // >= operator overloading

class FractionException {
public:
    FractionException(const string &message); // constructor
    string what() const; // error message return method

private:
    string errorMessage; // error message
};
#pragma once

#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

#include <util/constants.h>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
private:
    int num;
    int den;
    void Reduce();

public:
    Rational();
    Rational(int numerator);
    Rational(int numerator, int denominator);

    int GetNumerator() const;
    int GetDenominator() const;

    void SetNumerator(int numerator);
    void SetDenominator(int denominator);

    friend std::istream& operator>>(std::istream& in, Rational& fraction);
    friend std::ostream& operator<<(std::ostream& out, Rational fraction);

    const Rational& operator=(const Rational& other);

    const Rational operator+(const Rational& other);
    const Rational operator-(const Rational& other);
    const Rational operator/(const Rational& other);
    const Rational operator*(const Rational& other);

    const Rational& operator+=(const Rational& other);
    const Rational& operator-=(const Rational& other);
    const Rational& operator/=(const Rational& other);
    const Rational& operator*=(const Rational& other);

    const Rational operator+();
    const Rational operator-();

    const Rational& operator--();
    const Rational& operator++();

    const Rational operator--(int);
    const Rational operator++(int);

    bool operator<(const Rational& other);
    bool operator==(const Rational& other);
    bool operator!=(const Rational& other);
    bool operator>=(const Rational& other);
    bool operator>(const Rational& other);
    bool operator<=(const Rational& other);
};

#endif  // RATIONAL_RATIONAL_H

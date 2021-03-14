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
    Rational();               //  NOLINT
    Rational(int numerator);  //  NOLINT
    Rational(int numerator, int denominator);
    Rational(const Rational& other);

    int GetNumerator() const;
    int GetDenominator() const;

    void SetNumerator(int numerator);
    void SetDenominator(int denominator);

    friend std::istream& operator>>(std::istream& in, Rational& fraction);
    friend std::ostream& operator<<(std::ostream& out, const Rational& fraction);

    Rational operator+(const Rational& other) const;
    Rational operator-(const Rational& other) const;
    Rational operator/(const Rational& other) const;
    Rational operator*(const Rational& other) const;

    const Rational& operator=(const Rational& other);

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator/=(const Rational& other);
    Rational& operator*=(const Rational& other);

    Rational operator+();
    Rational operator-();

    Rational& operator--();
    Rational& operator++();

    Rational operator--(int);
    Rational operator++(int);

    bool operator<(const Rational& other) const;
    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;
    bool operator>=(const Rational& other) const;
    bool operator>(const Rational& other) const;
    bool operator<=(const Rational& other) const;
    bool operator>(int num, const Rational& other) const;
};

#endif  // RATIONAL_RATIONAL_H

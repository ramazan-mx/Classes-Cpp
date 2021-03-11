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
    Rational(int x);
    Rational(int x, int y);

    int GetNumerator() const;
    int GetDenominator() const;
    void SetNumerator(int x);
    void SetDenominator(int x);

    friend std::istream& operator>>(std::istream& is, Rational& fraction);
    friend std::ostream& operator<<(std::ostream& out, Rational& fraction);

    const Rational operator+(Rational& other);
    const Rational operator-(Rational& other);
    const Rational operator/(Rational& other);
    const Rational operator*(Rational& other);

    const Rational& operator+=(const Rational& other);
    const Rational& operator-=(const Rational& other);
    const Rational& operator/=(const Rational& other);
    const Rational& operator*=(const Rational& other);

    const Rational operator+();
    const Rational operator-();

    const Rational operator--();
    const Rational operator++();

    bool operator<(const Rational& x) const;
    bool operator==(const Rational& x) const;
    bool operator!=(const Rational& x) const;
    bool operator>=(const Rational& x) const;
    bool operator>(const Rational& x) const;
    bool operator<=(const Rational& x) const;
};

#endif  // RATIONAL_RATIONAL_H

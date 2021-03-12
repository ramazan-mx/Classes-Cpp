#include <iostream>
#include <numeric>
#include <stdlib.h>
#include "rational.h"

int GCD(int u, int v) {
    while (v) {
        u %= v;
        std::swap(u, v);
    }
    return u;
}

void Rational::Reduce() {
    int gcd = GCD(abs(num), abs(den));
    if (den < 0) {
        den *= -1;
        num *= -1;
    }
    num /= gcd;
    den /= gcd;
}

Rational::Rational() : num(0), den(1) {
}

Rational::Rational(int numerator) : num(numerator), den(1) {  // NOLINT
}

Rational::Rational(int numerator, int denominator) {
    if (denominator == 0) {
        throw RationalDivisionByZero{};
    }
    num = numerator;
    den = denominator;
    Reduce();
}

std::istream& operator>>(std::istream& in, Rational& fraction) {
    const int MaxStringSize = 32;
    char str[MaxStringSize];
    in >> str;
    int i = 0;
    int x = 0;
    int mod = 1;
    if (str[0] == '-') {
        mod = -1;
        ++i;
    } else if (str[0] == '+') {
        ++i;
    }
    for (; i < MaxStringSize && str[i] >= '0' && str[i] <= '9'; ++i) {
        x *= 10;
        x += str[i] - '0';
    }
    fraction.num = (x * mod);
    if (str[i] != 0) {
        ++i;
        x = 0;
        mod = 1;
        if (str[i] == '-') {
            mod = -1;
            ++i;
        } else if (str[i] == '+') {
            ++i;
        }
        for (; i < MaxStringSize && str[i] >= '0' && str[i] <= '9'; ++i) {
            x *= 10;
            x += str[i] - '0';
        }
        fraction.den = (x * mod);
    } else {
        fraction.SetDenominator(1);
    }
    fraction.Reduce();
    return in;
}

std::ostream& operator<<(std::ostream& out, Rational fraction) {
    if (fraction.GetDenominator() == 1) {
        out << fraction.GetNumerator();
    } else {
        out << fraction.GetNumerator() << "/" << fraction.GetDenominator();
    }
    return out;
}

int Rational::GetNumerator() const {
    return num;
}

int Rational::GetDenominator() const {
    return den;
}

void Rational::SetNumerator(int numerator) {
    num = numerator;
    Reduce();
}

void Rational::SetDenominator(int denominator) {
    den = denominator;
    Reduce();
}

const Rational& Rational::operator+=(const Rational& other) {
    num = (GetNumerator() * other.GetDenominator()) + (other.GetNumerator() * GetDenominator());
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

const Rational& Rational::operator-=(const Rational& other) {
    num = (GetNumerator() * other.GetDenominator()) - (other.GetNumerator() * GetDenominator());
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

const Rational& Rational::operator/=(const Rational& other) {
    if (other.num == 0) {
        throw RationalDivisionByZero();  //  NOLINT
    }
    num = GetNumerator() * other.GetDenominator();
    den = GetDenominator() * other.GetNumerator();
    Reduce();
    return *this;
}

const Rational& Rational::operator*=(const Rational& other) {
    num = GetNumerator() * other.GetNumerator();
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

const Rational Rational::operator+(const Rational& other) {
    Rational copy = *this;
    copy += other;
    return copy;
}

const Rational Rational::operator-(const Rational& other) {
    Rational copy = *this;
    copy -= other;
    return copy;
}

const Rational Rational::operator/(const Rational& other) {
    Rational copy = *this;
    copy /= other;
    return copy;
}

const Rational Rational::operator*(const Rational& other) {
    Rational copy = *this;
    copy *= other;
    return copy;
}

const Rational Rational::operator+() {
    return *this;
}

const Rational Rational::operator-() {
    Rational temp(-GetNumerator(), GetDenominator());
    return temp;
}

const Rational Rational::operator--(int) {
    Reduce();
    Rational temp = *this;
    SetNumerator(num - den);
    return temp;
}

const Rational Rational::operator++(int) {
    Reduce();
    Rational temp = *this;
    SetNumerator(num + den);
    return temp;
}

const Rational& Rational::operator--() {
    SetNumerator(num - den);
    return *this;
}

const Rational& Rational::operator++() {
    SetNumerator(num + den);
    return *this;
}

bool Rational::operator<(const Rational& other) {
    return (num * other.den < den * other.num);
}

bool Rational::operator==(const Rational& other) {
    return (num * other.den == den * other.num);
}

bool Rational::operator!=(const Rational& other) {
    return !operator==(other);
}

bool Rational::operator>=(const Rational& other) {
    return !operator<(other);
}

bool Rational::operator>(const Rational& other) {
    return (operator>=(other) && operator!=(other));
}

bool Rational::operator<=(const Rational& other) {
    return (operator<(other) || operator==(other));
}
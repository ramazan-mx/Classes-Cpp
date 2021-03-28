#include <iostream>
#include <exception>
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
    if (den_ == 0) {
        throw RationalDivisionByZero{};
    }
    int gcd = GCD(abs(num_), abs(den_));
    if (den_ < 0) {
        den_ *= -1;
        num_ *= -1;
    }
    num_ /= gcd;
    den_ /= gcd;
}

Rational::Rational() : num_(0), den_(1) {  //  NOLINT
}

Rational::Rational(int numerator) : num_(numerator), den_(1) {  // NOLINT
}

Rational::Rational(int numerator, int denominator) {  //  NOLINT
    if (denominator == 0) {
        throw RationalDivisionByZero{};
    }
    num_ = numerator;
    den_ = denominator;
    Reduce();
}

Rational::Rational(const Rational& other) {
    num_ = other.num_;
    den_ = other.den_;
    Reduce();
}

std::istream& operator>>(std::istream& in, Rational& fraction) {
    const int MaxStringSize = 32;
    char str[MaxStringSize];
    in >> str;
    int i = 0;
    int read_number = 0;
    int mod = 1;
    if (str[0] == '-') {
        mod = -1;
        ++i;
    } else if (str[0] == '+') {
        ++i;
    }
    for (; str[i] >= '0' && str[i] <= '9'; ++i) {
        read_number *= 10;
        read_number += str[i] - '0';
    }
    fraction.num_ = (read_number * mod);
    if (str[i] != '\0') {
        ++i;
        read_number = 0;
        mod = 1;
        if (str[i] == '-') {
            mod = -1;
            ++i;
        } else if (str[i] == '+') {
            ++i;
        }
        for (; str[i] >= '0' && str[i] <= '9'; ++i) {
            read_number *= 10;
            read_number += str[i] - '0';
        }
        fraction.den_ = (read_number * mod);
    } else {
        fraction.SetDenominator(1);
    }
    fraction.Reduce();
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& fraction) {
    if (fraction.GetDenominator() == 1) {
        out << fraction.GetNumerator();
    } else {
        out << fraction.GetNumerator() << "/" << fraction.GetDenominator();
    }
    return out;
}

int Rational::GetNumerator() const {
    return num_;
}

int Rational::GetDenominator() const {
    return den_;
}

void Rational::SetNumerator(int numerator) {
    num_ = numerator;
    Reduce();
}

void Rational::SetDenominator(int denominator) {
    den_ = denominator;
    Reduce();
}

const Rational& Rational::operator=(const Rational& other) {
    num_ = other.num_;
    den_ = other.den_;
    Reduce();
    return *this;
}

Rational& Rational::operator+=(const Rational& other) {
    num_ = (GetNumerator() * other.GetDenominator()) + (other.GetNumerator() * GetDenominator());
    den_ = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    num_ = (GetNumerator() * other.GetDenominator()) - (other.GetNumerator() * GetDenominator());
    den_ = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    Rational temp;
    temp.SetNumerator(GetNumerator() * other.GetDenominator());
    temp.SetDenominator(GetDenominator() * other.GetNumerator());
    temp.Reduce();
    *this = temp;
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    num_ = GetNumerator() * other.GetNumerator();
    den_ = GetDenominator() * other.GetDenominator();
    Reduce();
    return *this;
}

Rational Rational::operator+(const Rational& other) const {
    Rational copy = *this;
    copy += other;
    return copy;
}

Rational Rational::operator-(const Rational& other) const {
    Rational copy = *this;
    copy -= other;
    return copy;
}

Rational Rational::operator/(const Rational& other) const {
    Rational copy = *this;
    copy /= other;
    return copy;
}

Rational Rational::operator*(const Rational& other) const {
    Rational copy = *this;
    copy *= other;
    return copy;
}

Rational Rational::operator+() {
    return *this;
}

Rational Rational::operator-() {
    Rational temp(-GetNumerator(), GetDenominator());
    return temp;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    SetNumerator(num_ - den_);
    return temp;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    SetNumerator(num_ + den_);
    return temp;
}

Rational& Rational::operator--() {
    SetNumerator(num_ - den_);
    return *this;
}

Rational& Rational::operator++() {
    SetNumerator(num_ + den_);
    return *this;
}

bool Rational::operator<(const Rational& other) const {
    return (((*this) - other).GetNumerator() < 0);
}

bool Rational::operator==(const Rational& other) const {
    return ((num_ == other.num_) && (den_ == other.den_));
}

bool Rational::operator!=(const Rational& other) const {
    return !operator==(other);
}

bool Rational::operator>=(const Rational& other) const {
    return !operator<(other);
}

bool Rational::operator>(const Rational& other) const {
    return (operator>=(other) && operator!=(other));
}

bool Rational::operator<=(const Rational& other) const {
    return (operator<(other) || operator==(other));
}

bool operator>(int num, const Rational& other) {
    return (num * other.GetDenominator() > other.GetNumerator());
}
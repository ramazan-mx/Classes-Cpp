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
    if (den == 0) {
        throw RationalDivisionByZero{};
    }
    int gcd = GCD(abs(num), abs(den));
    if (den < 0) {
        den *= -1;
        num *= -1;
    }
    num /= gcd;
    den /= gcd;
}

Rational::Rational() : num(0), den(1) {  //  NOLINT
}

Rational::Rational(int numerator) : num(numerator), den(1) {  // NOLINT
}

Rational::Rational(int numerator, int denominator) {  //  NOLINT
    if (denominator == 0) {
        throw RationalDivisionByZero{};
    }
    num = numerator;
    den = denominator;
    Reduce();
}

Rational::Rational(const Rational& other) {
    num = other.num;
    den = other.den;
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
    for (; str[i] >= '0' && str[i] <= '9'; ++i) {
        x *= 10;
        x += str[i] - '0';
    }
    fraction.num = (x * mod);
    if (str[i] != '\0') {
        ++i;
        x = 0;
        mod = 1;
        if (str[i] == '-') {
            mod = -1;
            ++i;
        } else if (str[i] == '+') {
            ++i;
        }
        for (; str[i] >= '0' && str[i] <= '9'; ++i) {
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

std::ostream& operator<<(std::ostream& out, const Rational& fraction) {
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

const Rational& Rational::operator=(const Rational& other) {
    std::cerr << "= Was " << num << " " << den << " Other " << other.num << " " << other.den << "\n";
    num = other.num;
    den = other.den;
    Reduce();
    std::cerr << "Became " << num << " " << den << "\n";
    return *this;
}

Rational& Rational::operator+=(const Rational& other) {
    std::cerr << "+= Was " << num << " " << den << " Other " << other.num << " " << other.den << "\n";
    num = (GetNumerator() * other.GetDenominator()) + (other.GetNumerator() * GetDenominator());
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    std::cerr << "Became " << num << " " << den << "\n";
    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    std::cerr << "-= Was " << num << " " << den << " Other " << other.num << " " << other.den << "\n";
    num = (GetNumerator() * other.GetDenominator()) - (other.GetNumerator() * GetDenominator());
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    std::cerr << "Became " << num << " " << den << "\n";
    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    std::cerr << "/= Was " << num << " " << den << " Other " << other.num << " " << other.den << "\n";
    num = GetNumerator() * other.GetDenominator();
    den = GetDenominator() * other.GetNumerator();
    Reduce();
    std::cerr << "Became " << num << " " << den << "\n";
    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    std::cerr << "*= Was " << num << " " << den << " Other " << other.num << " " << other.den << "\n";
    num = GetNumerator() * other.GetNumerator();
    den = GetDenominator() * other.GetDenominator();
    Reduce();
    std::cerr << "Became " << num << " " << den << "\n";
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
    SetNumerator(num - den);
    return temp;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    SetNumerator(num + den);
    return temp;
}

Rational& Rational::operator--() {
    SetNumerator(num - den);
    return *this;
}

Rational& Rational::operator++() {
    SetNumerator(num + den);
    return *this;
}

bool Rational::operator<(const Rational& other) const {
    return (((*this) - other).GetNumerator() < 0);
}

bool Rational::operator==(const Rational& other) const {
    return ((num == other.num) && (den == other.den));
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
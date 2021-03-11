#include <iostream>
#include <numeric>
#include <stdlib.h>
#include "rational.h"

int GCD(int u, int v) {
    if (u < v) {
        std::swap(u, v);
    }
    while (v) {
        u %= v;
        std::swap(u, v);
    }
    return u;
}

void Rational::Reduce() {
    int gcd = GCD(num, den);
    if (den < 0) {
        den *= -1;
        num *= -1;
    }
    num /= gcd;
    den /= gcd;
}

Rational::Rational() : num(0), den(1) {}

Rational::Rational(int other) : num(other), den(1) {}

Rational::Rational(int x, int y) {
    if (y == 0) {
        throw RationalDivisionByZero{};
    }
    num = x,
            den = y;
    Reduce();
}

std::istream& operator>>(std::istream& is, Rational& fraction) {
    int num, den;
    char delimiter;
    is >> num >> delimiter >> den;
    fraction.SetNumerator(num);
    fraction.SetDenominator(den);
    return is;
}

std::ostream& operator<<(std::ostream& out, Rational& fraction) {
    if (fraction.GetDenominator() == 1) {
        out << fraction.GetNumerator();
    } else {
        out << fraction.GetNumerator() << " / " << fraction.GetDenominator();
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
    this->SetNumerator(num * other.den + other.num * den);
    this->SetDenominator(den * other.den);
    Reduce();
    return *this;
}

const Rational& Rational::operator-=(const Rational& other) {
    this->SetNumerator(num * other.den - other.num * den);
    this->SetDenominator(den * other.den);
    Reduce();
    return *this;
};

const Rational& Rational::operator/=(const Rational& other) {
    this->SetNumerator(num * other.den);
    this->SetDenominator(den * other.num);
    Reduce();
    return *this;
};

const Rational& Rational::operator*=(const Rational& other) {
    this->SetNumerator(num * other.num);
    this->SetDenominator(den * other.den);
    Reduce();
    return *this;
}

const Rational Rational::operator+(Rational& other) {
    Rational copy = *this;
    return copy += other;
}

const Rational Rational::operator-(Rational& other) {
    Rational copy = *this;
    return copy -= other;
}

const Rational Rational::operator/(Rational& other) {
    Rational copy = *this;
    return copy /= other;
}

const Rational Rational::operator*(Rational& other) {
    Rational copy = *this;
    return copy *= other;
}

const Rational Rational::operator+() {
    return *this;
}

const Rational Rational::operator-() {
    this->SetNumerator(-num);
    return *this;
}

const Rational Rational::operator--() {
    this->SetNumerator(num - den);
    Reduce();
    return *this;
}

const Rational Rational::operator++() {
    this->SetNumerator(num + den);
    Reduce();
    return *this;
}

bool Rational::operator<(const Rational& other) const {
    return (num * other.den < den * other.num);
}

bool Rational::operator==(const Rational& other) const {
    return (num * other.den == den * other.num);
}

bool Rational::operator!=(const Rational& other) const {
    return !(operator==(other));
}

bool Rational::operator>=(const Rational& other) const {
    return !(operator<(other));
}

bool Rational::operator>(const Rational& other) const {
    return (operator>=(other) && operator!=(other));
}

bool Rational::operator<=(const Rational& other) const {
    return (operator<(other) || operator==(other));
}
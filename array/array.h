#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <iterator>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
public:
    ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
    }
};

template <class T, size_t N>
struct Array {
    T arr[N];

    T& operator[](const size_t& index) {
        return arr[index];
    }

    const T& operator[](const size_t& index) const {
        return arr[index];
    }

    T& Back() {
        return arr[N - 1];
    }

    const T& Back() const {
        return arr[N - 1];
    }

    T& Front() {
        return arr[0];
    }

    const T& Front() const {
        return arr[0];
    }

    T* Data() {
        return arr;
    }

    /*T* Data() const {
        return arr;
    }*/

    size_t Size() const {
        return N;
    }

    bool Empty() const {
        return (N == 0);
    }

    void Fill(const T& value) {
        for (size_t i = 0; i < N; ++i) {
            arr[i] = value;
        }
    }

    T& At(size_t idx) {
        if (idx > N - 1) {
            throw ArrayOutOfRange{};
        }
        return arr[idx];
    }

    const T& At(size_t idx) const {
        if (idx > N - 1) {
            throw ArrayOutOfRange{};
        }
        return arr[idx];
    }

    void Swap(Array<T, N>& other) {  // NOLINT
        for (size_t i = 0; i < N; ++i) {
            std::swap(arr[i], other.arr[i]);
        }
    }

    bool operator<(const Array<T, N>& other) const {
        size_t pos = 0;
        while (pos < N && arr[pos] == other.arr[pos]) {
            pos++;
        }
        return (pos < N && arr[pos] < other.arr[pos]);
    }

    bool operator==(const Array<T, N>& other) const {
        size_t pos = 0;
        while (pos < N && arr[pos] == other.arr[pos]) {
            pos++;
        }
        return (pos == N);
    }

    bool operator!=(const Array<T, N>& other) const {
        size_t pos = 0;
        while (pos < N && arr[pos] == other.arr[pos]) {
            pos++;
        }
        return (pos != N);
    }

    void operator=(const Array<T, N>& other) const {
        for (size_t i = 0; i < N; ++i) {
            *this[i] = other[i];
        }
    }

    bool operator>=(const Array<T, N>& other) const {
        size_t pos = 0;
        while (pos < N && arr[pos] == other.arr[pos]) {
            pos++;
        }
        return ((pos < N && arr[pos] > other.arr[pos]) || pos == N);
    }

    bool operator>(const Array<T, N>& other) const {
        return (operator>=(other) && operator!=(other));
    }

    bool operator<=(const Array<T, N>& other) const {
        return (operator<(other) || operator==(other));
    }
};

#endif  // ARRAY_ARRAY_H

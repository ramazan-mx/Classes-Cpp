#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>

class VectorOutOfRange : public std::out_of_range {
public:
    VectorOutOfRange() : std::out_of_range("VectorOutOfRange") {
    }
};

template <class T>
class Vector {
private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T* buffer_ = nullptr;

    void Copy(T* buffer_to, T* buffer_from, size_t size) {
        for (size_t i = 0; i < size; ++i) {
            buffer_to[i] = buffer_from[i];
        }
    }
    void Fill(size_t start, size_t end, const T& value) {
        for (size_t i = start; i < end; ++i) {
            buffer_[i] = value;
        }
    }

    void BufferReallocation(size_t new_capacity) {
        T* new_buffer = ((new_capacity == 0) ? nullptr : (new T[new_capacity]));
        size_ = std::min(size_, new_capacity);
        capacity_ = new_capacity;
        if (new_capacity == 0) {
            delete[] buffer_;
            buffer_ = new_buffer;
            return;
        }
        Copy(new_buffer, buffer_, size_);
        delete[] buffer_;
        buffer_ = new_buffer;
    }

public:
    Vector() {
        size_ = 0;
        capacity_ = 0;
        buffer_ = nullptr;
    }

    explicit Vector(size_t count_elements) {
        size_ = count_elements;
        capacity_ = count_elements;
        if (capacity_ == 0) {
            buffer_ = nullptr;
            return;
        }
        buffer_ = new T[capacity_];
    }

    Vector(size_t count_elements, const T& value) {
        size_ = count_elements;
        capacity_ = count_elements;
        if (capacity_ == 0) {
            buffer_ = nullptr;
            return;
        }
        buffer_ = new T[capacity_];
        Fill(0, size_, value);
    }

    Vector(const Vector<T>& other) {
        if (other.capacity_ > 0) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            buffer_ = new T[capacity_];
            Copy(buffer_, other.buffer_, size_);
        } else {
            buffer_ = nullptr;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
    }

    Vector<T>& operator=(const Vector<T>& other) {
        delete[] buffer_;
        if (other.capacity_ > 0) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            buffer_ = new T[capacity_];
            Copy(buffer_, other.buffer_, size_);
            return *this;
        }
        buffer_ = nullptr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        return *this;
    }

    ~Vector() {
        delete[] buffer_;
    }

    void Clear() {
        size_ = 0;
    }

    void PushBack(const T& value) {
        if (size_ < capacity_) {
            buffer_[size_] = value;
            ++size_;
            return;
        }
        if (buffer_ == nullptr) {
            buffer_ = new T[1];
            capacity_ = 1;
            size_ = 1;
            buffer_[0] = value;
            return;
        }
        BufferReallocation(capacity_ * 2);
        buffer_[size_] = value;
        ++size_;
    }

    void PopBack() {
        if (size_ == 0) {
            return;
        }
        --size_;
    }

    void Resize(size_t new_size) {
        if (new_size > capacity_) {
            BufferReallocation(new_size);
            size_ = new_size;
        } else {
            size_ = new_size;
        }
    }
    void Resize(size_t new_size, const T& value) {
        if (new_size <= size_) {
            size_ = new_size;
            return;
        }
        if (new_size <= capacity_) {
            Fill(size_, new_size, value);
            size_ = new_size;
            return;
        }
        BufferReallocation(new_size);
        Fill(size_, new_size, value);
        size_ = new_size;
    }

    void Reserve(size_t new_cap) {
        std::cerr << new_cap << "\n";
        if (new_cap > capacity_) {
            BufferReallocation(new_cap);
        }
    }

    void ShrinkToFit() {
        if (capacity_ > size_) {
            BufferReallocation(size_);
        }
    }

    void Swap(Vector<T>& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(buffer_, other.buffer_);
    }

    T& operator[](const size_t& index) {
        return buffer_[index];
    }

    const T& operator[](const size_t& index) const {
        return buffer_[index];
    }

    T& At(size_t index) {
        if (index >= size_) {
            throw VectorOutOfRange();
        }
        return buffer_[index];
    }

    const T& At(size_t index) const {
        if (index >= size_) {
            throw VectorOutOfRange();
        }
        return buffer_[index];
    }

    T& Front() {
        return buffer_[0];
    }

    const T& Front() const {
        return buffer_[0];
    }

    T& Back() {
        return buffer_[size_ - 1];
    }

    const T& Back() const {
        return buffer_[size_ - 1];
    }

    bool Empty() const {
        return size_ == 0;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    T* Data() {
        return (&buffer_[0]);
    }
    const T* Data() const {
        return (&buffer_[0]);
    }

    bool operator==(const Vector<T>& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (size_t i = 0; i < size_; ++i) {
            if (buffer_[i] != other.buffer_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>(const Vector<T>& other) const {
        size_t post = 0;
        while (post < size_ && post < other.size_) {
            if ((*this)[post] > other[post]) {
                return true;
            }
            if ((*this)[post] < other[post]) {
                return false;
            }
            post++;
        }
        return (size_ > other.size_);
    }

    bool operator>=(const Vector<T>& other) const {
        return (this->operator>(other) || this->operator==(other));
    }

    bool operator<(const Vector<T>& other) const {
        return !(this->operator>=(other));
    }

    bool operator<=(const Vector<T>& other) const {
        return !(this->operator>(other));
    }

    bool operator!=(const Vector<T>& other) const {
        return !(this->operator==(other));
    }
};

#endif  // VECTOR_VECTOR_H
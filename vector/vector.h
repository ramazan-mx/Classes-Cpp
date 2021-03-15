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
        std::cerr << "Vector(cnt) " << size_ << " " << capacity_ << "\n";
    }

    Vector(size_t count_elements, const T& value) {
        size_ = count_elements;
        capacity_ = count_elements;
        if (capacity_ == 0) {
            buffer_ = nullptr;
            return;
        }
        buffer_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            buffer_[i] = value;
        }
        std::cerr << "Vector(cnt, value) " << size_ << " " << capacity_ << "\n";
    }

    Vector(const Vector<T>& other) {
        if (other.capacity_ > 0) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            buffer_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                buffer_[i] = other.buffer_[i];
            }
        } else {
            buffer_ = nullptr;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        std::cerr << "Vector(other) " << size_ << " " << capacity_ << "\n";
    }

    Vector<T>& operator=(const Vector<T>& other) {
        delete[] buffer_;
        if (other.capacity_ > 0) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            buffer_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                buffer_[i] = other.buffer_[i];
            }
            std::cerr << "operator= " << size_ << " " << capacity_ << "\n";
            return *this;
        }
        buffer_ = nullptr;
        size_ = other.size_;
        capacity_ = other.capacity_;
        std::cerr << "operator= " << size_ << " " << capacity_ << "\n";
        return *this;
    }

    ~Vector() {
        delete[] buffer_;
        std::cerr << "~Vector " << size_ << " " << capacity_ << "\n";
    }

    void Clear() {
        size_ = 0;
        std::cerr << "Clear " << size_ << " " << capacity_ << "\n";
    }

    void PushBack(const T& value) {
        if (size_ < capacity_) {
            buffer_[size_] = value;
            ++size_;
            return;
        }
        Reserve(capacity_ * 2);
        buffer_[size_] = value;
        ++size_;
        std::cerr << "PushBack " << size_ << " " << capacity_ << "\n";
    }

    void PopBack() {
        if (size_ == 0) {
            return;
        }
        --size_;
        std::cerr << "PopBack " << size_ << " " << capacity_ << "\n";
    }

    void Resize(size_t new_size) {
        if (new_size > capacity_) {
            Reserve(new_size);
            size_ = new_size;
        } else {
            size_ = new_size;
        }
        std::cerr << "Resize(new_size) " << size_ << " " << capacity_ << "\n";
    }
    void Resize(size_t new_size, T value) {
        if (new_size > capacity_) {
            T* new_buffer = new T[new_size];
            capacity_ = new_size;
            for (size_t i = 0; i < size_; ++i) {
                new_buffer[i] = buffer_[i];
            }
            delete[] buffer_;
            buffer_ = new_buffer;
            for (size_t i = size_; i < new_size; ++i) {
                buffer_[i] = value;
            }
            size_ = new_size;
            std::cerr << "Resize(new_size, value) " << size_ << " " << capacity_ << "\n";
            return;
        }
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i) {
                buffer_[i] = value;
            }
            size_ = new_size;
            std::cerr << "Resize(new_size, value) " << size_ << " " << capacity_ << "\n";
            return;
        }
        size_ = new_size;
        std::cerr << "Resize(new_size, value) " << size_ << " " << capacity_ << "\n";
    }

    void Reserve(size_t new_cap) {
        std::cerr << new_cap << "\n";
        if (new_cap > capacity_) {
            if (capacity_ == 0) {
                capacity_ = new_cap;
                delete[] buffer_;
                buffer_ = new T[capacity_];
                return;
            }
            capacity_ = new_cap;
            T* new_buffer = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                new_buffer[i] = buffer_[i];
            }
            delete[] buffer_;
            buffer_ = new_buffer;
        }
        std::cerr << "Reserve(new_cap) " << size_ << " " << capacity_ << "\n";
    }

    void ShrinkToFit() {
        if (capacity_ > size_) {
            capacity_ = size_;
            if (capacity_ == 0) {
                delete[] buffer_;
                buffer_ = nullptr;
                std::cerr << "ShrinkToFit " << size_ << " " << capacity_ << "\n";
                return;
            }
            T* new_buffer = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                new_buffer[i] = buffer_[i];
            }
            delete[] buffer_;
            buffer_ = new_buffer;
        }
        std::cerr << "ShrinkToFit " << size_ << " " << capacity_ << "\n";
    }

    void Swap(Vector<T>& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(buffer_, other.buffer_);
        std::cerr << "Swap " << size_ << " " << capacity_ << "\n";
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
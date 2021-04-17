#include <iostream>
#include <vector>

class BadWeakPtr : public std::runtime_error {
public:
    BadWeakPtr() : std::runtime_error("BadWeakPtr") {
    }
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
private:
    T* ptr_;

    void Delete(T* ptr) {
        for (size_t i = 0; i < cells.size(); ++i) {
            if (cells[i] == ptr) {
                cells.erase(cells.begin() + i);
                return;
            }
        }
    }

public:
    static std::vector<T*> cells;

    SharedPtr() : ptr_(nullptr) {
    }

    SharedPtr(T* ptr) : ptr_(ptr) {  //  NOLINT
        cells.push_back(ptr_);
    }

    SharedPtr(const SharedPtr& other) {
        ptr_ = other.ptr_;
        cells.push_back(ptr_);
    }

    SharedPtr& operator=(T* ptr) {
        if (UseCount() == 1) {
            delete ptr_;
        }
        Delete(ptr_);
        ptr_ = ptr;
        cells.push_back(ptr_);
        return *this;
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this == &other) {
            return *this;
        }
        if (UseCount() == 1) {
            delete ptr_;
        }
        Delete(ptr_);
        ptr_ = other.ptr_;
        cells.push_back(ptr_);
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        if (UseCount() == 1) {
            delete ptr_;
        }
        Delete(ptr_);
        Delete(other.ptr_);
        ptr_ = other.ptr_;
        cells.push_back(ptr_);
        other.ptr_ = nullptr;
        return *this;
    }

    explicit SharedPtr(WeakPtr<T> ptr) {
        if (ptr.Expired()) {
            throw BadWeakPtr();
        }
        ptr_ = ptr.Get();
        cells.push_back(ptr_);
    }

    ~SharedPtr() {
        if (UseCount() == 1) {
            delete ptr_;
        }
        Delete(ptr_);
    }

    void Swap(SharedPtr<T>& other) {
        std::swap(ptr_, other.ptr_);
    }

    size_t UseCount() {
        size_t count = 0;
        if (ptr_ == nullptr) {
            return 0;
        }
        for (size_t i = 0; i < cells.size(); ++i) {
            if (cells[i] == ptr_) {
                ++count;
            }
        }
        return count;
    }

    void Reset(T* ptr = nullptr) {
        if ((*this).UseCount() == 1) {
            delete ptr_;
        }
        Delete(ptr_);
        ptr_ = ptr;
        cells.push_back(ptr_);
    }

    T* Get() {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    T* Get() const {
        return ptr_;
    }

    explicit operator bool() const {
        return ptr_ != nullptr;
    }
};

template <class T>
std::vector<T*> SharedPtr<T>::cells;

template <class T>
class WeakPtr {
private:
    T* ptr_;

public:
    WeakPtr() : ptr_(nullptr) {
    }

    WeakPtr(T* ptr) : ptr_(ptr) {  // NOLINT
    }

    WeakPtr(const WeakPtr<T>& other) {
        ptr_ = other.ptr_;
    }

    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        if (this == &other) {
            return *this;
        }
        ptr_ = other.ptr_;
        return *this;
    }

    WeakPtr(WeakPtr<T>&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }

    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        return *this;
    }

    WeakPtr(SharedPtr<T> ptr) {  // NOLINT
        ptr_ = ptr.Get();
    }

    WeakPtr<T>& operator=(SharedPtr<T> ptr) {
        ptr_ = ptr.Get();
        return *this;
    }

    ~WeakPtr() = default;
    void Swap(WeakPtr<T>& other) {
        std::swap(ptr_, other.ptr_);
    }

    size_t UseCount() const {
        size_t count = 0;
        if (ptr_ == nullptr) {
            return 0;
        }
        for (size_t i = 0; i < SharedPtr<T>::cells.size(); ++i) {
            if (SharedPtr<T>::cells[i] == ptr_) {
                ++count;
            }
        }
        return count;
    }

    void Reset() {
        ptr_ = nullptr;
    }

    bool Expired() const {
        return (UseCount() == 0);
    }

    SharedPtr<T> Lock() const {
        if (Expired()) {
            SharedPtr<T> temp;
            return temp;
        };
        SharedPtr<T> temp(*this);
        return temp;
    }

    T* Get() {
        return ptr_;
    }
};
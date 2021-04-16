template <class T>
class UniquePtr {
private:
    T* ptr_;

public:
    UniquePtr() : ptr_(nullptr) {
    }

    explicit UniquePtr(T* ptr) : ptr_(ptr) {
    }

    UniquePtr(const UniquePtr& other) = delete;

    UniquePtr& operator=(const UniquePtr& other) = delete;

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T* Release() {
        auto tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void Reset(T* ptr = nullptr) {
        delete ptr_;
        ptr_ = ptr;
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
        return Get() != nullptr;
    }
};
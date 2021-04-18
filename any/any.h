#include <memory>
#include <exception>

class BadAnyCast : public std::bad_cast {
public:
    const char* what() const noexcept override {
        return "Bad Any Cast";
    }
};

class Any;

template <class T>
T AnyCast(const Any& value);

class Any {
    template <class T>
    friend T AnyCast(const Any& value);

    struct IBase {
        virtual std::unique_ptr<IBase> Clone() const = 0;
        virtual ~IBase() = default;
    };

    template <class T>
    struct Derived : public IBase {
        T value;
        explicit Derived(T v) : value(std::move(v)) {
        }
        std::unique_ptr<IBase> Clone() const override {
            return std::make_unique<Derived>(value);
        }
    };
    std::unique_ptr<IBase> storage_{};

public:
    Any() = default;

    Any(const Any& any) : storage_(any.storage_->Clone()) {
    }

    template <class T>
    Any(T value) : storage_(std::make_unique<Derived<T>>(std::move(value))) {  // NOLINT
    }

    void Swap(Any& any) noexcept {
        any.storage_.swap(storage_);
    }

    Any(Any&& any) noexcept {
        Swap(any);
    }

    Any& operator=(Any any) noexcept {
        Swap(any);
        return *this;
    }

    bool HasValue() const noexcept {
        return storage_ != nullptr;
    }

    void Reset() {
        storage_.reset();
    }

    template <class T>
    friend T any_cast(const Any& value);  //  NOLINT
};

template <class T>
T AnyCast(const Any& value) {
    auto* result = dynamic_cast<Any::Derived<T>*>(value.storage_.get());
    if (!result) {
        throw BadAnyCast();
    }
    return result->value;
}
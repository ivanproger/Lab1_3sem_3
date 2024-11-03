#pragma once

template <typename T>
class ShrdPtr {
private:
    T* ptr;
    size_t* referenceCount;

public:
    ShrdPtr(T* p = nullptr) : ptr(p), referenceCount(new size_t(1)) {}

    ShrdPtr(const ShrdPtr& other) : ptr(other.ptr), referenceCount(other.referenceCount) {
        ++(*referenceCount);
    }

    ShrdPtr(UnqPtr<T>&& uptr) : ptr(uptr.release()), referenceCount(new size_t(1)) {}

    ~ShrdPtr() {
        if (--(*referenceCount) == 0) {
            delete ptr;
            delete referenceCount;
        }
    }

    size_t useCount() {
        return *referenceCount;
    }

    bool isNull() const {
        return ptr == nullptr;
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }
};

#pragma once

template <typename T>
class UnqPtr {
private:
    T* ptr;

public:

    T* get() const {
        return ptr;
    }

    UnqPtr(T* p = nullptr) : ptr(p) {}

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    //��������� ������ ������
    ~UnqPtr() {
        delete ptr;
    }

    // ��������� �����������
    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // ��������� �����������
    UnqPtr(UnqPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr; // ����������� ���������
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    UnqPtr& operator=(UnqPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
};

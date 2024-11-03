#pragma once

#include "MemorySpan.h"

template <typename T>
class MsPtr {
private:
    MemorySpan<T>& span; // Reference to the MemorySpan
    size_t indexMemorySpan;        // index in the MemorySpan

public:
    // Constructor
    MsPtr(MemorySpan<T>& span, size_t index) : span(span), indexMemorySpan(index) {
        if (index >= span.getSize() || span.getCounter(index) == 0) {
            throw std::out_of_range("index out of range or element does not exist");
        }
    }

    // Overloading dereference operator
    T& operator*() const {
        return *(span.getElement(indexMemorySpan));
    }

    // Overloading arrow operator
    T* operator->() const {
        return span.getElement(indexMemorySpan);
    }

    // Overloading increment operator for pointer arithmetic
    MsPtr<T>& operator++() {
        if (indexMemorySpan + 1 >= span.getSize() || span.getCounter(indexMemorySpan + 1) == 0) {
            throw std::out_of_range("Incrementing out of bounds");
        }
        ++indexMemorySpan;
        return *this;
    }

    // Overloading decrement operator for pointer arithmetic
    MsPtr<T>& operator--() {
        if (indexMemorySpan == 0) {
            throw std::out_of_range("Decrementing out of bounds");
        }
        --indexMemorySpan;
        return *this;
    }

    // Overloading addition operator for pointer arithmetic
    MsPtr<T> operator+(size_t offset) const {
        if (indexMemorySpan + offset >= span.getSize() || span.getCounter(indexMemorySpan + offset) == 0) {
            throw std::out_of_range("Adding offset out of bounds");
        }
        return MsPtr<T>(span, indexMemorySpan + offset);
    }

    // Overloading subtraction operator for pointer arithmetic
    MsPtr<T> operator-(size_t offset) const {
        if (indexMemorySpan < offset) {
            throw std::out_of_range("Subtracting offset out of bounds");
        }
        return MsPtr<T>(span, indexMemorySpan - offset);
    }

    // Destructor
    ~MsPtr() {
        // No need to manage memory here, as MemorySpan handles it
    }
};
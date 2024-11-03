#pragma once

template <typename T>
class Pointer;

template <typename T>
class MemorySpan {
private:
    T** elems;     //T*
    size_t* counter;
    size_t nexter;
    size_t sizeMemorySpan;
    size_t* nextElems;   //ошибка в формате имён

public:
    MemorySpan(size_t size) : nexter(0), sizeMemorySpan(size) {
        elems = new T * [size];
        counter = new size_t[size];
        nextElems = new size_t[size];

        for (size_t i = 0; i < size; ++i) {
            counter[i] = 0;
            elems[i] = nullptr;
            nextElems[i] = (i < size - 1) ? (i + 1) : size; //не нужно тернарный if
        }
    }

    ~MemorySpan() {
        for (size_t i = 0; i < sizeMemorySpan; ++i) {
            delete elems[i];
        }
        delete[] elems;
        delete[] counter;
        delete[] nextElems;
    }

    Pointer<T> NewPointer(T* newObj);

    //не понятно как узнать это и нельзя показывать индексы, а должны быть только указатели
    T* getElement(size_t index) const {
        if (index < sizeMemorySpan && elems[index] != nullptr) {
            return elems[index];
        }
        throw std::out_of_range("Index out of range or element does not exist");
    }

    void deletePointer(size_t index) {
        if (index >= sizeMemorySpan || elems[index] == nullptr) {
            return;
        }

        if (--counter[index] == 0) {
            delete elems[index];
            elems[index] = nullptr;
            nextElems[index] = nexter;
            nexter = index;
        }
    }

    size_t getSize() const {
        return sizeMemorySpan;
    }

    size_t getCounter(size_t index) const {
        if (index < sizeMemorySpan) {
            return counter[index];
        }
        return 0;
    }

    const size_t* getCounters() const {
        return counter;
    }

    T** getElements() const {
        return elems;
    }
};

template <typename T>
class Pointer {
private:
    MemorySpan<T>& span_;
    size_t index_;

public:
    Pointer(MemorySpan<T>& span, size_t index) : span_(span), index_(index) {
        if (index_ >= span.getSize() || span.getCounter(index_) == 0) {
            throw std::out_of_range("Index out of range or element does not exist");
        }
    }

    ~Pointer() {
        span_.deletePointer(index_);
    }
    //найти ошибку
    T getValue() const {
        return *(span_.getElement(index_));
    }
};

template <typename T>
Pointer<T> MemorySpan<T>::NewPointer(T* newObj) {
    for (size_t i = 0; i < sizeMemorySpan; ++i) {
        if (elems[i] != nullptr && *elems[i] == *newObj) {
            counter[i]++;
            return Pointer<T>(*this, i);
        }
    }

    if (nexter < sizeMemorySpan) {
        size_t index = nexter;
        elems[index] = newObj;
        counter[index] = 1;
        nexter = nextElems[nexter];
        return Pointer<T>(*this, index);
    }

    throw std::runtime_error("No free space for a new element.");
}

//чем лучше memory_span лучше массива shrd ptr указателей
//хранить массив элементов и а не указатели
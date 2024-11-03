#pragma once

#include "Test.h"   

int mainFunc();

template <typename T>
void showPointer(const MemorySpan<T>& span);

template<typename T>
void displayShrdPtrs(ShrdPtr<T>** massPointers, T* massValue, int counter);

template<typename T>
void cleanShrdPtrs(ShrdPtr<T>** massPointers, int counter);

void createShrdPtrsInt();
void createShrdPtrsChar();

template<typename T>
void displayUnqPtrs(UnqPtr<T>** uniquePointers, T* valuesArray, int pointerCount);

template<typename T>
void cleanUnqPtrs(UnqPtr<T>** uniquePointers, int pointerCount);

void createUnqPtrsInt();
void createUnqPtrsChar();

void createMemorySpanInt();
void createMemorySpanChar();


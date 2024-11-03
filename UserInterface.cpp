#pragma once

#include "UserInterface.h"

template <typename T>
void showPointer(const MemorySpan<T>& span) {
    const size_t* counters = span.getCounters();
    T** elements = span.getElements();
    for (size_t i = 0; i < span.getSize(); ++i) {
        if (elements[i] != nullptr) {
            std::cout << "elem[" << i << "] = " << *elements[i]
                << ", counter = " << counters[i]
                << ", address = " << elements[i] << std::endl;
        }
        else {
            std::cout << "elem[" << i << "] = nullptr, counter = " << counters[i] << std::endl;
        }
    }
}

template<typename T>
void displayUnqPtrs(UnqPtr<T>** uniquePointers, T* valuesArray, int pointerCount) {
    std::cout << "UnqPtrs created:" << std::endl;
    for (int i = 0; i < pointerCount; ++i) {
        if (uniquePointers[i] != nullptr) {
            std::cout << "Unq Pointer " << i << ": Value = " << valuesArray[i] << std::endl;
        }
    }
    mainFunc();
}

template<typename T>
void cleanUnqPtrs(UnqPtr<T>** uniquePointers, int pointerCount) {
    for (int i = 0; i < pointerCount; ++i) {
        delete uniquePointers[i];
    }
}

template<typename T>
void displayShrdPtrs(ShrdPtr<T>** massPointers, T* massValue, int counter) {
    std::cout << "ShrdPtrs created:" << std::endl;
    for (int i = 0; i < counter; ++i) {
        std::cout << "Shrd Pointer " << i << ": Value = " << massValue[i]
            << ", Reference count = " << massPointers[i]->useCount() << std::endl;
    }
    mainFunc();
}

template<typename T>
void cleanShrdPtrs(ShrdPtr<T>** massPointers, int counter) {
    for (int i = 0; i < counter; ++i) {
        delete massPointers[i];
    }
}

void createShrdPtrsChar() {
    ShrdPtr<char>* massPointers[100];
    char massValue[100];
    int counter = 0;

    while (true) {
        std::cout << "Create ShrdPtr (enter character or type 'END' to exit):" << std::endl;
        std::string value;
        std::cin >> value;

        if (value == "END") {
            break;
        }

        if (value.length() != 1) {
            std::cout << "Please enter a single character." << std::endl;
            continue;
        }

        char charValue = value[0];

        bool found = false;
        for (int i = 0; i < counter; ++i) {
            if (massValue[i] == charValue) {
                std::cout << "Shrd Pointer(char) already exists. Incrementing reference count.\n";
                found = true;
                massPointers[counter] = new ShrdPtr<char>(*massPointers[i]);
                break;
            }
        }

        if (!found) {
            massPointers[counter] = new ShrdPtr<char>(new char(charValue));
            massValue[counter] = charValue;
            std::cout << "New ShrdPtr(char) created with value: " << charValue << std::endl;
            counter++;
        }
    }

    displayShrdPtrs(massPointers, massValue, counter);
    cleanShrdPtrs(massPointers, counter);
}

void createShrdPtrsInt() {
    ShrdPtr<int>* massPointers[100];
    int massValue[100];
    int counter = 0;

    while (true) {
        std::cout << "Create ShrdPtr (enter value or type 'END' to exit):" << std::endl;
        std::string value;
        std::cin >> value;

        if (value == "END") {
            break;
        }

        int intValue;
        try {
            intValue = std::stoi(value);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid input, please enter an integer." << std::endl;
            continue;
        }
        catch (std::out_of_range&) {
            std::cout << "Input is out of range for an integer." << std::endl;
            continue;
        }

        bool found = false;
        for (int i = 0; i < counter; ++i) {
            if (massValue[i] == intValue) {
                std::cout << "Pointer Shrd(int) already exists. Incrementing reference count.\n";
                found = true;
                massPointers[counter] = new ShrdPtr<int>(*massPointers[i]);
                break;
            }
        }

        if (!found) {
            massPointers[counter] = new ShrdPtr<int>(new int(intValue));
            massValue[counter] = intValue;
            std::cout << "New ShrdPtr(int) created with value: " << intValue << std::endl;
            counter++;
        }
    }

    displayShrdPtrs(massPointers, massValue, counter);
    cleanShrdPtrs(massPointers, counter);
}

void createUnqPtrsInt() {
    UnqPtr<int>* uniquePointers[100];
    int valuesArray[100];
    int pointerCount = 0;

    while (true) {
        std::cout << "Create UnqPtr (enter value or type 'END' to exit):" << std::endl;
        std::string value;
        std::cin >> value;

        if (value == "END") {
            break;
        }

        int inputValue;
        try {
            inputValue = std::stoi(value);
        }
        catch (std::invalid_argument&) {
            std::cout << "Invalid input, please enter a valid integer." << std::endl;
            continue;
        }
        catch (std::out_of_range&) {
            std::cout << "Input is out of range for an integer." << std::endl;
            continue;
        }

        bool isDuplicate = false;
        for (int i = 0; i < pointerCount; ++i) {
            if (valuesArray[i] == inputValue) {
                std::cout << "Pointer already exists. No new pointer created.\n";
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            uniquePointers[pointerCount] = new UnqPtr<int>(new int(inputValue));
            valuesArray[pointerCount] = inputValue;
            std::cout << "New UnqPtr created with value: " << inputValue << std::endl;
            pointerCount++;
        }
    }

    displayUnqPtrs(uniquePointers, valuesArray, pointerCount);
    cleanUnqPtrs(uniquePointers, pointerCount);
}

void createUnqPtrsChar() {
    UnqPtr<char>* uniquePointers[100];
    char valuesArray[100];
    int pointerCount = 0;

    while (true) {
        std::cout << "Create UnqPtr (enter character or type 'END' to exit):" << std::endl;
        std::string value;
        std::cin >> value;

        if (value == "END") {
            break;
        }

        if (value.length() != 1) {
            std::cout << "Please enter a single character." << std::endl;
            continue;
        }

        char inputValue = value[0];

        bool isDuplicate = false;
        for (int i = 0; i < pointerCount; ++i) {
            if (valuesArray[i] == inputValue) {
                std::cout << "Pointer already exists. No new pointer created.\n";
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            uniquePointers[pointerCount] = new UnqPtr<char>(new char(inputValue));
            valuesArray[pointerCount] = inputValue;
            std::cout << "New UnqPtr created with value: " << inputValue << std::endl;
            pointerCount++;
        }
    }

    displayUnqPtrs(uniquePointers, valuesArray, pointerCount);
    cleanUnqPtrs(uniquePointers, pointerCount);
}

void createMemorySpanInt() {
    MemorySpan<int> memorySpan(5);
    int mass[5];

    std::cout << "Enter 5 values: " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Enter a value to add to MemorySpan: ";
        std::cin >> mass[i];
    }

    Pointer<int> ptr1 = memorySpan.NewPointer(new int(mass[0]));
    Pointer<int> ptr2 = memorySpan.NewPointer(new int(mass[1]));
    Pointer<int> ptr3 = memorySpan.NewPointer(new int(mass[2]));
    Pointer<int> ptr4 = memorySpan.NewPointer(new int(mass[3]));
    Pointer<int> ptr5 = memorySpan.NewPointer(new int(mass[4]));

    showPointer(memorySpan);
}

void createMemorySpanChar() {
    MemorySpan<char> memorySpan(5);
    char mass[5];

    std::cout << "Enter 5 values: " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Enter a value to add to MemorySpan: ";
        std::cin >> mass[i];
    }

    Pointer<char> ptr1 = memorySpan.NewPointer(new char(mass[0]));
    Pointer<char> ptr2 = memorySpan.NewPointer(new char(mass[1]));
    Pointer<char> ptr3 = memorySpan.NewPointer(new char(mass[2]));
    Pointer<char> ptr4 = memorySpan.NewPointer(new char(mass[3]));
    Pointer<char> ptr5 = memorySpan.NewPointer(new char(mass[4]));

    showPointer(memorySpan);
}
int mainFunc() {
    while (true) {
        std::string choice;
        std::string dataType;

        std::cout << "What would you like to work with? (shrd, uniq, memoryspan) or type 'END' to exit: ";
        std::cin >> choice;

        if (choice == "END") {
            break;
        }

        std::cout << "Choose data type (int or char): ";
        std::cin >> dataType;

        if (dataType != "int" && dataType != "char") {
            std::cout << "Invalid data type selected. Please choose 'int' or 'char'." << std::endl;
            return -1;
        }

        if (choice == "shrd") {
            if (dataType == "int") {
                createShrdPtrsInt();
            }
            else {
                createShrdPtrsChar();
            }
        }
        else if (choice == "uniq") {
            if (dataType == "int") {
                createUnqPtrsInt();
            }
            else {
                createUnqPtrsChar();
            }
        }
        else if (choice == "memoryspan") {
            if (dataType == "int") {
                createMemorySpanInt();
            }
            else {
                createMemorySpanChar();
            }
        }
        else {
            std::cout << "Invalid choice. Please select 'shrd', 'uniq', or 'memoryspan'." << std::endl;
            return -1;
        }
    }

    testMemorySpan();
    testMsPtr();
    testShrdPtr();
    testUnqPtr();
    
    loadTestShrdPtr(1000);
    loadTestStdSharedPtr(1000);
    loadTestUnqPtr(100000);
    loadTestStdUniquePtr(100000);

    return 0;
};
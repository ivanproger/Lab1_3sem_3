#pragma once

#include "Test.h"

//MemorySpan

void testMemorySpan() {

    //int:

    MemorySpan<int> intSpan(5);

    int* num1 = new int(10);
    Pointer<int> p1 = intSpan.NewPointer(num1);
    assert(p1.getValue() == 10);

    int* num2 = new int(20);
    Pointer<int> p2 = intSpan.NewPointer(num2);
    assert(p2.getValue() == 20);

    int* num3 = new int(30);
    Pointer<int> p3 = intSpan.NewPointer(num3);
    assert(p3.getValue() == 30);

    assert(*intSpan.getElement(0) == 10);
    assert(*intSpan.getElement(1) == 20);
    assert(*intSpan.getElement(2) == 30);

    assert(intSpan.getCounter(0) == 1);
    assert(intSpan.getCounter(1) == 1);
    assert(intSpan.getCounter(2) == 1);

    Pointer<int> p4 = intSpan.NewPointer(num1);
    assert(p4.getValue() == 10);
    assert(intSpan.getCounter(0) == 2);

    p1.~Pointer();
    assert(intSpan.getCounter(0) == 1);

    p2.~Pointer();
    assert(intSpan.getCounter(1) == 0);

    assert(*intSpan.getElement(2) == 30);

    p3.~Pointer();
    assert(intSpan.getCounter(2) == 0);

    int* num4 = new int(40);
    Pointer<int> p5 = intSpan.NewPointer(num4);
    assert(p5.getValue() == 40);

    assert(intSpan.getCounter(2) == 1);

    p5.~Pointer();

    //char:

    MemorySpan<char> charSpan(5);
    char* char1 = new char('e');
    Pointer<char> c = charSpan.NewPointer(char1);
    assert(c.getValue() == 'e');


    std::cout << "MemorySpan OK" << std::endl;

}

//MsPtr

int testMsPtr() {

    // Тестирование для типа int

    {
        MemorySpan<int> span(5);

        Pointer<int> p1 = span.NewPointer(new int(10));
        Pointer<int> p2 = span.NewPointer(new int(20));
        Pointer<int> p3 = span.NewPointer(new int(30));

        MsPtr<int> msPtr1(span, 0);
        MsPtr<int> msPtr2(span, 1);
        MsPtr<int> msPtr3(span, 2);

        assert(*msPtr1 == 10);
        assert(*msPtr2 == 20);
        assert(*msPtr3 == 30);

        assert(*++msPtr1 == 20);
        assert(*msPtr1 == 20);

        assert(*--msPtr1 == 10);
        assert(*msPtr1 == 10);

        assert(*(msPtr1 + 1) == 20);

        span.deletePointer(0);
        span.deletePointer(1);
        span.deletePointer(2);
    }

    // Тестирование для типа char

    {
        MemorySpan<char> span(5);

        Pointer<char> p1 = span.NewPointer(new char('A'));
        Pointer<char> p2 = span.NewPointer(new char('B'));
        Pointer<char> p3 = span.NewPointer(new char('C'));

        MsPtr<char> msPtr1(span, 0);
        MsPtr<char> msPtr2(span, 1);
        MsPtr<char> msPtr3(span, 2);

        assert(*msPtr1 == 'A');
        assert(*msPtr2 == 'B');
        assert(*msPtr3 == 'C');

        assert(*++msPtr1 == 'B');
        assert(*msPtr1 == 'B');

        assert(*--msPtr1 == 'A');
        assert(*msPtr1 == 'A');

        assert(*(msPtr1 + 1) == 'B');

        span.deletePointer(0);
        span.deletePointer(1);
        span.deletePointer(2);
    }

    std::cout << "MsPtr OK" << std::endl;
    return 0;
}

//ShrdPtr

void testShrdPtr() {
    ShrdPtr<int> p1(new int(5));
    assert(*p1 == 5);

    ShrdPtr<int> p2 = p1;
    assert(*p2 == 5);
    assert(p1.operator->() == p2.operator->());

    {
        ShrdPtr<int> p3 = p2;
        assert(*p3 == 5);
        assert(p2.operator->() == p3.operator->());
    }

    assert(*p1 == 5);
    assert(*p2 == 5);

    UnqPtr<int> uptr(new int(10));
    ShrdPtr<int> p4(std::move(uptr));
    assert(*p4 == 10);

    ShrdPtr<char> p5(new char('A'));
    assert(*p5 == 'A');

    ShrdPtr<char> p6 = p5;
    assert(*p6 == 'A');
    assert(p5.operator->() == p6.operator->());

    {
        ShrdPtr<char> p7 = p6;
        assert(*p7 == 'A');
        assert(p6.operator->() == p7.operator->());
    }

    assert(*p5 == 'A');
    assert(*p6 == 'A');

    UnqPtr<char> uptrChar(new char('B'));
    ShrdPtr<char> p8(std::move(uptrChar));
    assert(*p8 == 'B');

    ShrdPtr<float> p9(new float(3.14f));
    assert(*p9 == 3.14f);

    ShrdPtr<float> p10 = p9;
    assert(*p10 == 3.14f);
    assert(p9.operator->() == p10.operator->());

    {
        ShrdPtr<float> p11 = p10;
        assert(*p11 == 3.14f);
        assert(p10.operator->() == p11.operator->());
    }

    assert(*p9 == 3.14f);
    assert(*p10 == 3.14f);

    UnqPtr<float> uptrFloat(new float(2.71f));
    ShrdPtr<float> p12(std::move(uptrFloat));
    assert(*p12 == 2.71f);

    std::cout << "ShrdPtr OK" << std::endl;
}

void loadTestShrdPtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<ShrdPtr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(new int(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects ShrdPtr for " << duration.count() << " seconds." << std::endl;
}

void loadTestStdSharedPtr(int objectCount) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::shared_ptr<int>> ptrs;
    for (int i = 0; i < objectCount; ++i) {
        ptrs.emplace_back(std::make_shared<int>(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects std::shared_ptr for " << duration.count() << " seconds." << std::endl;
}

//UnqPtr

void testUnqPtr() {
    {
        UnqPtr<int> uptr(new int(5));
        assert(*(uptr.get()) == 5);
    }

    {
        UnqPtr<int> uptr1(new int(10));
        UnqPtr<int> uptr2(std::move(uptr1));
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 10);
    }

    {
        UnqPtr<int> uptr1(new int(20));
        UnqPtr<int> uptr2;
        uptr2 = std::move(uptr1);
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 20);
    }

    {
        UnqPtr<char> uptr(new char('A'));
        assert(*(uptr.get()) == 'A');
    }

    {
        UnqPtr<char> uptr1(new char('B'));
        UnqPtr<char> uptr2(std::move(uptr1));
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 'B');
    }

    {
        UnqPtr<char> uptr1(new char('C'));
        UnqPtr<char> uptr2;
        uptr2 = std::move(uptr1);
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 'C');
    }

    {
        UnqPtr<float> uptr(new float(3.14f));
        assert(*(uptr.get()) == 3.14f);
    }

    {
        UnqPtr<float> uptr1(new float(2.71f));
        UnqPtr<float> uptr2(std::move(uptr1));
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 2.71f);
    }

    {
        UnqPtr<float> uptr1(new float(1.61f));
        UnqPtr<float> uptr2;
        uptr2 = std::move(uptr1);
        assert(uptr1.get() == nullptr);
        assert(*(uptr2.get()) == 1.61f);
    }

    std::cout << "UniqPtr OK" << std::endl;
}

void loadTestUnqPtr(int objectCount) {
    UnqPtr<int>* ptrs = new UnqPtr<int>[objectCount];
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < objectCount; ++i) {
        UnqPtr<int> p(new int(10));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects UnqPtr for " << duration.count() << " seconds." << std::endl;

    delete[] ptrs;
}

void loadTestStdUniquePtr(int objectCount) {
    std::unique_ptr<int>* ptrs = new std::unique_ptr<int>[objectCount];
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < objectCount; ++i) {
        std::unique_ptr<int> p = std::make_unique<int>(5);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Create " << objectCount << " objects std::unique_ptr for " << duration.count() << " seconds." << std::endl;

    delete[] ptrs;
}

#pragma once

#include <iostream>
#include <cassert>
#include <chrono> 
#include <memory> 
#include <vector> 
#include <string>

//Мои инклуды:

#include "UnqPtr.h"
#include "ShrdPtr.h"
#include "MsPtr.h"
#include "MemorySpan.h"

void testMemorySpan();
int testMsPtr();

void testShrdPtr();
void loadTestShrdPtr(int objectCount);
void loadTestStdSharedPtr(int objectCount);

void testUnqPtr();
void loadTestUnqPtr(int objectCount);
void loadTestStdUniquePtr(int objectCount);

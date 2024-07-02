#ifndef __PREHEADER_H__
#define __PREHEADER_H__

#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <array>

// #include <stdexcept>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#ifdef MEMORY_CHECK
struct MemoryTracker {
    uint32_t allocated = 0;
    uint32_t deallocated = 0;

    uint32_t memoryInUse() const {
        return allocated - deallocated;
    }
};

static MemoryTracker memory;

void* operator new(size_t size) {
    memory.allocated += size;
    return malloc(size);
}

void operator delete(void* memoryBlock, size_t size) {
    memory.deallocated += size;
    free(memoryBlock);
}
#endif


#endif // __PREHEADER_H__
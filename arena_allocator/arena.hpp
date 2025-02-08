#pragma once
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

class arena_allocator;
void print_mem_of_allocator(arena_allocator& arena);
void log_allocator(arena_allocator& arena);

class arena_allocator {
private:
    char* memory_ptr;
    size_t capacity; // max size
    size_t offset; // current pointer in arena

public:
    explicit arena_allocator(size_t size) : capacity{size}, offset{0} {
        memory_ptr = static_cast<char*>(std::malloc(capacity));
        if (!memory_ptr) throw std::bad_alloc();
    }

    ~arena_allocator() {
        if (memory_ptr == nullptr) return;
        std::free(memory_ptr);
    }

    void deinit() {
        if (memory_ptr == nullptr) return; 
        
        std::free(memory_ptr);
        memory_ptr = nullptr;
    }

    void init(size_t bytes) {
        if (memory_ptr != nullptr) return;

        memory_ptr = static_cast<char*>(std::malloc(bytes));
        capacity = bytes;
        offset = 0;

        if (!memory_ptr) throw std::bad_alloc();
        
    }

    void init(size_t bytes, size_t cap) {
        if (memory_ptr != nullptr) return;

        memory_ptr = static_cast<char*>(std::malloc(bytes));
        capacity = cap;
        offset = 0;

        if (!memory_ptr) throw std::bad_alloc();
        
    }

    void free() {
        offset = 0;
    }

    void* alloc(size_t size) {
        if (offset + size > capacity) throw std::bad_alloc();

        void* ptr = memory_ptr + offset;
        offset += size;

        return ptr;
    }

    size_t used_size() {
        return offset;
    }
    size_t cap() {
        return capacity;
    }

    static void memset(arena_allocator& self, char z) {
        for (size_t i = 0; i < self.cap(); i++) self.memory_ptr[i] = z;
    }

    friend void print_mem_of_allocator(arena_allocator&);
    friend void log_allocator(arena_allocator&);
};


void print_mem_of_allocator(arena_allocator& arena) {
    std::cout << "mem { " << std::endl;
    for (size_t i = 0; i < arena.used_size(); i++) {
        std::cout << "\t" << static_cast<int>(arena.memory_ptr[i]) << ", ";
    }
    std::cout << std::endl << "}" << std::endl;

}

void log_allocator(arena_allocator& arena) {
    std::cout << "capacity: " << arena.cap() << std::endl;
    std::cout << "offset: " << arena.used_size() << std::endl;

    print_mem_of_allocator(arena);
}
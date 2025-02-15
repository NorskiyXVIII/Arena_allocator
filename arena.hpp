#pragma once
#include <cstdlib>
#include <iostream>
namespace arena {
    class allocator;
    void print_arena_bytes(const allocator& arena);


    class allocator {
    private:
        char* memory = nullptr;
        size_t cap = 0, offset = 0;
    public:
        allocator(void* mem, size_t cap, size_t offset = 0) : cap{cap}, offset{offset} {
            if (mem == nullptr || mem == 0) {
                throw "mem = nullptr not allowed";
            }

            this->memory = (char*)mem;
        }
        allocator(allocator& alloc) {
            this->memory = alloc.memory;
            this->cap    = alloc.cap;
            this->offset = alloc.offset;

            alloc.memory = nullptr;
            alloc.cap    = 0;
            alloc.offset = 0;
        }
        allocator(size_t cap) : cap{cap} {
            memory = static_cast<char*>(std::malloc(cap));
            if (memory == 0) {
                throw "allocate error";
            }
        }
        allocator() {}

        void init(size_t cap) {
            this->cap = cap;

            memory = static_cast<char*>(std::malloc(cap));
            if (memory == 0) {
                throw "allocate error";
            }
        }
        void init(allocator& alloc) {
            this->memory = alloc.memory;
            this->cap    = alloc.cap;
            this->offset = alloc.offset;

            alloc.memory = nullptr;
            alloc.cap    = 0;
            alloc.offset = 0;
        }
        void init(void* mem, size_t cap, size_t offset = 0) {
            this->cap    = cap;
            this->offset = 0;

            if (mem == nullptr || mem == 0) {
                throw "mem = nullptr not allowed";
            }

            this->memory = (char*)mem;
        }

        void* alloc(size_t sz) {
            if (offset + sz > cap) {
                throw "bad alloc in arena";
            }

            void* pt = memory + offset;
            offset += sz;

            return pt;
        }

        void free() {
            offset = 0;
        }

        void free_arena() {
            offset = 0;
            cap = 0;
            std::free(memory);
            memory = nullptr;
        }

        size_t get_size() const {
            return offset;
        }
        size_t get_capacity() const {
            return cap;
        }
        char* get_ptr() const {
            return memory;
        }

        void resize_arena(size_t capacity) {
            free_arena();
            init(capacity);
        }

        ~allocator() {
            if (memory == nullptr) return;
            std::free(memory);
            memory = nullptr;
        }
    
    };

    void print_arena_bytes(const allocator& arena) {

        if (arena.get_size() <= 15) std::printf("{");
        else                        std::printf("{\n");

        for (int i = 0; i < arena.get_size(); i++) {
            if (i == 0) std::printf("\t");
            else if (i % 20 == 0) std::printf("\n\t");

            std::printf("%d", (char)arena.get_ptr()[i]);
            if (i < arena.get_size() - 1 ) std::printf(", ");
        }
        
        if (arena.get_size() >= 15) std::printf("\n");
        std::printf("}\n");
    }


}

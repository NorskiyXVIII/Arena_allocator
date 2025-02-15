#include <iostream>
#include <stdexcept>
#include "arena.hpp"




int main() {
    setlocale(LC_ALL, "Rus");
    try {
        arena::allocator arena{1024};
        arena::print_arena_bytes(arena);

        int* x = (int*)arena.alloc(4);
        *x = 12894;
        std::cout << *x << std::endl;


        int* y = (int*)arena.alloc(sizeof(int) * 25);
        for (int i = 0; i < 25; i++) {
            y[i] = i * 10;
        }
        arena::print_arena_bytes(arena);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}


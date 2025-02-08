#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>
#include <vector>
#include "arena.hpp"
#include <clocale>




int main() {
    setlocale(LC_ALL, "Rus");
    try {
        arena_allocator arena{1024};
        int* my_array = static_cast<int*>(arena.alloc(sizeof(int) * 10));
        short* my_array2 = static_cast<short*>(arena.alloc(sizeof(short) * 256));
        arena_allocator::memset(arena, 'x');
        for (int i = 0; i < 10; i++) my_array[i] = i * i;
        //for (int i = 0; i < 10; i++) std::cout << my_array[i] << std::endl;
        
        for (int i = 0; i < 256; i++) my_array2[i] = i * 10;
        //for (int i = 0; i < 512; i++) std::cout << my_array2[i] << std::endl;
        arena.free();
        log_allocator(arena);
        
        arena.deinit();
        /*log_allocator(arena);
        arena.init(2048);
        log_allocator(arena);
        */
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}

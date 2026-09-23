#include <cstdint>

inline uint64_t expand(uint64_t input, uint32_t scale) {
    uint64_t result = 0;
    uint32_t i = 0;
    while(i*scale < 64)
    {
        if(input & (1ULL << i))
        {
            result |= (1ULL << (i * scale));
        }
        i++;
    }

    return result;  
}

inline uint64_t morton3d(uint64_t x, uint64_t y, uint64_t z){
    return  expand(x, 3) | (expand(y, 3) << 1) | (expand(z, 3) << 2);
}

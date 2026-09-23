#include <iostream>  
#include <list>      
#include <random>  
#include "timer.h"

constexpr size_t SIZE = 16000000;
int int_SIZE = 16000000;

int main() { 
    Timer timer;
    std::mt19937_64 rng(0);
    
    std::vector<uint64_t> vec1;
    vec1.resize(SIZE);
    rng.seed(0);
    timer.restart();
    for (int row = 0; row < 4000; ++row) {
        for(int col = 0; col < 4000; ++col){
            vec1[row*4000 + col] = rng();
        }
    }
    std::cout << "Vec1 insert:              " << timer.click<Timer::Micros>() << " us\n";
    
    uint64_t arraySum = 0;
    timer.restart();
    for (int row = 0; row < 4000; ++row) {
        for(int col = 0; col < 4000; ++col){
            arraySum+=vec1[row*4000 + col];
        }
    }
    std::cout << "Vec1 sum:   " << arraySum << ", " << timer.click<Timer::Micros>() << " us\n";

    std::vector<uint64_t> vec2;
    vec2.resize(SIZE);
    rng.seed(0);
    timer.restart();
    for (int col = 0; col < 4000; ++col) {
        for(int row = 0; row < 4000; ++row){
            vec2[row*4000 + col] = rng();
        }
    }
    std::cout << "Vec2 (col) insert:              " << timer.click<Timer::Micros>() << " us\n";
    
    uint64_t arraySum2 = 0;
    timer.restart();
    for (int col = 0; col < 4000; ++col) {
        for(int row = 0; row < 4000; ++row){
            arraySum2+=vec2[row*4000 + col];
        }
    }

    std::cout << "Vec2 (col) sum:   " << arraySum2 << ", " << timer.click<Timer::Micros>() << " us\n";


}

#include <iostream>  
#include <list>      
#include <random>  
#include "timer.h"

constexpr size_t SIZE = 16000000;
int int_SIZE = 16000000;

int main() { 
    Timer timer;
    std::mt19937_64 rng(0);

    std::list<uint64_t> list;
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; ++i) {
        list.push_back(rng());
    }
    std::cout << "list insert:              " << timer.click<Timer::Micros>() << " us\n";
    
    uint64_t listSum = 0;
    timer.restart();
    for (uint64_t x : list) {
        listSum += x;
    }
    std::cout << "list sum:   " << listSum << ", " << timer.click<Timer::Micros>() << " us\n";

    std::list<uint64_t> list2;
    rng.seed(0);
    timer.restart();
    int y = 0;
    int r = 0;
    while (y + 4000*r < int_SIZE) {
        list2.push_back(rng());
        if(y + 4000*(r+1) < int_SIZE){
            r++;
        }
        else if((y+1) == 4000) {
            break;
        }
        else{
            r=0;
            y++;
        }
    }
    std::cout << "Col list:              " << timer.click<Timer::Micros>() << " us\n";
    
    uint64_t listSum2 = 0;
    timer.restart();
    y = 0;
    r = 0;
    while (y + 4000*r < int_SIZE) {
        listSum2 += (y + 4000*r);
        if(y + 4000*(r+1) < int_SIZE){
            r++;
        }
        else if((y+1) == 4000) {
            break;
        }
        else{
            r=0;
            y++;
        }
    }
    std::cout << "list2 sum:   " << listSum2 << ", " << timer.click<Timer::Micros>() << " us\n";


}

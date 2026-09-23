#include "p2a.h"
#include <iostream> 
#include <random>  
#include <cassert>
#include "timer.h"

constexpr size_t SIZE = 16777216;

int main() { 
    Timer timer;
    std::mt19937_64 rng(0);
    
    std::vector<uint64_t> vecA;
    vecA.resize(SIZE);
    rng.seed(0);
    timer.restart();
    for (int x = 0; x < 256; ++x) {
        for(int y = 0; y < 256; ++y){
            for(int z = 0; z < 256; ++z){
                vecA[x*256*256 + y*256 +z ] = rng();
            } 
        }
    }

    std::vector<uint64_t> vecB;
    vecB.resize(SIZE);

    for (int x = 0; x < 256; ++x) {
        for (int y = 0; y < 256; ++y) {
            for (int z = 0; z < 256; ++z) {
                vecB[morton3d(x, y, z)] = vecA[x*256*256 + y*256 + z];
            }
        }
    }

    std::vector<uint64_t> vecKa;
    vecKa.resize(64);

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            for (int z = 0; z < 4; ++z) {
                vecKa[x*4*4 + y*4 +z ] = x+y+z;
            }
        }
    }

    std::vector<uint64_t> vecKb;
    vecKb.resize(64);

    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            for (int z = 0; z < 4; ++z) {
                vecKb[morton3d(x, y, z)] = vecKa[x*4*4 + y*4 + z];
            }
        }
    }

    uint64_t sum = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    std::vector<uint64_t> rmao;
    rmao.resize(64*64*64);
    timer.restart();
    for (int sx = 0; sx < 64; ++sx) {
        for (int sy = 0; sy < 64; ++sy) {
            for (int sz = 0; sz < 64; ++sz) {
                sum = 0;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        for (int w = 0; w < 4; ++w) {
                            x = sx*4 +i;
                            y = sy*4 +j;
                            z = sz*4 +w;
                            sum+= vecA[x*256*256 + y*256 +z ]*vecKa[i*4*4 + j*4+ w];
                        }
                    }
                }
                rmao[sx*64*64 + sy*64 + sz] = sum;
            }
        }
    }
    std::cout << "Ka convolution:              " << timer.click<Timer::Micros>() << " us\n";


    x = 0;
    y = 0;
    z = 0;
    std::vector<uint64_t> moa;
    moa.resize(64*64*64);
    timer.restart();
    for (int sx = 0; sx < 64; ++sx) {
        for (int sy = 0; sy < 64; ++sy) {
            for (int sz = 0; sz < 64; ++sz) {
                sum = 0;
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        for (int w = 0; w < 4; ++w) {
                            x = sx*4 +i;
                            y = sy*4 +j;
                            z = sz*4 +w;
                            sum += vecB[morton3d(x, y, z)] * vecKb[morton3d(i , j, w)];
                        }
                    }
                }
                moa[morton3d(sx, sy, sz)] = sum;
            }
        }
    }
    std::cout << "Kb convolution:              " << timer.click<Timer::Micros>() << " us\n";
    for (int sx = 0; sx < 64; ++sx) {
        for (int sy = 0; sy < 64; ++sy) {
            for (int sz = 0; sz < 64; ++sz) {
                assert(rmao[sx*64*64 + sy*64 + sz] == moa[morton3d(sx,sy,sz)]);
            }
        }
    }


    
}
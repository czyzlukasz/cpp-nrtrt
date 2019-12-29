//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_RANDGEN_HPP
#define CPP_NRTRT_RANDGEN_HPP

#include <stack>
#include <array>
#include <iostream>
#include <random>

struct RandGen {
    static void initRandGen(){
        for(; itemsInArray < stack.size(); ++itemsInArray){
            stack.at(itemsInArray) = dist(engine);
        }
    }

    static inline float getRandom(){
        return dist(engine);
//        static constexpr size_t halfSize = stack.size() / 2;
//        if(itemsInArray < halfSize){
//            replenishStack();
//        }
//        return stack.at(--itemsInArray);
    }

private:
    //TODO: do that in another thread
    static inline void replenishStack(){
        for(; itemsInArray < stack.size(); ++itemsInArray){
            stack.at(itemsInArray) = dist(engine);
        }
    }

    static std::array<float, 1000> stack;
    static size_t itemsInArray;
    static std::random_device rd;
    static std::mt19937 engine;
    static std::uniform_real_distribution<float> dist;
};

#endif //CPP_NRTRT_RANDGEN_HPP

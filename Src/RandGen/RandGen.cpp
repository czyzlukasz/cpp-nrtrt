//
// Created by krawacik3 on 28.12.2019.
//

#include <RandGen.hpp>

std::array<float, 1000> RandGen::stack = {};
size_t RandGen::itemsInArray = 0;
std::random_device RandGen::rd{};
std::mt19937 RandGen::engine(rd());
std::uniform_real_distribution<float> RandGen::dist(0.f, 1.f);

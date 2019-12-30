//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_WORKER_HPP
#define CPP_NRTRT_WORKER_HPP


#include <World.hpp>
#include <Pixel.hpp>
#include <queue>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <variant>

struct Worker {
    explicit Worker(const World& world) : world(world){
    }

    void addRay(const Ray& ray, uint pixelId){
        raysToProcess.push_back(std::make_pair(ray, pixelId));
    }

    void shuffle(){
        // static_assert(std::is_swappable<Ray>());
        // std::random_shuffle(raysToProcess.begin(), raysToProcess.end());
    }

    void processRays(std::array<Pixel, 160000>& container){
        while(!raysToProcess.empty()){
            const auto& rayToProcess = raysToProcess.back();
            const auto result = getColorAtRay(rayToProcess.first);
            if(auto pixel = std::get_if<Pixel>(&result)){
                container.at(rayToProcess.second) = *pixel;
            }
            raysToProcess.pop_back();
        }
    }

private:
    [[nodiscard]] std::variant<Pixel, Light> getColorAtRay(const Ray& ray, uint recursionDepth = 0) const;

    [[nodiscard]] inline glm::vec3 getReflectionVector(const auto& objectPtr, const glm::vec3& collisionPoint, const Ray& ray) const{
        return ray.direction - 2.f * glm::dot(objectPtr->normalAtPoint(collisionPoint), ray.direction) * objectPtr->normalAtPoint(collisionPoint);
    }

//    [[nodiscard]] inline float getDirectLuminosity(const glm::vec3& point, const glm::vec3& normal) const;

    //World is read-only
    const World& world;
    std::unordered_multimap<uint, Pixel> processedPixels;
    std::vector<std::pair<Ray, uint>> raysToProcess;
};


#endif //CPP_NRTRT_WORKER_HPP

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

constexpr uint spp = 64;

struct SuperPixel{
    float r = 0, g = 0, b = 0;
};

struct Worker {
    explicit Worker(const World& world) : world(world){
    }

    void addRay(const Ray& ray, uint pixelId){
        raysToProcess.emplace_back(ray, pixelId);
    }

    void shuffle(){
        // static_assert(std::is_swappable<Ray>());
        // std::random_shuffle(raysToProcess.begin(), raysToProcess.end());
    }

    void processRays(std::array<std::vector<Pixel<>>, 160000>& container){
        while(!raysToProcess.empty()){
            const auto& rayToProcess = raysToProcess.back();
            for(uint idx = 0; idx < spp; ++idx) {
                container.at(rayToProcess.second).push_back(getColorAtRay(rayToProcess.first));
            }
            raysToProcess.pop_back();
        }
    }

private:
    [[nodiscard]] Pixel<> getColorAtRay(const Ray &ray, uint recursionDepth = 0, std::vector<std::unique_ptr<IObject>>::const_iterator parent = std::vector<std::unique_ptr<IObject>>::const_iterator()) const;

    [[nodiscard]] inline glm::vec3 getReflectionVector(const auto& objectPtr, const glm::vec3& collisionPoint, const Ray& ray) const{
        return ray.direction - 2.f * glm::dot(objectPtr->normalAtPoint(collisionPoint), ray.direction) * objectPtr->normalAtPoint(collisionPoint);
    }

    //World is read-only
    const World& world;
    std::vector<std::pair<Ray, uint>> raysToProcess;
};


#endif //CPP_NRTRT_WORKER_HPP

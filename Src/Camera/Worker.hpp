//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_WORKER_HPP
#define CPP_NRTRT_WORKER_HPP


#include <World.hpp>
#include <Pixel.hpp>
#include <queue>
#include <functional>


struct Worker {
    explicit Worker(const World& world) : world(world){
    }

    void addRay(const Ray& ray, uint pixelId){
        raysToProcess.push(std::make_pair(ray, pixelId));
    }

    void processRays(std::array<Pixel, 160000>& container){
        while(!raysToProcess.empty()){
            const auto& rayToProcess = raysToProcess.front();
            container.at(rayToProcess.second) = getColorAtRay(rayToProcess.first);
            raysToProcess.pop();
        }
    }

private:
    [[nodiscard]] Pixel getColorAtRay(const Ray& ray, uint recursionDepth = 0) const;

    [[nodiscard]] inline glm::vec3 getReflectionVector(const auto& objectPtr, const glm::vec3& collisionPoint, const Ray& ray) const{
        return ray.direction - 2.f * glm::dot(objectPtr->normalAtPoint(collisionPoint), ray.direction) * objectPtr->normalAtPoint(collisionPoint);
    }

    [[nodiscard]] inline float getDirectLuminosity(const glm::vec3& point, const glm::vec3& direction) const;

    //World is read-only
    const World& world;
    std::queue<std::pair<Ray, uint>> raysToProcess;
};


#endif //CPP_NRTRT_WORKER_HPP

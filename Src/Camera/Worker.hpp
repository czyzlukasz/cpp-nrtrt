//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_WORKER_HPP
#define CPP_NRTRT_WORKER_HPP


#include <World.hpp>
#include <Pixel.hpp>

struct Worker {
    explicit Worker(const World& world) : world(world){
    }

    Pixel getColorAtRay(const Ray& ray, uint recursionDepth = 0) const;

private:
    inline glm::vec3 getReflectionVector(const auto& objectPtr, const glm::vec3& collisionPoint, const Ray& ray) const{
        return ray.direction - 2.f * glm::dot(objectPtr->normalAtPoint(collisionPoint), ray.direction) * objectPtr->normalAtPoint(collisionPoint);
    }

    //World is read-only
    const World& world;
};


#endif //CPP_NRTRT_WORKER_HPP

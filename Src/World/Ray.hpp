//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_RAY_HPP
#define CPP_NRTRT_RAY_HPP

#include <glm/vec3.hpp>


struct Ray{
    const glm::vec3 startPoint;
    const glm::vec3 direction;

    inline glm::vec3 getPoint(float t) const{
        return startPoint + direction * t;
    }
    Ray(const Ray& other) = default;
    Ray(Ray&& other) noexcept = default;
    Ray& operator=(const Ray& other) = default;
    Ray& operator=(Ray&& other) noexcept = default;
};

#endif //CPP_NRTRT_RAY_HPP

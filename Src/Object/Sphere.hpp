//
// Created by krawacik3 on 03.01.2020.
//

#ifndef CPP_NRTRT_SPHERE_HPP
#define CPP_NRTRT_SPHERE_HPP

#include <IObject.hpp>
#include <glm/geometric.hpp>
#include <algorithm>


struct Sphere : public IObject{
    Sphere(const glm::vec3& center, const float radius, Pixel<> color, float diffuseFactor, bool light = false)
        : center(center), radius(radius), diffuseFactor(diffuseFactor), color(color), light(light){

    }

    [[nodiscard]] inline glm::vec3 getCenter() const final{
        return center;
    }
    [[nodiscard]] inline float getRadius() const final{
        return radius;
    }

    //TODO: unused for now
    [[nodiscard]] inline bool canCollide(const Ray& ray) const final{
        const glm::vec3 distance = ray.startPoint - center;
        const float doubleDirection = glm::dot(ray.direction, ray.direction);
        const float b = 2.f * glm::dot(distance, ray.direction);
        const float c = glm::dot(distance, distance) - radius * radius;
        //b^2 - 4ac
        const float discriminant = b * b - 4 * doubleDirection * c;
        return discriminant > 0.f;
    }

    [[nodiscard]] inline glm::vec3 collisionPoint(const Ray& ray) const final{
        const glm::vec3 distance = ray.startPoint - center;
        const float doubleDirection = glm::dot(ray.direction, ray.direction);
        const float b = 2.f * glm::dot(distance, ray.direction);
        const float c = glm::dot(distance, distance) - radius * radius;
        //b^2 - 4ac
        const float discriminant = b * b - 4 * doubleDirection * c;
        const float t1 = (-b - std::sqrt(discriminant)) / (2.f * doubleDirection);
        const float t2 = (-b + std::sqrt(discriminant)) / (2.f * doubleDirection);
        if(t1 > 0.f && t2 <= 0.f){
            return ray.getPoint(t1);
        }
        else if(t1 <= 0.f && t2 > 0.f){
            return ray.getPoint(t2);
        }
        else if(t1 > 0.f && t2 > 0.f){
            return ray.getPoint(std::min(t1, t2));
        }
        else{
            return glm::vec3();
        }
    }

    [[nodiscard]] inline glm::vec3 normalAtPoint(const glm::vec3& point) const final{
        return glm::normalize(point - center);
    }

    [[nodiscard]] inline Pixel<> getColor() const final{
        return color;
    }
    [[nodiscard]] inline float getDiffuseFactor() const final{
        return diffuseFactor;
    }

    [[nodiscard]] inline bool isLight() const final{
        return light;
    }
    const glm::vec3 center;
    const float radius, diffuseFactor;
    const Pixel<> color;
    const bool light;
};


#endif //CPP_NRTRT_TRIANGLE_HPP

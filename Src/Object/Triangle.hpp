//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_TRIANGLE_HPP
#define CPP_NRTRT_TRIANGLE_HPP

#include <IObject.hpp>
#include <glm/geometric.hpp>
#include <algorithm>


struct Triangle : public IObject{
    Triangle(const glm::vec3 a, const glm::vec3 b, const glm::vec3 c) : a(a), b(b), c(c){
        const glm::vec3 sideA  = a - c;
        const glm::vec3 sideB  = b - c;
        //Calculating normal of triangle requires cross product of its two sides
        normal = glm::normalize(glm::cross(sideA, sideB));

        //Circumcenter, per https://en.wikipedia.org/wiki/Circumscribed_circle
        const float lengthA = glm::length(c - b);
        const float lengthB = glm::length(c - a);
        const float lengthC = glm::length(b - a);
        static const auto sqr = [](const float m) -> float {return std::pow(m, 2);};
        center = (sqr(lengthA) * (sqr(lengthB) + sqr(lengthC) - sqr(lengthA)) * a +
                  sqr(lengthB) * (sqr(lengthC) + sqr(lengthA) - sqr(lengthB)) * b +
                  sqr(lengthC) * (sqr(lengthA) + sqr(lengthB) - sqr(lengthC)) * c)
            / //---------------------------------------------------------------------//
                 (sqr(lengthA) * (sqr(lengthB) + sqr(lengthC) - sqr(lengthA)) +
                  sqr(lengthB) * (sqr(lengthC) + sqr(lengthA) - sqr(lengthB)) +
                  sqr(lengthC) * (sqr(lengthA) + sqr(lengthB) - sqr(lengthC)));

        //Radius is the biggest distance from center to a, b or c
        radius = std::max({glm::length(a - center), glm::length(b - center), glm::length(c - center)});
    }

    [[nodiscard]] inline glm::vec3 getCenter() const final{
        return center;
    }
    [[nodiscard]] inline float getRadius() const final{
        return radius;
    }

    //TODO: unused for now
    [[nodiscard]] inline bool canCollide(const Ray& ray) const final{
        return true;
    }

    [[nodiscard]] inline glm::vec3 collisionPoint(const Ray& ray) const final{

    }

    [[nodiscard]] inline glm::vec3 normalAtPoint(const glm::vec3& point) const final{
        return normal;
    }

private:
    const glm::vec3 a, b, c;
    glm::vec3 normal;
    glm::vec3 center;
    float radius;
};


#endif //CPP_NRTRT_TRIANGLE_HPP

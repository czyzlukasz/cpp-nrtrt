//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_IOBJECT_HPP
#define CPP_NRTRT_IOBJECT_HPP

#include <glm/vec3.hpp>
#include <Ray.hpp>

struct IObject{
    [[nodiscard]] virtual inline glm::vec3 getCenter() const = 0;
    [[nodiscard]] virtual inline float getRadius() const = 0;
    [[nodiscard]] virtual inline bool canCollide(const Ray& ray) const = 0;
    [[nodiscard]] virtual inline glm::vec3 collisionPoint(const Ray& ray) const = 0;
    [[nodiscard]] virtual inline glm::vec3 normalAtPoint(const glm::vec3& point) const = 0;
};

#endif //CPP_NRTRT_IOBJECT_HPP

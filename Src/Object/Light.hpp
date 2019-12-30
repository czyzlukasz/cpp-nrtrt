//
// Created by krawacik3 on 29.12.2019.
//

#ifndef CPP_NRTRT_LIGHT_HPP
#define CPP_NRTRT_LIGHT_HPP

#include <Triangle.hpp>


struct Light : public Triangle{
    Light(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, Pixel color, float intensivity)
        : Triangle(a, b, c, color, 1.f), intensivity(intensivity){
    }

    [[nodiscard]] inline bool isLight() const final{
        return true;
    }

    const float intensivity;
};

#endif //CPP_NRTRT_LIGHT_HPP

//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_RANDGEN_HPP
#define CPP_NRTRT_RANDGEN_HPP

#include <stack>
#include <array>
#include <iostream>
#include <random>
#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

struct RandGen {
    static inline float getRandom(){
        return dist(engine);
    }

    static inline glm::vec3 deviateVector(glm::vec3 vector, float factor){
        //Generate random vector around z axis within cone of angle factor * pi
        const float angle = factor * M_PI / 2.f;
        //std::cout << angle << std::endl;
        const float cosTheta = std::cos(angle);
        //std::cout << cosTheta << std::endl;
        //z is in range [cosTheta, 1];
        const float z = (1 - cosTheta) * getRandom() + cosTheta;
        //std::cout << z << std::endl;
        //Random angle
        const float randomPhi = getRandom() * 2.f * M_PI;
        const float cosPhi = std::cos(randomPhi);
        const float sinPhi = std::sin(randomPhi);
        //std::cout << "randomPhi" << randomPhi << "cosPhi" << cosPhi << "sinPhi" << sinPhi << std::endl;

        const float sqr = std::sqrt(1 - std::pow(z, 2));
        //std::cout << sqr << std::endl;
        glm::vec3 randomVector, zVector;
        if(vector.z != 1.f){
            randomVector = glm::vec3(sqr * cosPhi, sqr * sinPhi, z);   
            zVector = glm::vec3(0, 0, 1);
        }
        else{
            randomVector = glm::vec3(z, sqr * cosPhi, sqr * sinPhi);   
            zVector = glm::vec3(1, 0, 0);
        }
        const glm::vec3 crossProduct = glm::cross(zVector, vector);
        //std::cout << crossProduct.x << " " << crossProduct.y << " " << crossProduct.z << std::endl;
        const float angleToRotate = glm::angle(zVector, vector);
        //std::cout << angleToRotate << std::endl;
        return glm::normalize(glm::rotate(randomVector, angleToRotate, crossProduct));
    }

private:
    //TODO: do that in another thread
    static inline void replenishStack(){
        for(; itemsInArray < stack.size(); ++itemsInArray){
            stack.at(itemsInArray) = dist(engine);
        }
    }

    static std::array<float, 1000> stack;
    static size_t itemsInArray;
    static std::random_device rd;
    static std::mt19937 engine;
    static std::uniform_real_distribution<float> dist;
};

#endif //CPP_NRTRT_RANDGEN_HPP

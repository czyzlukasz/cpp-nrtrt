//
// Created by krawacik3 on 08.01.2020.
//

#include <cmath>
#include <Sphere.hpp>
#include <glm/gtx/vector_angle.hpp>


struct TransparentSphere : public Sphere{
    TransparentSphere(const glm::vec3& center, const float radius, Pixel<> color, float indexOfRefraction)
        : Sphere(center, radius, color, 0.f, false),
          indexOfRefraction(indexOfRefraction)
        {}

    [[nodiscard]] Ray outputRay(const glm::vec3 sphereCollisionPoint, const glm::vec3& direction) const{
        const Ray internalRay = calculateInternalRay(sphereCollisionPoint, direction);
        return internalToOutputRay(internalRay);
    }

    //TODO: for UTs
//private:
    [[nodiscard]] inline Ray calculateInternalRay(const glm::vec3 sphereCollisionPoint, const glm::vec3& direction) const{
        //Calculate angle between normal and direction
        const glm::vec3 tempNormal = normalAtPoint(sphereCollisionPoint);
        const glm::vec3 normal = glm::dot(tempNormal, direction) < 0.f ? tempNormal : - tempNormal;
        const float angle = glm::angle(-normal, direction);

        //Calculate internal ray
        const glm::vec3 crossProduct = glm::cross(direction, normal);
        const float sinAngle = std::sin(angle);
        const float internalAngle = std::asin(1.f / indexOfRefraction * sinAngle);
        const glm::vec3 internalRayDirection = glm::normalize(glm::rotate(-normal, internalAngle, crossProduct));
        const Ray internalRay{sphereCollisionPoint, internalRayDirection};
        return internalRay;
    }

    [[nodiscard]] inline Ray internalToOutputRay(const Ray& ray) const{
        const glm::vec3 sphereCollisionPoint = collisionPoint(ray);
        const glm::vec3 tempNormal = normalAtPoint(sphereCollisionPoint);
        const glm::vec3 normal = glm::dot(ray.direction, tempNormal) > 0.f ? tempNormal : - tempNormal;
        const float angle = glm::angle(ray.direction, normal);

        const glm::vec3 crossProduct = glm::cross(ray.direction, normal);
        if(isTotalInternalReflection(angle)){
            const float outputAngle = -std::asin(indexOfRefraction * std::sin(angle) - M_PI_2);
            const glm::vec3 outputRayDirection = glm::normalize(glm::rotate(-normal, outputAngle, crossProduct));
            return internalToOutputRay(Ray{sphereCollisionPoint, outputRayDirection});
        }
        else{
            const float outputAngle = -std::asin(indexOfRefraction * std::sin(angle));
            const glm::vec3 outputRayDirection = glm::normalize(glm::rotate(normal, outputAngle, crossProduct));
            return Ray{sphereCollisionPoint, outputRayDirection};
        }
    }

    inline bool isTotalInternalReflection(float angle) const{
        return std::asin(indexOfRefraction) <= angle;
    }

    const float indexOfRefraction;
};
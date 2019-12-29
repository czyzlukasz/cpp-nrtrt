//
// Created by krawacik3 on 28.12.2019.
//

#include <Worker.hpp>
#include <Pixel.hpp>

Pixel Worker::getColorAtRay(const Ray& ray, uint recursionDepth) const{
    for(const auto& objectPtr : world.getObjects()){
        if(objectPtr->canCollide(ray)){
            static constexpr glm::vec3 zeroVector = glm::vec3();
            //TODO: change collisionPoint to std::option
            const glm::vec3 collisionPoint = objectPtr->collisionPoint(ray);
            if( collisionPoint != zeroVector){
                const glm::vec3 reflectionVector = getReflectionVector(objectPtr, collisionPoint, ray);
                return objectPtr->getColor() * getDirectLuminosity(collisionPoint, reflectionVector);
            }
        }
    }
    return Pixel();
}

inline float Worker::getDirectLuminosity(const glm::vec3& point, const glm::vec3& direction) const{
    float result = 0.f;
    for(const Light& light : world.getLights()){
        const glm::vec3 lightDirection = glm::normalize(light.position - point);
        const float dotProduct = glm::dot(lightDirection, glm::normalize(direction));
        result += dotProduct > 0.f ? dotProduct : 0.f;
    }
    return result;
}
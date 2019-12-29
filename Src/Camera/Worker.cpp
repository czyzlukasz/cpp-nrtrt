//
// Created by krawacik3 on 28.12.2019.
//

#include <Worker.hpp>
#include <Pixel.hpp>
#include <limits>


Pixel Worker::getColorAtRay(const Ray& ray, uint recursionDepth) const{
    float minimalDistance = std::numeric_limits<float>::max();
    size_t objectIdx = std::numeric_limits<size_t>::max();
    glm::vec3 closestCollisionPoint = glm::vec3();
    for(size_t idx = 0; idx < world.getObjects().size(); ++idx){
        const auto& objectPtr = world.getObjects().at(idx);
        if(objectPtr->canCollide(ray)){
            static constexpr glm::vec3 zeroVector = glm::vec3();
            //TODO: change collisionPoint to std::option
            const glm::vec3 collisionPoint = objectPtr->collisionPoint(ray);
            if( collisionPoint != zeroVector){
                const float distance = glm::length(collisionPoint);
                if(distance < minimalDistance){
                    minimalDistance = distance;
                    closestCollisionPoint = collisionPoint;
                    objectIdx = idx;
                }
            }
        }
    }
    if(objectIdx < world.getObjects().size()){
        const glm::vec3 reflectionVector = getReflectionVector(world.getObjects().at(objectIdx), closestCollisionPoint, ray);
        return world.getObjects().at(objectIdx)->getColor() * getDirectLuminosity(closestCollisionPoint, reflectionVector);
    }
    else {
        return Pixel();
    }
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
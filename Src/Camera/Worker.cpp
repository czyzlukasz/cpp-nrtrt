//
// Created by krawacik3 on 28.12.2019.
//

#include <Worker.hpp>
#include "Pixel.hpp"


Pixel Worker::getColorAtRay(const Ray& ray, uint recursionDepth) const{
    for(const auto& objectPtr : world.getObjects()){
        if(objectPtr->canCollide(ray)){
            static constexpr glm::vec3 zeroVector = glm::vec3();
            //TODO: change collisionPoint to std::option
            const glm::vec3 collisionPoint = objectPtr->collisionPoint(ray);
            if( collisionPoint != zeroVector){
                const glm::vec3 reflectionVector = getReflectionVector(objectPtr, collisionPoint, ray);
                return objectPtr->getColor();
            }
        }
    }
    return Pixel();
}
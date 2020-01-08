//
// Created by krawacik3 on 28.12.2019.
//

#include <Worker.hpp>
#include <Pixel.hpp>
#include <limits>
#include <RandGen.hpp>
#include <TransparentSphere.hpp>


Pixel<> Worker::getColorAtRay(const Ray &ray, uint recursionDepth, std::vector<std::unique_ptr<IObject>>::const_iterator parent) const {
    constexpr uint MAX_RECURSION_DEPTH = 3;
    constexpr glm::vec3 zeroVector = glm::vec3(0,0,0);
    if(recursionDepth > MAX_RECURSION_DEPTH){
        return Pixel<>{0, 0, 0, 255};
    }
    std::vector<std::unique_ptr<IObject>>::const_iterator closestObject;
    float closestDistance = std::numeric_limits<float>::max();
    glm::vec3 closestCollisionPoint;

    for(auto object = world.getObjects().begin(); object < world.getObjects().end(); ++ object){
        const glm::vec3 collisionPoint = (*object)->collisionPoint(ray);
        //Collision occured
        if(collisionPoint != zeroVector){
            if(object == parent){
                continue;
            }
            const float distance = glm::length(ray.startPoint - collisionPoint);
            if(distance < closestDistance && distance > 0.001f){
                closestObject = object;
                closestDistance = distance;
                closestCollisionPoint = collisionPoint;
            }
        }
    }
    //If any object was hit
    if(closestDistance < std::numeric_limits<float>::max()){
        const glm::vec3 tempNormal = (*closestObject)->normalAtPoint(closestCollisionPoint);
        const glm::vec3 normal = glm::dot(tempNormal, ray.direction) < 0.f ? tempNormal : - tempNormal;
        //Check if object itself is light
        if((*closestObject)->isLight()){
            const float importance = - glm::dot(normal, ray.direction);
            //Diffuse factor is used as a light intensivity there
            return (*closestObject)->getColor() * (importance * (*closestObject)->getDiffuseFactor());
        }
        if(const TransparentSphere* transparent = dynamic_cast<TransparentSphere*>((*closestObject).get())){
            if(recursionDepth == 0){
                int x =0;
            }
            const Ray outputRay = transparent->outputRay(closestCollisionPoint, ray.direction);
            return getColorAtRay(outputRay, recursionDepth + 1, closestObject);
        }
        else{
            //Get reflected vector in random position
            const glm::vec3 deviatedVector = RandGen::deviateVector(normal, 1.f);
            const Ray newRay{closestCollisionPoint, deviatedVector};
            const Pixel resultPixel = getColorAtRay(newRay, recursionDepth + 1, closestObject);
            const float importance = glm::abs(glm::dot(normal, deviatedVector));
            const auto objectColor = (*closestObject)->getColor();
            const auto result = resultPixel * (objectColor * importance);
            return result;
        }
    }
    return Pixel<>{0, 0, 0, 255};
}

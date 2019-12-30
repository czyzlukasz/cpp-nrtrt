//
// Created by krawacik3 on 28.12.2019.
//

#include <Worker.hpp>
#include <Pixel.hpp>
#include <limits>
#include <RandGen.hpp>


std::variant<Pixel, Light> Worker::getColorAtRay(const Ray& ray, uint recursionDepth) const{
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
        constexpr uint NUM_OF_SAMPLES = 16;
        if(recursionDepth < 2){
            //SuperPixel is used to cumulate values of all reflected rays
            struct SuperPixel{
                uint r, g, b;
            };
            SuperPixel sPixel{0,0,0};
            for(int sample = 0; sample < NUM_OF_SAMPLES; ++sample){
                const glm::vec3 deviatedVector = RandGen::deviateVector(reflectionVector, world.getObjects().at(objectIdx)->getDiffuseFactor());
                //TODO: check if deviatedVector does point 'outside' shape
                //Check if calculated vector is not over 90 degrees to the normal
                // if(glm::dot(deviatedVector, world.getObjects().at(objectIdx)->normalAtPoint(closestCollisionPoint)) < 0.f){
                //     --sample;
                //     continue;
                // }
                //Check if hit object is light

                const Ray sampleRay = {closestCollisionPoint, deviatedVector};
                const auto samplePixel = getColorAtRay(sampleRay, recursionDepth + 1);
                //Check if hit object is light
                if(const auto light = std::get_if<Light>(&samplePixel)){
                    const Pixel pixel = light->getColor() * glm::dot(world.getObjects().at(objectIdx)->normalAtPoint(closestCollisionPoint), deviatedVector);
                    sPixel.r += pixel.R;
                    sPixel.g += pixel.G;
                    sPixel.b += pixel.B;
                    continue;
                }
                else {
                    const auto pixel = std::get<Pixel>(samplePixel);
                    sPixel.r += pixel.R;
                    sPixel.g += pixel.G;
                    sPixel.b += pixel.B;
                    continue;
                }
            }
            return Pixel{static_cast<sf::Uint8>(sPixel.r / (NUM_OF_SAMPLES)),
                         static_cast<sf::Uint8>(sPixel.g / (NUM_OF_SAMPLES)),
                         static_cast<sf::Uint8>(sPixel.b / (NUM_OF_SAMPLES)),
                         255};
        }
        else{
            return world.getObjects().at(objectIdx)->getColor();
        }
    }
    else {
        return Pixel();
    }
}

//inline float Worker::getDirectLuminosity(const glm::vec3& point, const glm::vec3& normal) const{
//    float result = 0.f;
//    static constexpr glm::vec3 zeroVector = glm::vec3();
//    for(const Light& light : world.getLights()){
//        const glm::vec3 lightDirection = glm::normalize(light.position - point);
//        const Ray reflectionRay{point, lightDirection};
//        bool isCollision = false;
//        for(auto& object : world.getObjects()){
//            const glm::vec3 collisionPoint = object->collisionPoint(reflectionRay);
//            if(glm::length(collisionPoint - point) > 0.1f){
//                // isCollision = true;
//                // break;
//            }
//        }
//        if(!isCollision){
//            const float dotProduct = glm::dot(lightDirection, normal);
//            result += dotProduct > 0.f ? dotProduct : 0.f;
//        }
//    }
//    return result;
//}
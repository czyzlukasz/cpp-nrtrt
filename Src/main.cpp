//
// Created by krawacik3 on 27.12.2019.
//
#include <Camera.hpp>
#include <RandGen.hpp>

int main(){
    RandGen::initRandGen();
    Camera<400, 400, 70> camera;
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-2, -1, -3),
            glm::vec3(0, -1, -3),
            glm::vec3(-1, 1, -5),
            Pixel{200, 200, 0, 255},
            0.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-1, -1, -5),
            glm::vec3(1, -1, -5),
            glm::vec3(0, 1, -5),
            Pixel{0, 200, 200, 255},
            0.0f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -3),
            glm::vec3(3, -1, -6),
            Pixel{0, 200, 0, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -6),
            glm::vec3(-3, -1, -6),
            Pixel{0, 200, 0, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Light>(
            glm::vec3(-5, 5, 1),
            glm::vec3(-7, 3, 1),
            glm::vec3(-3, 3, 1),
            Pixel{0, 200, 0, 255},
            1.f
    ));
//     while(true)
    {
        camera.startRender();
        camera.startRender();
    }
}

//
// Created by krawacik3 on 27.12.2019.
//
#include <Camera.hpp>
#include <RandGen.hpp>

int main(){
    RandGen::initRandGen();
    Camera<400, 400, 70> camera;
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-2, -1, -4),
            glm::vec3(0, -1, -4),
            glm::vec3(-1, 1, -4),
            Pixel{255, 255, 0, 255},
            0.95f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-1, -1, -5),
            glm::vec3(1, -1, -5),
            glm::vec3(0, 1, -5),
            Pixel{0, 255, 255, 255},
            0.05f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -3),
            glm::vec3(3, -1, -6),
            Pixel{0, 255, 0, 255},
            0.1f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -6),
            glm::vec3(-3, -1, -6),
            Pixel{0, 255, 0, 255},
            0.75f
    ));
    camera.getWorld().addObject(std::make_unique<Light>(
            glm::vec3(0, 5, 0),
            glm::vec3(-2, 3, 0),
            glm::vec3(2, 3, 0),
            Pixel{0, 255, 0, 255},
            0.75f
    ));
//     while(true)
    {
        camera.startRender();
        camera.startRender();
    }
}

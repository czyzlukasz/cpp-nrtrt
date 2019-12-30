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
            Pixel{255, 255, 0, 255}
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-1, -1, -5),
            glm::vec3(1, -1, -5),
            glm::vec3(0, 1, -5),
            Pixel{0, 255, 255, 255}
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -3),
            glm::vec3(3, -1, -6),
            Pixel{0, 255, 0, 255}
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, -3),
            glm::vec3(3, -1, -6),
            glm::vec3(-3, -1, -6),
            Pixel{0, 255, 0, 255}
    ));
    camera.getWorld().addLight(Light{glm::vec3{0, 10, -6}, 1.f});
    camera.getWorld().addLight(Light{glm::vec3{0, 10, 5}, 1.f});
    while(true)
    {
        camera.startRender();
    }
}

//
// Created by krawacik3 on 27.12.2019.
//
#include <Camera.hpp>
#include <RandGen.hpp>

int main(){
    Camera<400, 400, 70> camera;
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-2, -1, -3),
            glm::vec3(0, -1, -3),
            glm::vec3(-1, 1, -3),
            Pixel<>{255, 250, 100, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-1, -1, -5),
            glm::vec3(1, -1, -5),
            glm::vec3(0, 1, -5),
            Pixel<>{100, 200, 200, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, 1),
            glm::vec3(3, -1, 1),
            glm::vec3(3, -1, -6),
            Pixel<>{100, 200, 100, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-3, -1, 1),
            glm::vec3(3, -1, -6),
            glm::vec3(-3, -1, -6),
            Pixel<>{100, 200, 100, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-2, -1, -4),
            glm::vec3(0, -1, -4),
            glm::vec3(-1, 1, -4),
            Pixel<>{255, 255, 255, 255},
            5.5f,
            true
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-5000, 1, 10),
            glm::vec3(5000, 1, 10),
            glm::vec3(0, 5000, 10),
            Pixel<>{255, 255, 255, 255},
            1.f,
            true
    ));
     while(true)
    {
        camera.startRender();
        camera.startRender();
    }
}

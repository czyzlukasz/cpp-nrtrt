//
// Created by krawacik3 on 27.12.2019.
//
#include <Camera.hpp>
#include <RandGen.hpp>
#include <Sphere.hpp>
#include <TransparentSphere.hpp>


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
            Pixel<>{250, 50, 50, 255},
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
    camera.getWorld().addObject(std::make_unique<Sphere>(
            glm::vec3(.6f,-.5f,-3.5),
            0.25f,
            Pixel<>{255, 255, 255, 255},
            10.9f,
            true
    ));
    camera.getWorld().addObject(std::make_unique<Sphere>(
            glm::vec3(.5f,-.85f,-3.3),
            0.1f,
            Pixel<>{250,120,120, 255},
            1.f
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-2, -1, -4),
            glm::vec3(0, -1, -4),
            glm::vec3(-1, 1, -4),
            Pixel<>{15, 255, 20, 255},
            0.5f,
            true
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(-5000, 1, 10),
            glm::vec3(5000, 1, 10),
            glm::vec3(0, 5000, 10),
            Pixel<>{255, 255, 255, 255},
            0.1f,
            true
    ));
    camera.getWorld().addObject(std::make_unique<Triangle>(
            glm::vec3(1.5, -1, -2),
            glm::vec3(1.5, -1, -4),
            glm::vec3(1.5, 1, -3),
            Pixel<>{255, 200, 200, 255},
            5.5f
    ));
    
    camera.getWorld().addObject(std::make_unique<TransparentSphere>(
            glm::vec3(0.2f, 0, -2.f),
            0.35f,
            Pixel<>{255, 255, 255, 255},
            1.5f
    ));
     while(true)
    {
        camera.startRender();
        camera.startRender();
    }
}

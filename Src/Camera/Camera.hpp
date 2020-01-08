//
// Created by krawacik3 on 27.12.2019.
//

#ifndef CPP_NRTRT_CAMERA_HPP
#define CPP_NRTRT_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <chrono>
#include <thread>
#include <World/World.hpp>
#include <Pixel.hpp>
#include <RandGen/RandGen.hpp>
#include <Worker.hpp>
#include <WorkerPool.hpp>

using uint = unsigned int;


template<uint WIDTH, uint HEIGHT, uint FOV, uint FOCAL_POINT_1000 = 1, uint SENSOR_WIDTH_1000 = 10, uint NUM_OF_WORKER_THREADS = 8, uint SAMPLES_PER_PIXEL = spp, typename vec3=glm::dvec3>
struct Camera {
    Camera() : 
        window(sf::VideoMode(WIDTH, HEIGHT), "cpp-nrtrt"), 
        workerPool(world),
        pixelBuffer(std::make_unique<std::array<AveragePixel, WIDTH * HEIGHT>>()){
        window.setFramerateLimit(30);
        displayThread = std::thread([&]() {
            sf::Event event;
            while(window.waitEvent(event)) {
                refreshDisplayedImage();
                std::this_thread::sleep_for(std::chrono_literals::operator ""ms(100));
            }
        });
        displayThread.detach();
    }

    inline Pixel<>& getPixel(uint x, uint y){
        return imageBuffer.at(x + y * WIDTH);
    }

    //Returns the direction of given pixel by calculating deviation from "front"
    inline Ray getRay(int x, int y) const{
        constexpr float RANGE = std::tan(FOV / 2.f);
        constexpr float MOVE_PER_X = 2.f * RANGE / WIDTH;
        constexpr float MOVE_PER_Y = - 2.f * RANGE / HEIGHT;
        const float deviationFromCenterX = static_cast<float>(x) - WIDTH / 2.f;
        const float deviationFromCenterY = static_cast<float>(y) - HEIGHT / 2.f;
        const glm::vec3 generalDirection = glm::normalize(glm::vec3(deviationFromCenterX * MOVE_PER_X, deviationFromCenterY * MOVE_PER_Y,-1.f));
        return Ray{{}, generalDirection};
        // constexpr float FOCAL_POINT = FOCAL_POINT_1000 / 1000.f;
        // constexpr float SENSOR_WIDTH = SENSOR_WIDTH_1000 / 1000.f;
        // constexpr float PIXEL_WIDTH = SENSOR_WIDTH / WIDTH;
        // const float relPixelPosX = PIXEL_WIDTH * (RandGen::getRandom() * 2.f - 1.f);
        // const float relPixelPosY = PIXEL_WIDTH * (RandGen::getRandom() * 2.f - 1.f);
        // const float absPixelPosX = static_cast<float>(x) * PIXEL_WIDTH - SENSOR_WIDTH / 2.f + relPixelPosX;
        // const float absPixelPosY = static_cast<float>(y) * PIXEL_WIDTH - SENSOR_WIDTH / 2.f + relPixelPosY;
        // const glm::vec3 position = glm::vec3(absPixelPosX, absPixelPosY, 0.f);

        // constexpr float MAX_ANGLE = std::atan((PIXEL_WIDTH / 2.f) / FOCAL_POINT);
        // const glm::vec3 directionToFocalPoint(-absPixelPosX, -absPixelPosY, -1.f);
        // constexpr glm::vec3 zVector(0, 0, -1);
        // const glm::vec3 crossProduct = glm::cross(zVector, generalDirection);
        // const float angle = glm::angle(generalDirection, zVector);
        // const glm::vec3 direction = glm::normalize(glm::rotate(directionToFocalPoint, angle, crossProduct));
        // return Ray{position, direction};
    }

    inline World& getWorld(){
        return world;
    }

    void startRender(){
        //TODO: Start with sorting the world's items from nearest to furthest
        world.sortObjects();
        //To start the render, Camera needs to split the work between multiple worker threads
        for(uint y = 0; y < HEIGHT; ++y){
            for(uint x = 0; x < WIDTH; ++x){
                for(uint sample = 0; sample < SAMPLES_PER_PIXEL; ++sample){
                    const Ray ray = getRay(x, y);
                    workerPool.initWorkerPool(ray, x + y * WIDTH);
                }
                workerPool.changeWorker();
            }
        }
        //Optional step, just looks way cooler
        workerPool.shuffle();
        //TODO: just pass a imageBuffer to startProcessing()
        workerPool.startProcessing(*pixelBuffer);
    }

private:

    void refreshDisplayedImage(){
        sf::Texture texture;
        texture.create(WIDTH, HEIGHT);
        sf::Sprite sprite(texture);
        for(uint idx = 0; idx < WIDTH * HEIGHT; ++idx){
            imageBuffer.at(idx) = pixelBuffer->at(idx).getPixel();
        }
        texture.update(reinterpret_cast<sf::Uint8*>(&imageBuffer[0]));
        window.draw(sprite);
        window.display();
        std::cout << &texture << std::endl;
    }

    sf::RenderWindow window;
    std::array<Pixel<sf::Uint8>, WIDTH * HEIGHT> imageBuffer;
    //TODO: changet vector to array of size SPP
    std::unique_ptr<std::array<AveragePixel, WIDTH * HEIGHT>> pixelBuffer;
    std::thread displayThread;
    World world;
    WorkerPool<NUM_OF_WORKER_THREADS, WIDTH * HEIGHT, SAMPLES_PER_PIXEL> workerPool;
};

#endif //CPP_NRTRT_CAMERA_HPP

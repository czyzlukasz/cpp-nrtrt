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


template<uint WIDTH, uint HEIGHT, uint FOV, uint NUM_OF_WORKER_THREADS = 4, uint SAMPLES_PER_PIXEL = spp, typename vec3=glm::dvec3>
struct Camera {
    Camera() : 
        window(sf::VideoMode(WIDTH, HEIGHT), "cpp-nrtrt"), 
        workerPool(world),
        pixelBuffer(std::make_unique<std::array<std::array<Pixel, SAMPLES_PER_PIXEL>, WIDTH * HEIGHT>>()){
        window.setFramerateLimit(30);
        displayThread = std::thread([&]() {
            while(true) {
                refreshDisplayedImage();
                std::this_thread::sleep_for(std::chrono_literals::operator ""ms(100));
            }
        });
        displayThread.detach();
    }

    inline Pixel& getPixel(uint x, uint y){
        return imageBuffer.at(x + y * WIDTH);
    }

    //Returns the direction of given pixel by calculating deviation from "front"
    inline glm::vec3 getDirection(int x, int y) const{
        constexpr float RANGE = std::tan(FOV / 2.f);
        constexpr float MOVE_PER_X = 2.f * RANGE / WIDTH;
        constexpr float MOVE_PER_Y = - 2.f * RANGE / HEIGHT;
        const float deviationFromCenterX = static_cast<float>(x) - WIDTH / 2.f;
        const float deviationFromCenterY = static_cast<float>(y) - HEIGHT / 2.f;
        return glm::normalize(glm::vec3(deviationFromCenterX * MOVE_PER_X, deviationFromCenterY * MOVE_PER_Y,-1.f));
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
                Ray ray{glm::vec3(), getDirection(x, y)};
                workerPool.initWorkerPool(ray, x + y * WIDTH);
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
        static auto accumulatePixels = [&](const uint index){
            uint r = 0, g = 0, b = 0;
            for(auto& pixel : pixelBuffer->at(index)){
                r += pixel.R;
                g += pixel.G;
                b += pixel.B;
            }
            return Pixel{
                    static_cast<sf::Uint8>(r / SAMPLES_PER_PIXEL),
                    static_cast<sf::Uint8>(g / SAMPLES_PER_PIXEL),
                    static_cast<sf::Uint8>(b / SAMPLES_PER_PIXEL),
                    255
            };
        };
        for(uint idx = 0; idx < WIDTH * HEIGHT; ++idx){
            imageBuffer.at(idx) = accumulatePixels(idx);
        }
        texture.update(reinterpret_cast<sf::Uint8*>(&imageBuffer[0]));
        window.draw(sprite);
        window.display();
        std::cout << &texture << std::endl;
    }

    sf::RenderWindow window;
    std::array<Pixel, WIDTH * HEIGHT> imageBuffer;
    std::unique_ptr<std::array<std::array<Pixel, SAMPLES_PER_PIXEL>, WIDTH * HEIGHT>> pixelBuffer;
    std::thread displayThread;
    World world;
    WorkerPool<NUM_OF_WORKER_THREADS, WIDTH * HEIGHT, SAMPLES_PER_PIXEL> workerPool;
};


#endif //CPP_NRTRT_CAMERA_HPP

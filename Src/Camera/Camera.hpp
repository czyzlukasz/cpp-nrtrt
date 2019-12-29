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


template<uint WIDTH, uint HEIGHT, uint FOV, uint NUM_OF_WORKER_THREADS = 16, typename vec3=glm::dvec3>
struct Camera {
    Camera() : window(sf::VideoMode(WIDTH, HEIGHT), "cpp-nrtrt"), workerPool(world){
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

    //Returns the angle of given pixel by calculating deviation from "front"
    inline auto getAngle(int x, int y) const{
        //minus is there for reversing direction of rotation
        static constexpr float ANGLE_PER_PIXEL = - static_cast<float>(FOV) / WIDTH * 2. * M_PI / 360.;
        static constexpr int HALF_WIDTH = WIDTH / 2;
        static constexpr int HALF_HEIGHT = HEIGHT / 2;
        return std::make_tuple((x - HALF_WIDTH) * ANGLE_PER_PIXEL,
                               (y - HALF_HEIGHT) * ANGLE_PER_PIXEL);
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
                const auto [angleX, angleY] = getAngle(x, y);
                glm::vec3 direction(0.f, 0.f, -1.f);
                direction = glm::rotateY(direction, angleX);
                direction = glm::rotateX(direction, angleY);

                Ray ray{glm::vec3(), glm::normalize(direction)};
                workerPool.initWorkerPool(ray, x + y * WIDTH);
            }
        }

        //TODO: just pass a imageBuffer to startProcessing()
        workerPool.startProcessing(imageBuffer);
    }

private:

    void refreshDisplayedImage(){
        sf::Texture texture;
        texture.create(WIDTH, HEIGHT);
        sf::Sprite sprite(texture);
        texture.update(reinterpret_cast<sf::Uint8*>(&imageBuffer[0]));
        window.draw(sprite);
        window.display();
        std::cout << &texture << std::endl;
    }

    sf::RenderWindow window;
    std::array<Pixel, WIDTH * HEIGHT> imageBuffer;
    std::thread displayThread;
    World world;
    WorkerPool<NUM_OF_WORKER_THREADS, WIDTH * HEIGHT> workerPool;
};


#endif //CPP_NRTRT_CAMERA_HPP

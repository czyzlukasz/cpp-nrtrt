//
// Created by krawacik3 on 27.12.2019.
//

#ifndef CPP_NRTRT_CAMERA_HPP
#define CPP_NRTRT_CAMERA_HPP

#include <glm/vec3.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>


using uint = unsigned int;

//POD to store RGBA data of pixel
struct Pixel{
    sf::Uint8 R = 0, G = 0,  B = 0, A = 255;
};


template<uint WIDTH, uint HEIGHT, uint FOV, typename vec3=glm::dvec3>
struct Camera {
    Camera() : window(sf::VideoMode(WIDTH, HEIGHT), "cpp-nrtrt"){
        window.setFramerateLimit(30);
    }

    void refreshDisplayedImage(){
        sf::Texture texture;
        texture.create(WIDTH, HEIGHT);
        sf::Sprite sprite(texture);
        texture.update(reinterpret_cast<sf::Uint8*>(&imageBuffer[0]));
        window.draw(sprite);
        window.display();
    }

    inline Pixel& getPixel(uint x, uint y){
        return imageBuffer.at(x + y * WIDTH);
    }

    //Returns the angle of given pixel by calculating deviation from "front"
    inline auto getAngle(uint x, uint y) const{
        static constexpr float ANGLE_PER_PIXEL = static_cast<float>(FOV) / WIDTH;
        static constexpr int HALF_WIDTH = WIDTH / 2;
        static constexpr int HALF_HEIGHT = HEIGHT / 2;
        return std::make_tuple((HALF_WIDTH - x) * ANGLE_PER_PIXEL,
                               (HALF_HEIGHT - y) * ANGLE_PER_PIXEL);
    }

private:
    sf::RenderWindow window;
    std::array<Pixel, WIDTH * HEIGHT> imageBuffer;
};


#endif //CPP_NRTRT_CAMERA_HPP

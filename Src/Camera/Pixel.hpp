//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_PIXEL_HPP
#define CPP_NRTRT_PIXEL_HPP

#include <SFML/Graphics.hpp>


//POD to store RGBA data of pixel
struct Pixel{
    sf::Uint8 R = 0, G = 255,  B = 0, A = 255;
};

#endif //CPP_NRTRT_PIXEL_HPP

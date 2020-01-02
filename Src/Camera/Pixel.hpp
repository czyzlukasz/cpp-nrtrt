//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_PIXEL_HPP
#define CPP_NRTRT_PIXEL_HPP

#include <SFML/Graphics.hpp>


//POD to store RGBA data of pixel
struct Pixel{
    sf::Uint8 R = 0, G = 0,  B = 0, A = 255;

    Pixel operator* (float factor) const{
        return Pixel{static_cast<sf::Uint8>(R * factor),
                     static_cast<sf::Uint8>(G * factor),
                     static_cast<sf::Uint8>(B * factor),
                     255};
    }

     Pixel operator* (const Pixel& other) const{
        uint r = static_cast<uint>(R) * static_cast<uint>(other.R);
        uint g = static_cast<uint>(G) * static_cast<uint>(other.G);
        uint b = static_cast<uint>(B) * static_cast<uint>(other.B);
        return Pixel{static_cast<sf::Uint8>(r / 255),
                     static_cast<sf::Uint8>(g / 255),
                     static_cast<sf::Uint8>(b / 255),
                     255};
    }

    bool operator == (const Pixel& other) const{
        return (R == other.R) &&
                (G == other.G) &&
                (B == other.B);
    }
};

#endif //CPP_NRTRT_PIXEL_HPP

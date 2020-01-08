//
// Created by krawacik3 on 28.12.2019.
//

#ifndef CPP_NRTRT_PIXEL_HPP
#define CPP_NRTRT_PIXEL_HPP

#include <SFML/Graphics.hpp>


//POD to store RGBA data of pixel
template<typename T = unsigned char>
struct Pixel{
    T R = 0, G = 0,  B = 0, A = 255;

    Pixel operator* (float factor) const{
        if(factor < 1.f) {
            return Pixel{static_cast<T>(R * factor),
                         static_cast<T>(G * factor),
                         static_cast<T>(B * factor),
                         255};
        }
        return Pixel{static_cast<T>(std::min(static_cast<uint>(std::numeric_limits<T>::max()), static_cast<uint>(R * factor))),
                     static_cast<T>(std::min(static_cast<uint>(std::numeric_limits<T>::max()), static_cast<uint>(G * factor))),
                     static_cast<T>(std::min(static_cast<uint>(std::numeric_limits<T>::max()), static_cast<uint>(B * factor))),
                     255
        };
    }

    Pixel operator / (uint factor) const{
        return Pixel{static_cast<T>(static_cast<uint>(R) / factor),
                     static_cast<T>(static_cast<uint>(G) / factor),
                     static_cast<T>(static_cast<uint>(B) / factor),
                     255};
    }

    Pixel operator* (const Pixel& other) const{
        uint r = static_cast<uint>(R) * static_cast<uint>(other.R);
        uint g = static_cast<uint>(G) * static_cast<uint>(other.G);
        uint b = static_cast<uint>(B) * static_cast<uint>(other.B);
        return Pixel{static_cast<T>(r / 255),
                     static_cast<T>(g / 255),
                     static_cast<T>(b / 255),
                     255};
    }

    bool operator == (const Pixel& other) const{
        return (R == other.R) &&
                (G == other.G) &&
                (B == other.B);
    }
};

//Struct holding data of pixel sampled multiple times
struct AveragePixel{
    [[nodiscard]] Pixel<sf::Uint8> getPixel() const{
        if(samples == 0){
            return Pixel<sf::Uint8>{0,0,0,255};
        }
        const auto result = cumulatedPixel / samples * 5.f;
        return Pixel<sf::Uint8>{static_cast<sf::Uint8>(result.R),
                                static_cast<sf::Uint8>(result.G),
                                static_cast<sf::Uint8>(result.B),
                                255};
    }

    template <typename T>
    void addPixel(const Pixel<T>& pixel){
        cumulatedPixel.R += pixel.R;
        cumulatedPixel.G += pixel.G;
        cumulatedPixel.B += pixel.B;
        ++samples;
    }

private:
    Pixel<uint> cumulatedPixel;
    uint samples;
};

#endif //CPP_NRTRT_PIXEL_HPP

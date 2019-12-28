//
// Created by krawacik3 on 27.12.2019.
//
#include <Camera.hpp>
#include <chrono>
#include <thread>
#include <RandGen.hpp>

int main(){
    RandGen::initRandGen();
    Camera<400, 400, 70> camera;
    while(true) {
        camera.refreshDisplayedImage();
        std::this_thread::sleep_for(std::chrono_literals::operator ""ms(100));
    }
}

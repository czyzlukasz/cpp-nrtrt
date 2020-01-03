//
// Created by krawacik3 on 29.12.2019.
//

#ifndef CPP_NRTRT_WORKERPOOL_HPP
#define CPP_NRTRT_WORKERPOOL_HPP

#include <Worker.hpp>
#include <thread>


template <uint NUM_OF_WORKER_THREADS, uint NUM_OF_PIXELS, uint SAMPLES_PER_PIXEL>
struct WorkerPool {
    explicit WorkerPool(const World& world) : currentWorkerSelected(0){
        for(uint idx = 0; idx < NUM_OF_WORKER_THREADS; ++idx){
            workerArray.emplace_back(world);
        }
    }

    inline void initWorkerPool(const Ray& ray, uint pixelId){
        workerArray.at(currentWorkerSelected).addRay(ray, pixelId);
        //Increment current worker ID
        ++currentWorkerSelected;
        if(!(currentWorkerSelected % NUM_OF_WORKER_THREADS)){
            currentWorkerSelected = 0;
        }
    }

    void shuffle(){
        for(auto& worker : workerArray){
            worker.shuffle();
        }
    }

    void startProcessing(std::array<std::vector<Pixel<>>, NUM_OF_PIXELS>& pixelArray){
        std::vector<std::thread> threadArray;
        for(uint idx = 0; idx < NUM_OF_WORKER_THREADS; ++idx){
            threadArray.emplace_back(&Worker::processRays, &workerArray.at(idx), std::ref(pixelArray));
        }

        for(auto& thread : threadArray){
            thread.join();
        }
    }

private:
    std::vector<Worker> workerArray;
    uint currentWorkerSelected;
};


#endif //CPP_NRTRT_WORKERPOOL_HPP

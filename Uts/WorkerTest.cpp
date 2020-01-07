//
// Created by krawacik3 on 03.01.2020.
//

#include <gtest/gtest.h>
#include <Worker.hpp>
#include <World.hpp>
#include <numeric>


struct WorkerTest : public ::testing::Test{
    WorkerTest() : worker(world){
        world.addObject(std::make_unique<Triangle>(
            glm::vec3(2, 0, -1),
            glm::vec3(1, 2, -1),
            glm::vec3(0, 0, -1),
            Pixel<>{255, 255, 255, 255},
            1.f,
            true
        ));
        //This object is behind the light
        world.addObject(std::make_unique<Triangle>(
            glm::vec3(2, 0, -2),
            glm::vec3(0, 0, -2),
            glm::vec3(1, 2, -2),
            Pixel<>{200, 100, 50, 255},
            1.f
        ));
    }

protected:
    World world;
    Worker worker;
};

TEST_F(WorkerTest, CheckColorFromFront){
    const Ray front{{1, 1, 0}, {0, 0 , -1}};
    std::array<std::vector<Pixel<>>, 160000> container;
    worker.addRay(front, 0);
    worker.processRays(container);
    const Pixel<> whitePixel{255, 255, 255, 255};
    EXPECT_EQ(container.at(0).at(0), whitePixel);
}

TEST_F(WorkerTest, CheckColorFromBack){
    const Ray front{{1, 1, -2}, {0, 0 , 1}};
    std::array<std::vector<Pixel<>>, 160000> container;
    worker.addRay(front, 0);
    worker.processRays(container);
    const Pixel<> whitePixel{255, 255, 255, 255};
    EXPECT_EQ(container.at(0).at(0), whitePixel);
}

TEST_F(WorkerTest, CheckColorFromAngle){
    //45 degrees to the triangle
    const Ray front{{0, 0.5, 0}, glm::normalize(glm::vec3(1, 0, -1))};
    std::array<std::vector<Pixel<>>, 160000> container;
    worker.addRay(front, 0);
    worker.processRays(container);
    const float factor = std::cos(M_PI_4);
    const Pixel<> grayPixel{static_cast<sf::Uint8>(255.f * factor),
                          static_cast<sf::Uint8>(255.f * factor),
                          static_cast<sf::Uint8>(255.f * factor),
                          255};
    EXPECT_EQ(container.at(0).at(0), grayPixel);
}

TEST_F(WorkerTest, CheckIfRaysPenetrate){
    //Ray is directed towards object and has no direct path towards light
    const Ray ray{{0, 0, -3}, glm::normalize(glm::vec3(0.1, 0.1, 1))};
    std::array<std::vector<Pixel<>>, 160000> container;
    const Pixel<> blackPixel{0, 0, 0, 255};
    worker.addRay(ray, 0);
    for(uint idx = 0; idx < 1000; ++idx){
        worker.processRays(container);
        ASSERT_EQ(container.at(0).at(0), blackPixel) << std::to_string(idx);
    }
}

TEST_F(WorkerTest, CheckReflections){
    //Ray is between object and light and is directed towards object
    const Ray ray{{1.f, 1.f, -1.5f}, {0, 0 , -1}};
    std::array<std::vector<Pixel<>>, 160000> container;
    for(uint idx = 0; idx < 1000; ++idx){
        worker.addRay(ray, idx);
    }
    worker.processRays(container);
    struct SuperPixel{
        uint r = 0, g = 0, b = 0;
    };
    static auto accumulateInner = [](const SuperPixel& sPixel, const Pixel<>& pixel){
        return SuperPixel{sPixel.r + pixel.R,
                          sPixel.g + pixel.G,
                          sPixel.b + pixel.B};
    };

    static auto accumulate = [](const SuperPixel& sPixel, const std::vector<Pixel<>>& pixelVector){
        const SuperPixel pixel = std::accumulate(pixelVector.begin(), pixelVector.end(), SuperPixel(), accumulateInner);
        return SuperPixel{sPixel.r + pixel.r,
                          sPixel.g + pixel.g,
                          sPixel.b + pixel.b};
    };

    const SuperPixel result = std::accumulate(container.begin(), container.begin() + 1000, SuperPixel(), accumulate);
    //Parameter 0.10 is chosen by common sense,
    //It indicates that pixel receives only 0.15 of best case scenario:
    //Perpendicular reflections that always reach light
    const float factor = 0.10;
    EXPECT_GT(result.r, 1000 * 200 * factor * spp);
    EXPECT_GT(result.g, 1000 * 100 * factor * spp);
    EXPECT_GT(result.b, 1000 * 50 * factor * spp);
    EXPECT_LT(result.r, 1000 * 255 * spp);
    EXPECT_LT(result.g, 1000 * 255 * spp);
    EXPECT_LT(result.b, 1000 * 255 * spp);
}
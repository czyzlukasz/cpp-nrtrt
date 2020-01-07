//
// Created by krawacik3 on 30.12.2019.
//

#include <gtest/gtest.h>
#include <RandGen.hpp>

TEST(RandGenTest, DeviateVectorX){
    const glm::vec3 xVector(1, 0, 0);
    const float angle = 1.f;
    for(uint idx = 0; idx < 1000; ++idx){
        const glm::vec3 result = RandGen::deviateVector(xVector, angle);
        ASSERT_LE(glm::angle(xVector, result), angle * 0.5f * M_PI);
        ASSERT_GT(glm::dot(xVector, result), 0.f);
    }
}

TEST(RandGenTest, DeviateVectorRandom){
    const float angle = 0.25f;
    for(uint vectorIdx = 0; vectorIdx < 100; ++vectorIdx){
        const glm::vec3 randomVector = glm::normalize(glm::vec3(RandGen::getRandom(), RandGen::getRandom(), RandGen::getRandom()));
        for(uint idx = 0; idx < 1000; ++idx){
            const glm::vec3 result = RandGen::deviateVector(randomVector, angle);
            ASSERT_LE(glm::angle(randomVector, result), angle * 0.5f * M_PI);
        }
    }
}

TEST(RandGenTest, DeviateVectorZ){
    const glm::vec3 zVector(0, 0, 1);
    const float angle = 1.f;
    for(uint idx = 0; idx < 1000; ++idx){
        const glm::vec3 result = RandGen::deviateVector(zVector, angle);
        ASSERT_LE(glm::angle(zVector, result), angle * 0.5f * M_PI);
        ASSERT_GT(glm::dot(zVector, result), 0.f);
    }
}

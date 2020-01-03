//
// Created by krawacik3 on 03.01.2020.
//

#include <gtest/gtest.h>
#include <Sphere.hpp>

struct SphereTest : public ::testing::Test{
    SphereTest()
        : sphere({10, 10, 10}, 5.f, Pixel<>(), 1),
        passRay(Ray{{3,3,3}, glm::normalize(glm::vec3(1,1,1))}),
        failRay(Ray{{3,3,3}, glm::normalize(glm::vec3(-1,-1,-1))})
        {}
protected:
    const Sphere sphere;
    const Ray passRay, failRay;
};

TEST_F(SphereTest, TestCollisionPass){
    const glm::vec3 result = sphere.collisionPoint(passRay);
    EXPECT_NE(result.x, 0.f);
    EXPECT_NE(result.y, 0.f);
    EXPECT_NE(result.z, 0.f);
}

TEST_F(SphereTest, TestCollisionFail){
    const glm::vec3 result = sphere.collisionPoint(failRay);
    EXPECT_EQ(result.x, 0.f);
    EXPECT_EQ(result.y, 0.f);
    EXPECT_EQ(result.z, 0.f);
}

TEST_F(SphereTest, CheckCollsionPoint){
    const glm::vec3 result = sphere.collisionPoint(passRay);
    EXPECT_FLOAT_EQ(result.x, 7.12435565298f);
    EXPECT_FLOAT_EQ(result.y, 7.12435565298f);
    EXPECT_FLOAT_EQ(result.z, 7.12435565298f);
}

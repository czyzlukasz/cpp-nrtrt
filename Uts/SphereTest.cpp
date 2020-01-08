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

TEST_F(SphereTest, TestCollisionFromCenter){
    const Ray ray{{10, 10, 8}, {0, 0, 1}};
    const glm::vec3 result = sphere.collisionPoint(ray);
    EXPECT_FLOAT_EQ(result.x, 10.f);
    EXPECT_FLOAT_EQ(result.y, 10.f);
    EXPECT_FLOAT_EQ(result.z, 15.f);
}

TEST_F(SphereTest, CheckCollsionPoint){
    const glm::vec3 result = sphere.collisionPoint(passRay);
    EXPECT_FLOAT_EQ(result.x, 7.1132493f);
    EXPECT_FLOAT_EQ(result.y, 7.1132493f);
    EXPECT_FLOAT_EQ(result.z, 7.1132493f);
}

TEST_F(SphereTest, CheckNormal){
    const glm::vec3 collisionPoint = sphere.collisionPoint(passRay);
    const glm::vec3 normal = sphere.normalAtPoint(collisionPoint);
    const float val = 1. / std::sqrt(3);
    EXPECT_FLOAT_EQ(normal.x, -val);
    EXPECT_FLOAT_EQ(normal.y, -val);
    EXPECT_FLOAT_EQ(normal.z, -val);
}

TEST_F(SphereTest, CheckNormalAtAngle){
    const Ray ray{{10, 7.5, 0}, {0, 0, 1}};
    const glm::vec3 collisionPoint = sphere.collisionPoint(ray);
    const glm::vec3 normal = sphere.normalAtPoint(collisionPoint);
    EXPECT_FLOAT_EQ(normal.x, 0.f);
    EXPECT_FLOAT_EQ(normal.y, -0.5f);
    EXPECT_FLOAT_EQ(normal.z, -0.86602545f);
}

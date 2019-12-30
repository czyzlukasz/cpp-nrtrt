//
// Created by krawacik3 on 28.12.2019.
//

#include <gtest/gtest.h>
#include <Triangle.hpp>


struct TriangleTest : public ::testing::Test{
    TriangleTest() : t(glm::vec3(10, 14, 15),
                       glm::vec3(10, 10, 10),
                       glm::vec3(10, 10, 19),
                       Pixel(),
                       0.5f),
                    passRay(Ray{glm::vec3(1, 1, 1),glm::normalize(glm::vec3(1, 1.1, 1.4))}),
                    failRay(Ray{glm::vec3(1, 1, 1),glm::normalize(glm::vec3(1, 2, 1.1))}){
    }
protected:
    const Triangle t;
    const Ray passRay;
    const Ray failRay;
};


TEST_F(TriangleTest, CheckCenter){
    EXPECT_EQ(t.getCenter().x, 10.f);
    EXPECT_EQ(t.getCenter().y, 9.5f);
    EXPECT_EQ(t.getCenter().z, 14.5f);
}

TEST_F(TriangleTest, CheckRadius){
    EXPECT_FLOAT_EQ(t.getRadius(), 4.5276929f);
}

TEST_F(TriangleTest, CheckNormal){
    EXPECT_EQ(t.normalAtPoint(glm::vec3()).x, -1);
    EXPECT_EQ(t.normalAtPoint(glm::vec3()).y, 0);
    EXPECT_EQ(t.normalAtPoint(glm::vec3()).z, 0);
}

TEST_F(TriangleTest, CheckIfCanCollide){
    EXPECT_TRUE(t.canCollide(passRay));
    EXPECT_FALSE(t.canCollide(failRay));
}

TEST_F(TriangleTest, CollisionPointPass){
    const glm::vec3 collisionPoint = t.collisionPoint(passRay);
    EXPECT_FLOAT_EQ(collisionPoint.x, 10);
    EXPECT_FLOAT_EQ(collisionPoint.y, 10.9);
    EXPECT_FLOAT_EQ(collisionPoint.z, 13.6);
}

TEST_F(TriangleTest, CollisionPointFail){
    const glm::vec3 collisionPoint = t.collisionPoint(failRay);
    EXPECT_FLOAT_EQ(collisionPoint.x, 0);
    EXPECT_FLOAT_EQ(collisionPoint.y, 0);
    EXPECT_FLOAT_EQ(collisionPoint.z, 0);
}

//
// Created by krawacik3 on 28.12.2019.
//

#include <gtest/gtest.h>
#include <Triangle.hpp>

TEST(TriangleTest, CheckCenter){
    const glm::vec3 a(10, 10, 10);
    const glm::vec3 b(10, 10, 19);
    const glm::vec3 c(10, 14, 15);
    Triangle t(a, b, c);
    EXPECT_EQ(t.getCenter().x, 10.f);
    EXPECT_EQ(t.getCenter().y, 9.5f);
    EXPECT_EQ(t.getCenter().z, 14.5f);
}

TEST(TriangleTest, CheckRadius){
    const glm::vec3 a(10, 10, 10);
    const glm::vec3 b(10, 10, 19);
    const glm::vec3 c(10, 14, 15);
    Triangle t(a, b, c);
    EXPECT_FLOAT_EQ(t.getRadius(), 4.5276929f);
}
//
// Created by krawacik3 on 08.01.2020.
//

#include <gtest/gtest.h>
#include <TransparentSphere.hpp>


struct TransparentSphereTest : public ::testing::Test{
    TransparentSphereTest() : tSphere(glm::vec3(3,3,3), 2.f, Pixel<>{255,255,255,255}, 1.5f){}

protected:
    TransparentSphere tSphere;
};

TEST_F(TransparentSphereTest, CheckCenterRay){
    //Almost center. Avoid perfect hit at 0 degrees to normal
    const Ray centerRay{{3,2.999,0}, {0,0,1}};
    const glm::vec3 collisionPoint = tSphere.collisionPoint(centerRay);
    const Ray result = tSphere.outputRay(collisionPoint, centerRay.direction);
    EXPECT_FLOAT_EQ(result.direction.x, centerRay.direction.x);
    EXPECT_NEAR(result.direction.y, centerRay.direction.y, 0.0002);
    EXPECT_FLOAT_EQ(result.direction.z, centerRay.direction.z);
}

TEST_F(TransparentSphereTest, CheckRayAt45Degree){
    //Hit at 45 degrees
    const Ray centerRay{{3,3 + 2.f / std::sqrt(2.f),0}, {0,0,1}};
    const glm::vec3 collisionPoint = tSphere.collisionPoint(centerRay);
    //Check if ray hits at 45 degrees
    EXPECT_NEAR(glm::dot(-centerRay.direction, tSphere.normalAtPoint(collisionPoint)), std::sin(M_PI_4), 1e-5);
    const Ray result = tSphere.calculateInternalRay(collisionPoint, centerRay.direction);
    const float internalAngleCalculated = std::asin(std::sin(M_PI_4) * 1.f / 1.5f);
    const float internalAngleResult = glm::angle(result.direction, -tSphere.normalAtPoint(collisionPoint));
    EXPECT_NEAR(internalAngleResult, internalAngleCalculated, 1e-5);
}

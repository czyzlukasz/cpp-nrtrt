//
// Created by krawacik3 on 02.01.2020.
//

#include <gtest/gtest.h>
#include <Pixel.hpp>

TEST(PixelTest, TestPixelMultiplyPixel){
    const Pixel<> pixelFirst{10, 20, 30};
    const Pixel<> pixelSecond{190, 190, 190};
    const Pixel<> result{7, 14, 22};
    EXPECT_EQ(result, pixelFirst * pixelSecond);
    EXPECT_EQ(result, pixelSecond * pixelFirst);
}
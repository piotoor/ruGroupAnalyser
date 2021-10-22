#include "gtest/gtest.h"
#include "ruCubeMultiSolveHandler.h"


TEST(ruCubeMultiSolveHandlerTest, calculateTotalNumberOfCubesToGenerateDefaultSettingsTest) {
    ruCubeMultiSolveHandler handler;

    const int expectedNumberOfCubes = 73'483'200;
    ASSERT_EQ(expectedNumberOfCubes, handler.calculateTotalNumberOfCubesToGenerate());
}

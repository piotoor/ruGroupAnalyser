#include "gtest/gtest.h"
#include "orientationGenerator.h"

#include <vector>
#include <iostream>
using namespace std;


TEST(orientationGeneratorTest, generateOrientationtTest) {
    orientationGenerator gen;

    auto orients = gen.generateOrientations(0);
    std::vector<std::vector<int8_t>> expectedOrients = {
        { }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(1);
    expectedOrients = {
        { 0 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(2);
    expectedOrients = {
        { 0, 0 },
        { 1, 2 },
        { 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(3);
    expectedOrients = {
        { 0, 0, 0 },
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 1, 1 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 },
        { 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(4);
    expectedOrients = {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 2 },
        { 0, 0, 2, 1 },
        { 0, 1, 0, 2 },
        { 0, 1, 1, 1 },
        { 0, 1, 2, 0 },
        { 0, 2, 0, 1 },
        { 0, 2, 1, 0 },
        { 0, 2, 2, 2 },
        { 1, 0, 0, 2 },
        { 1, 0, 1, 1 },
        { 1, 0, 2, 0 },
        { 1, 1, 0, 1 },
        { 1, 1, 1, 0 },
        { 1, 1, 2, 2 },
        { 1, 2, 0, 0 },
        { 1, 2, 1, 2 },
        { 1, 2, 2, 1 },
        { 2, 0, 0, 1 },
        { 2, 0, 1, 0 },
        { 2, 0, 2, 2 },
        { 2, 1, 0, 0 },
        { 2, 1, 1, 2 },
        { 2, 1, 2, 1 },
        { 2, 2, 0, 2 },
        { 2, 2, 1, 1 },
        { 2, 2, 2, 0 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(5);
    expectedOrients = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2 },
        { 0, 0, 0, 2, 1 },
        { 0, 0, 1, 0, 2 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 1, 2, 0 },
        { 0, 0, 2, 0, 1 },
        { 0, 0, 2, 1, 0 },
        { 0, 0, 2, 2, 2 },
        { 0, 1, 0, 0, 2 },
        { 0, 1, 0, 1, 1 },
        { 0, 1, 0, 2, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 1, 2, 2 },
        { 0, 1, 2, 0, 0 },
        { 0, 1, 2, 1, 2 },
        { 0, 1, 2, 2, 1 },
        { 0, 2, 0, 0, 1 },
        { 0, 2, 0, 1, 0 },
        { 0, 2, 0, 2, 2 },
        { 0, 2, 1, 0, 0 },
        { 0, 2, 1, 1, 2 },
        { 0, 2, 1, 2, 1 },
        { 0, 2, 2, 0, 2 },
        { 0, 2, 2, 1, 1 },
        { 0, 2, 2, 2, 0 },
        { 1, 0, 0, 0, 2 },
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 2, 0 },
        { 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 0, 1, 2, 2 },
        { 1, 0, 2, 0, 0 },
        { 1, 0, 2, 1, 2 },
        { 1, 0, 2, 2, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 1, 0, 2, 2 },
        { 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 2 },
        { 1, 1, 1, 2, 1 },
        { 1, 1, 2, 0, 2 },
        { 1, 1, 2, 1, 1 },
        { 1, 1, 2, 2, 0 },
        { 1, 2, 0, 0, 0 },
        { 1, 2, 0, 1, 2 },
        { 1, 2, 0, 2, 1 },
        { 1, 2, 1, 0, 2 },
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 0 },
        { 1, 2, 2, 0, 1 },
        { 1, 2, 2, 1, 0 },
        { 1, 2, 2, 2, 2 },
        { 2, 0, 0, 0, 1 },
        { 2, 0, 0, 1, 0 },
        { 2, 0, 0, 2, 2 },
        { 2, 0, 1, 0, 0 },
        { 2, 0, 1, 1, 2 },
        { 2, 0, 1, 2, 1 },
        { 2, 0, 2, 0, 2 },
        { 2, 0, 2, 1, 1 },
        { 2, 0, 2, 2, 0 },
        { 2, 1, 0, 0, 0 },
        { 2, 1, 0, 1, 2 },
        { 2, 1, 0, 2, 1 },
        { 2, 1, 1, 0, 2 },
        { 2, 1, 1, 1, 1 },
        { 2, 1, 1, 2, 0 },
        { 2, 1, 2, 0, 1 },
        { 2, 1, 2, 1, 0 },
        { 2, 1, 2, 2, 2 },
        { 2, 2, 0, 0, 2 },
        { 2, 2, 0, 1, 1 },
        { 2, 2, 0, 2, 0 },
        { 2, 2, 1, 0, 1 },
        { 2, 2, 1, 1, 0 },
        { 2, 2, 1, 2, 2 },
        { 2, 2, 2, 0, 0 },
        { 2, 2, 2, 1, 2 },
        { 2, 2, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (int i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}

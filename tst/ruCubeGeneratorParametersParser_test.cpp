#include "gtest/gtest.h"
#include "ruCubeGeneratorParametersParser.h"
#include "ruException.h"
#include <vector>
#include <string>


TEST(ruCubeGeneratorParametersParserTest, correctGeneratorParametersTest) {
    std::vector<std::string> generatorParamsStr {
        "GGGGGGGGGGGG;GGGGGGG",
        "GGGGGGGGGGGG;IIIIIII",
        "GGGGGGGGGGGG;LLLLLLL",
        "GGGGGGGGGGGG;LILILIL",
        "GGGGGGGGGGGG;LIGLIGL",

        "IIIIIIIIIIII;LIGLIGL",
        "2G2G2G2G2G1G;LIGLIGL",
        "IL2G2I2G2G0I;LIGLIGL",
    };

    std::vector<generatorParameters> expectedGenParams {
        generatorParameters(),
        {
            {},                         // lockedEdges
            { 0, 1, 2, 3, 4, 5, 6 },    // ignoredEdges
            {},                         // lockedCornersPerm
            {},                         // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },
        {
            { 0, 1, 2, 3, 4, 5, 6 },    // lockedEdges
            {},                         // ignoredEdges
            {},                         // lockedCornersPerm
            {},                         // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },
        {
            { 0, 2, 4, 6 },             // lockedEdges
            { 1, 3, 5 },                // ignoredEdges
            {},                         // lockedCornersPerm
            {},                         // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },
        {
            { 0, 3, 6 },                // lockedEdges
            { 1, 4 },                   // ignoredEdges
            {},                         // lockedCornersPerm
            {},                         // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },


        {
            { 0, 3, 6 },                // lockedEdges
            { 1, 4 },                   // ignoredEdges
            {},                         // lockedCornersPerm
            { 0, 1, 2, 3, 4, 5 },       // ignoredCornersPerm
            { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
            {  1,  1,  1,  1,  1,  1 }, // ignoredCornersOrient
        },
        {
            { 0, 3, 6 },                // lockedEdges
            { 1, 4 },                   // ignoredEdges
            {},                         // lockedCornersPerm
            {},                         // ignoredCornersPerm
            {  2,  2,  2,  2,  2,  1 }, // lockedCornersOrient
            {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },
        {
            { 0, 3, 6 },                // lockedEdges
            { 1, 4 },                   // ignoredEdges
            { 0 },                      // lockedCornersPerm
            { 2, 5 },                   // ignoredCornersPerm
            { -1,  2,  2,  2,  2,  0 }, // lockedCornersOrient
            {  1,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
        },
    };

    for (uint8_t i = 0; i < size(expectedGenParams); ++i) {
        generatorParameters genParams;
        ASSERT_NO_THROW(genParams = ruCubeGeneratorParametersParser::strGeneratorParametersToStruct(generatorParamsStr[i]));
        ASSERT_EQ(expectedGenParams[i].lockedEdges, genParams.lockedEdges);
        ASSERT_EQ(expectedGenParams[i].ignoredEdges, genParams.ignoredEdges);
        ASSERT_EQ(expectedGenParams[i].lockedCornersPerm, genParams.lockedCornersPerm);
        ASSERT_EQ(expectedGenParams[i].ignoredCornersPerm, genParams.ignoredCornersPerm);
        ASSERT_EQ(expectedGenParams[i].lockedCornersOrient, genParams.lockedCornersOrient);
        ASSERT_EQ(expectedGenParams[i].ignoredCornersOrient, genParams.ignoredCornersOrient);
    }
}


TEST(ruCubeGeneratorParametersParserTest, negativeTest) {
    std::vector<std::string> generatorParamsStr {
        "GGGGGGGGGGGG;GGGGGgG",
        "GGGGGGGGGGGG;IIiIIII",
        "GGGGGGGGGGGG;LLlLLLL",
        "GGGGGGGGGGGG;lilgGGl",
        "IiIlIgIIIIII;LIGLIGL",
        "2G2G2G3G2G1G;LIGLIGL",
        "IL2G2I2G2GgI;LIGLIGL",
        "Ib2G2I2G2GgI;LIGLIGL",
        "LL;LIGLIGL",
        "IL2G2I2G2GgI;L",
        "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLL;LLLLLLLLLLLLLLLLLL",
        "IIIIIIIIII;IIIIIIIIIIIII;LLLLLLLLLLLLLL",
        "",
        "sdfasdfasdfasdkfjlas;dlkfjas;dlfkjas;dlf"
    };

    std::string expectedException = "ruCubeGeneratorParametersException: Parsing exception. Invalid cube generator parameters.";

    uint8_t i = 0;
    for (; i < size(generatorParamsStr); ++i) {
        std::string exceptionMessage;
        try {
            auto genPerms = ruCubeGeneratorParametersParser::strGeneratorParametersToStruct(generatorParamsStr[i]);
        } catch (const ruCubeGeneratorParametersException &e) {
            exceptionMessage = e.what();
        }
        ASSERT_EQ(expectedException, exceptionMessage);
    }
    ASSERT_EQ(size(generatorParamsStr), i);
}


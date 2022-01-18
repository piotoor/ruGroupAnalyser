#include "gtest/gtest.h"
#include "ruCubeGeneratorParametersParser.h"
#include "ruException.h"
#include <vector>
#include <string>



namespace {
    class ruCubeGeneratorParametersParserTestPamrameterizedTestFixture: public testing::TestWithParam<std::tuple<std::string, generatorParameters>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    auto [generatorParamsStr, expected] = testData.param;
                    std::replace(begin(generatorParamsStr), end(generatorParamsStr), ';', '_');

                    std::stringstream ss;
                    ss  << generatorParamsStr;
                    return ss.str();
                }
            };

        protected:
            ruLutCube cube;
            ruCubeStateConverter conv;
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeGeneratorParametersParserTests,
        ruCubeGeneratorParametersParserTestPamrameterizedTestFixture,
        ::testing::ValuesIn( std::vector<std::tuple<std::string, generatorParameters>> {
                {
                    "GGGGGGGGGGGG;GGGGGGG",
                    generatorParameters()
                },
                {
                    "GGGGGGGGGGGG;IIIIIII",
                    {
                        {},                         // lockedEdges
                        { 0, 1, 2, 3, 4, 5, 6 },    // ignoredEdges
                        {},                         // lockedCornersPerm
                        {},                         // ignoredCornersPerm
                        { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                        {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                },
                {
                    "GGGGGGGGGGGG;LLLLLLL",
                    {
                        { 0, 1, 2, 3, 4, 5, 6 },    // lockedEdges
                        {},                         // ignoredEdges
                        {},                         // lockedCornersPerm
                        {},                         // ignoredCornersPerm
                        { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                        {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                },
                {
                    "GGGGGGGGGGGG;LILILIL",
                    {
                        { 0, 2, 4, 6 },             // lockedEdges
                        { 1, 3, 5 },                // ignoredEdges
                        {},                         // lockedCornersPerm
                        {},                         // ignoredCornersPerm
                        { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                        {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                },
                {
                    "GGGGGGGGGGGG;LIGLIGL",
                    {
                        { 0, 3, 6 },                // lockedEdges
                        { 1, 4 },                   // ignoredEdges
                        {},                         // lockedCornersPerm
                        {},                         // ignoredCornersPerm
                        { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                        {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                },
                {
                    "IIIIIIIIIIII;LIGLIGL",
                    {
                        { 0, 3, 6 },                // lockedEdges
                        { 1, 4 },                   // ignoredEdges
                        {},                         // lockedCornersPerm
                        { 0, 1, 2, 3, 4, 5 },       // ignoredCornersPerm
                        { -1, -1, -1, -1, -1, -1 }, // lockedCornersOrient
                        {  1,  1,  1,  1,  1,  1 }, // ignoredCornersOrient
                    },
                },
                {
                    "2G2G2G2G2G1G;LIGLIGL",
                    {
                        { 0, 3, 6 },                // lockedEdges
                        { 1, 4 },                   // ignoredEdges
                        {},                         // lockedCornersPerm
                        {},                         // ignoredCornersPerm
                        {  2,  2,  2,  2,  2,  1 }, // lockedCornersOrient
                        {  0,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                },
                {
                    "IL2G2I2G2G0I;LIGLIGL",
                    {
                        { 0, 3, 6 },                // lockedEdges
                        { 1, 4 },                   // ignoredEdges
                        { 0 },                      // lockedCornersPerm
                        { 2, 5 },                   // ignoredCornersPerm
                        { -1,  2,  2,  2,  2,  0 }, // lockedCornersOrient
                        {  1,  0,  0,  0,  0,  0 }, // ignoredCornersOrient
                    },
                }
            }
        ),
        ruCubeGeneratorParametersParserTestPamrameterizedTestFixture::toString()
    );

    TEST_P(ruCubeGeneratorParametersParserTestPamrameterizedTestFixture, correctGeneratorParametersTest) {
        const auto& [generatorParamsStr, expected] = GetParam();
        generatorParameters genParams;
        ASSERT_NO_THROW(genParams = ruCubeGeneratorParametersParser::strGeneratorParametersToStruct(generatorParamsStr));

        ASSERT_EQ(expected.lockedEdges, genParams.lockedEdges);
        ASSERT_EQ(expected.ignoredEdges, genParams.ignoredEdges);
        ASSERT_EQ(expected.lockedCornersPerm, genParams.lockedCornersPerm);
        ASSERT_EQ(expected.ignoredCornersPerm, genParams.ignoredCornersPerm);
        ASSERT_EQ(expected.lockedCornersOrient, genParams.lockedCornersOrient);
        ASSERT_EQ(expected.ignoredCornersOrient, genParams.ignoredCornersOrient);
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
            exceptionMessage = std::string(e.what());
        }
        ASSERT_EQ(expectedException, exceptionMessage);
    }
    ASSERT_EQ(size(generatorParamsStr), i);
}


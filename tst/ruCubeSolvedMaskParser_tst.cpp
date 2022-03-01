#include "gtest/gtest.h"
#include "ruCubeSolvedMaskParser.h"
#include "ruException.h"
#include "testCustomDefinitions.h"
#include <vector>
#include <string>

// co, cp, ep
using ruCubeSolvedMaskPair = std::pair<uint64_t, uint32_t>;

namespace {
    class ruCubeSolvedMaskParserStringSolvedMaskToIntCorrectMasksTestFixture: public testing::TestWithParam<std::tuple<std::string, ruCubeSolvedMaskPair>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    auto [mask, expected] = testData.param;
                    std::replace(begin(mask), end(mask), ';', '_');
                    return mask;
                }
            };
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSolvedMaskParserTests,
        ruCubeSolvedMaskParserStringSolvedMaskToIntCorrectMasksTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, ruCubeSolvedMaskPair> (
            {
                "FA32FAFA;0345FBCD;FFCA4520",
                "45687865;0345FBCD;FFCA4520",
                "FAFAFAFA;AAAAAAAA;BBBBBBBB",
                "00000000;00000000;00000000",
                "FFFFFFFF;FFFFFFFF;FFFFFFFF",
                "CCCCCCCC;DDDDDDDD;12345678",
                "01010101;01010101;00000000",
            },
            {
                { 0xFA32FAFA0345FBCD, 0xFFCA4520 },
                { 0x456878650345FBCD, 0xFFCA4520 },
                { 0xFAFAFAFAAAAAAAAA, 0xBBBBBBBB },
                { 0x0000000000000000, 0x00000000 },
                { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFF },
                { 0xCCCCCCCCDDDDDDDD, 0x12345678 },
                { 0x0101010101010101, 0x00000000 },
            }
        )),
        ruCubeSolvedMaskParserStringSolvedMaskToIntCorrectMasksTestFixture::toString()
    );

    TEST_P(ruCubeSolvedMaskParserStringSolvedMaskToIntCorrectMasksTestFixture, stringSolvedMaskToIntCorrectMasksTest) {
        const auto &[maskStr, expected] = GetParam();
        ruCubeSolvedMaskPair masks;
        ASSERT_NO_THROW(masks = ruCubeSolvedMaskParser::stringSolvedMaskToInt(maskStr));
        ASSERT_EQ(expected, masks);
    }
}

namespace {
    class ruCubeSolvedMaskParserStringSolvedMaskToIntNegativeMasksTestFixture: public testing::TestWithParam<std::string> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    std::string mask = "_" + testData.param;
                    std::replace_if(begin(mask),
                                    end(mask),
                                    ::ispunct,
                                    '_');
                    return mask;
                }
            };
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSolvedMaskParserTests,
        ruCubeSolvedMaskParserStringSolvedMaskToIntNegativeMasksTestFixture,
        ::testing::Values(
            "GA32FAFA;0345FBCD;FFCA4520",
            "FFA32FAFA;0345FBCD;FFCA452",
            "45687865;03;5FBCD;FFCA4520",
            "FAFA5-FA;AAAAAAAA;BBBBBBBB",
            "0000FFFF;00000000;00000000;00000000",
            "ffffffff;FFFFFFFF;FFFFFFFF",
            "CCCCCCCC:DDDDDDDD;12345678",
            ""
        ),
        ruCubeSolvedMaskParserStringSolvedMaskToIntNegativeMasksTestFixture::toString()
    );

    TEST_P(ruCubeSolvedMaskParserStringSolvedMaskToIntNegativeMasksTestFixture, stringSolvedMaskToIntNegativeMasksTest) {
        std::string masks = GetParam();
        const std::string expectedException = "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.";
        ASSERT_THROW (
            try {
                ruCubeSolvedMaskParser::stringSolvedMaskToInt(masks);
            } catch (const ruCubeSolvedMaskException &e) {
                std::cout << std::string(e.what()) << std::endl;
                ASSERT_EQ(expectedException, std::string(e.what()));
                throw;
            },
            ruCubeSolvedMaskException
        );

    }
}

namespace {
    class ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleCorrectMasksTestFixture: public testing::TestWithParam<std::tuple<std::string, ruCubeSolvedMaskPair>> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    auto [mask, expected] = testData.param;
                    std::replace(begin(mask), end(mask), ';', '_');
                    return mask;
                }
            };
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSolvedMaskParserTests,
        ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleCorrectMasksTestFixture,
        ::testing::ValuesIn(testDataGenerators::combine2VectorsLinear<std::string, ruCubeSolvedMaskPair> (
            {
                "111111111111;1111111",
                "000000000000;0000000",
                "111111111111;0000000",
                "000000000000;1111111",
                "101010101010;1010101",
                "010101010101;0101010",
                "000001010101;1101110",
            },
            {
                { 0x0000003F'0000003F, 0x0000007F },
                { 0x00000000'00000000, 0x00000000 },
                { 0x0000003F'0000003F, 0x00000000 },
                { 0x00000000'00000000, 0x0000007F },
                { 0x0000003F'00000000, 0x00000055 },
                { 0x00000000'0000003F, 0x0000002A },
                { 0x00000000'0000000F, 0x0000006E },
            }
        )),
        ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleCorrectMasksTestFixture::toString()
    );

    TEST_P(ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleCorrectMasksTestFixture, stringSolvedMaskToIntSimpleCorrectMasksTest) {
        const auto &[maskStr, expected] = GetParam();
        ruCubeSolvedMaskPair masks;
        ASSERT_NO_THROW(masks = ruCubeSolvedMaskParser::stringSolvedMaskToIntSimple(maskStr));
        ASSERT_EQ(expected, masks);
    }
}

namespace {
    class ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleNegativeMasksTestFixture: public testing::TestWithParam<std::string> {
        public:
            struct toString {
                template <class ParamType>
                std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                    std::string mask = "_" + testData.param;
                    std::replace_if(begin(mask),
                                    end(mask),
                                    ::ispunct,
                                    '_');
                    return mask;
                }
            };
    };

    INSTANTIATE_TEST_SUITE_P (
        ruCubeSolvedMaskParserTests,
        ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleNegativeMasksTestFixture,
        ::testing::Values(
            "111111111111;1111211",
            "000200000000;0000000",
            "111111211111;0002000",
            "0000;0000000;1111111",
            "1001010101010;1010101",
            "0f0101010101;01010100",
            ""
        ),
        ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleNegativeMasksTestFixture::toString()
    );

    TEST_P(ruCubeSolvedMaskParserStringSolvedMaskToIntSimpleNegativeMasksTestFixture, stringSolvedMaskToIntSimpleCorrectMasksNegativeTest) {
        std::string masks = GetParam();
        const std::string expectedException = "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.";
        ASSERT_THROW (
            try {
                ruCubeSolvedMaskParser::stringSolvedMaskToIntSimple(masks);
            } catch (const ruCubeSolvedMaskException &e) {
                std::cout << std::string(e.what()) << std::endl;
                ASSERT_EQ(expectedException, std::string(e.what()));
                throw;
            },
            ruCubeSolvedMaskException
        );

    }
}

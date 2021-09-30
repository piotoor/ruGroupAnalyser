#include "gtest/gtest.h"
#include "ruCubeSolvedMaskParser.h"
#include "ruException.h"
#include <vector>
#include <string>

// co, cp, ep
using ruCubeSolvedMaskPair = std::pair<uint64_t, uint32_t>;

TEST(ruCubeSolvedMaskParserTest, stringSolvedMaskToIntCorrectMasksTest) {
    std::vector<std::string> masksStr {
        "FA32FAFA;0345FBCD;FFCA4520",
        "FA32FAFA;0345FBCD;FFCA4520",
        "45687865;0345FBCD;FFCA4520",
        "FAFAFAFA;AAAAAAAA;BBBBBBBB",
        "00000000;00000000;00000000",
        "FFFFFFFF;FFFFFFFF;FFFFFFFF",
        "CCCCCCCC;DDDDDDDD;12345678",
        "01010101;01010101;00000000",
    };

    std::vector<ruCubeSolvedMaskPair> expectedMasks {
        { 0xFA32FAFA0345FBCD, 0xFFCA4520 },
        { 0xFA32FAFA0345FBCD, 0xFFCA4520 },
        { 0x456878650345FBCD, 0xFFCA4520 },
        { 0xFAFAFAFAAAAAAAAA, 0xBBBBBBBB },
        { 0x0000000000000000, 0x00000000 },
        { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFF },
        { 0xCCCCCCCCDDDDDDDD, 0x12345678 },
        { 0x0101010101010101, 0x00000000 },
    };

    for (uint8_t i = 0; i < size(expectedMasks); ++i) {
        auto masks = ruCubeSolvedMaskParser::stringSolvedMaskToInt(masksStr[i]);
        ASSERT_EQ(expectedMasks[i], masks);

    }
}

TEST(ruCubeSolvedMaskParserTest, stringSolvedMaskToIntNegativeTest) {
    std::vector<std::string> masksStr {
        "GA32FAFA;0345FBCD;FFCA4520",
        "FFA32FAFA;0345FBCD;FFCA452",
        "45687865;03;5FBCD;FFCA4520",
        "FAFA5-FA;AAAAAAAA;BBBBBBBB",
        "0000FFFF;00000000;00000000;00000000",
        "ffffffff;FFFFFFFF;FFFFFFFF",
        "CCCCCCCC:DDDDDDDD;12345678",
        "",
    };

    std::string expectedException = "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.";

    uint8_t i = 0;
    for (; i < size(masksStr); ++i) {
        std::string exceptionMessage;
        try {
            auto masksInt = ruCubeSolvedMaskParser::stringSolvedMaskToInt(masksStr[i]);
        } catch (const ruCubeSolvedMaskException &e) {
            exceptionMessage = e.what();
        }
        ASSERT_EQ(expectedException, exceptionMessage);
    }
    ASSERT_EQ(size(masksStr), i);
}


TEST(ruCubeSolvedMaskParserTest, stringSolvedMaskToIntSimpleCorrectMasksTest) {
    std::vector<std::string> masksStr {
        "111111111111;1111111",
        "000000000000;0000000",
        "111111111111;0000000",
        "000000000000;1111111",
        "101010101010;1010101",
        "010101010101;0101010",
        "000001010101;1101110",
    };

    std::vector<ruCubeSolvedMaskPair> expectedMasks {
        { 0x0000003F'0000003F, 0x0000007F },
        { 0x00000000'00000000, 0x00000000 },
        { 0x0000003F'0000003F, 0x00000000 },
        { 0x00000000'00000000, 0x0000007F },

        { 0x0000003F'00000000, 0x00000055 },
        { 0x00000000'0000003F, 0x0000002A },
        { 0x00000000'0000000F, 0x0000006E },
    };

    for (uint8_t i = 0; i < size(expectedMasks); ++i) {
        auto masks = ruCubeSolvedMaskParser::stringSolvedMaskToIntSimple(masksStr[i]);
        ASSERT_EQ(expectedMasks[i], masks);
    }
}

TEST(ruCubeSolvedMaskParserTest, stringSolvedMaskToIntSimpleCorrectMasksNegativeTest) {
    std::vector<std::string> masksStr {
        "111111111111;1111211",
        "000200000000;0000000",
        "111111211111;0002000",
        "0000;0000000;1111111",
        "1001010101010;1010101",
        "0f0101010101;01010100",
        "",
    };

    std::string expectedException = "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.";

    uint8_t i = 0;
    for (; i < size(masksStr); ++i) {
        std::string exceptionMessage;
        try {
            auto masks = ruCubeSolvedMaskParser::stringSolvedMaskToIntSimple(masksStr[i]);
        } catch (const ruCubeSolvedMaskException &e) {
            exceptionMessage = e.what();
        }
        ASSERT_EQ(expectedException, exceptionMessage);
    }
    ASSERT_EQ(size(masksStr), i);
}


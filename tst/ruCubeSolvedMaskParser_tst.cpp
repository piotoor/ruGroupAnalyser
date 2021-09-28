#include "gtest/gtest.h"
#include "ruCubeSolvedMaskParser.h"
#include "ruException.h"
#include <vector>
#include <string>

// co, cp, ep
using ruCubeSolvedMaskPair = std::pair<uint64_t, uint32_t>;

TEST(ruCubeSolvedMaskParserTest, correctMasksTest) {
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

TEST(ruCubeSolvedMaskParserTest, negativeTest) {
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

    std::vector<std::string> expectedExceptions {
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
        "ruCubeSolvedMaskException: Parsing exception. Invalid cube solved mask definition.",
    };

    uint8_t i = 0;
    for (; i < size(expectedExceptions); ++i) {
        std::string exceptionMessage;
        try {
            auto masksInt = ruCubeSolvedMaskParser::stringSolvedMaskToInt(masksStr[i]);
        } catch (const ruCubeSolvedMaskException &e) {
            exceptionMessage = e.what();
        }
        ASSERT_EQ(expectedExceptions[i], exceptionMessage);
    }
    ASSERT_EQ(size(expectedExceptions), i);
}

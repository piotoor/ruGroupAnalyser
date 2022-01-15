#include "gtest/gtest.h"
#include "ruCubeScrambleParser.h"
#include "ruException.h"


TEST(ruCubeScrambleParserTest, vectorScrambleToStringScrambleTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        { R, R2, Ri, U, U2, Ui },
        { R },
        { R2 },
        { Ri },
        { U },
        { U2 },
        { Ui },
        { R, U },
        { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
    };

    std::vector<std::string> expectedScrambles {
        "R R2 R' U U2 U'",
        "R",
        "R2",
        "R'",
        "U",
        "U2",
        "U'",
        "R U",
        "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        std::string scramble = ruCubeScrambleParser::vectorScrambleToStringScramble(scrambles[i]);
        ASSERT_EQ(expectedScrambles[i], scramble);
    }
}

TEST(ruCubeScrambleParserTest, vectorScrambleToStringScrambleCompressSolutionTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        { R, R2, Ri, U, U2, Ui },
        { R },
        { R2 },
        { Ri },
        { U },
        { U2 },
        { Ui },
        { R, U },
        { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
    };

    std::vector<std::string> expectedScrambles {
        "RR2R'UU2U'",
        "R",
        "R2",
        "R'",
        "U",
        "U2",
        "U'",
        "RU",
        "RURURUR'U'R2U2R2U2RU'R2U2R2U2R2U'"
    };

    const bool compressSolution = true;
    for (uint8_t i = 0; i < size(scrambles); ++i) {
        std::string scramble = ruCubeScrambleParser::vectorScrambleToStringScramble(scrambles[i], compressSolution);
        ASSERT_EQ(expectedScrambles[i], scramble);
    }
}

TEST(ruCubeScrambleParserTest, vectorScrambleToStringScrambleNegativeTest) {
    std::vector<std::vector<uint8_t>> scrambles {
        { R, R2, Ri, 12, U, U2, Ui, 11, 8 },
        { R, 15 },
        { R2, 7, 99, 121 },
        { Ri, 7 },
        { U, 7 },
        { 7, 7, 7, 7, 7, 7, U2, 8 },
        { Ui, 14 },
        { R, 12, U },
        { R, U, R, 9, U, R, U, 9, Ri, Ui, R2, U2, R2, U2, R, 9, Ui, R2, U2, R2, U2, R2, Ui }
    };

    std::vector<std::string> expectedScrambles {
        "R R2 R' U U2 U'",
        "R",
        "R2",
        "R'",
        "U",
        "U2",
        "U'",
        "R U",
        "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        std::string scramble = ruCubeScrambleParser::vectorScrambleToStringScramble(scrambles[i]);
        ASSERT_EQ(expectedScrambles[i], scramble);
    }
}

TEST(ruCubeScrambleParserTest, stringScrambleToVectorScrambleCleanInputTest) {
    std::vector<std::string> scrambles {
        "R R2 R' U U2 U'",
        "R",
        "R2",
        "R'",
        "U",
        "U2",
        "U'",
        "R U",
        "R U R U R U R' U' R2 U2 R2 U2 R U' R2 U2 R2 U2 R2 U'"
    };

    std::vector<std::vector<uint8_t>> expectedScrambles {
        { R, R2, Ri, U, U2, Ui },
        { R },
        { R2 },
        { Ri },
        { U },
        { U2 },
        { Ui },
        { R, U },
        { R, U, R, U, R, U, Ri, Ui, R2, U2, R2, U2, R, Ui, R2, U2, R2, U2, R2, Ui }
    };

    for (uint8_t i = 0; i < size(scrambles); ++i) {
        std::vector<uint8_t> scramble;
        ASSERT_NO_THROW(scramble = ruCubeScrambleParser::stringScrambleToVectorScramble(scrambles[i]));
        ASSERT_EQ(expectedScrambles[i], scramble);
    }
}

TEST(ruCubeScrambleParserTest, stringScrambleToVectorScrambleInvalidInputTest) {
    std::vector<std::string> scrambles {
        "RR2 R'rU U2 U'",
        "RXCV",
        "R2XVCXVCCXVCXV",
        "'''' 12341234213412342134 QWEQWEQWEwqeqweqweR'",
        "U3",
        "U2    2",
        "U'",
        "R';';';;;;;::[]{}[]]][]}}}!@#$%^&*()-=+______0,.<>/???`~ U",
        "R U R U R U R'YUI H      U' R2vbnnbvnbvnbvnvb%^^%%^5645665^%%$#$#234#24 U2 R2 U2 R U' R22 U2 R3 U1 R2 U'"
    };

    std::string expectedException = "ruCubeScrambleException: Parsing exception. Invalid scramble.";
    uint8_t i = 0;
    for (; i < size(scrambles); ++i) {
        try {
            auto scramble = ruCubeScrambleParser::stringScrambleToVectorScramble(scrambles[i]);
        } catch (const ruCubeScrambleException &e) {
            std::cout << "piotoor = " << std::string(e.what()) << std::endl;
            ASSERT_EQ(expectedException, std::string(e.what()));
        }
    }
    ASSERT_EQ(size(scrambles), i);

}

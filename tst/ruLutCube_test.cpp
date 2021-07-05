#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"


TEST(ruLutCubeTest, initialStateTest) {
    ruLutCube cube;

    ASSERT_EQ (ruLutCube::solvedLexIndexCornersOrient, cube.getEdges());
    ASSERT_EQ (ruLutCube::solvedLexIndexCornersPerm, cube.getCornersPerm());
    ASSERT_EQ (ruLutCube::solvedLexIndexCornersOrient, cube.getCornersOrient());


    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruLutCubeTest, settersGettersTest) {
    ruLutCube cube;

    cube.setEdges(1234);
    cube.setCorners(3432243);
    ASSERT_EQ (1234, cube.getEdges());
    ASSERT_EQ (3432243, cube.getCorners());

    cube.reset();
    cube.setCube(1234, 423234);
    ASSERT_EQ (1234, cube.getEdges());
    ASSERT_EQ (423234, cube.getCorners());

    cube.reset();
    cube.setCornersPerm(2234);
    cube.setCornersOrient(34);
    ASSERT_EQ (2234, cube.getCornersPerm());
    ASSERT_EQ (34, cube.getCornersOrient());
}

TEST(ruLutCubeTest, cubeStateResetTest) {
    ruLutCube cube;
    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
    cube.setEdges(2234);
    cube.setCorners(344);
    ASSERT_FALSE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
    cube.reset();
    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
}

TEST(ruLutCubeTest, singleTurnTest) {
    ruLutCube cube;

    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));

    cube.turn(R);
    cube.turn(R);
    cube.turn(R);
    cube.turn(R);

    cube.turn(R2);
    cube.turn(R2);

    cube.turn(Ri);
    cube.turn(Ri);
    cube.turn(Ri);
    cube.turn(Ri);

    cube.turn(U);
    cube.turn(U);
    cube.turn(U);
    cube.turn(U);

    cube.turn(U2);
    cube.turn(U2);

    cube.turn(Ui);
    cube.turn(Ui);
    cube.turn(Ui);
    cube.turn(Ui);

    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));

    cube.turn(Ri);
    cube.turn(U);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(U);
    cube.turn(R);
    cube.turn(U);
    cube.turn(R2);

    cube.turn(R2);
    cube.turn(U2);
    cube.turn(R2);
    cube.turn(U2);
    cube.turn(R2);
    cube.turn(U2);
    cube.turn(R2);
    cube.turn(U2);
    cube.turn(R2);
    cube.turn(U2);
    cube.turn(R2);
    cube.turn(U2);

    cube.turn(Ri);
    cube.turn(U);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(U);
    cube.turn(R);
    cube.turn(U);
    cube.turn(R2);

    cube.turn(Ri);
    cube.turn(U);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(Ui);
    cube.turn(Ri);
    cube.turn(U);
    cube.turn(R);
    cube.turn(U);
    cube.turn(R2);

    ASSERT_TRUE (cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
}

TEST(ruLutCubeTest, singleTurnInversionTest) {
    ruLutCube cube;

    for (int trn = R; trn <= Ui; ++trn) {
        cube.turn(trn);
        ASSERT_FALSE(cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
        cube.inverseTurn(trn);
        ASSERT_TRUE(cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
    }

    cube.inverseTurn(R);
    cube.inverseTurn(R);
    cube.inverseTurn(R);
    cube.inverseTurn(R);

    cube.inverseTurn(R2);
    cube.inverseTurn(R2);

    cube.inverseTurn(Ri);
    cube.inverseTurn(Ri);
    cube.inverseTurn(Ri);
    cube.inverseTurn(Ri);

    cube.inverseTurn(U);
    cube.inverseTurn(U);
    cube.inverseTurn(U);
    cube.inverseTurn(U);

    cube.inverseTurn(U2);
    cube.inverseTurn(U2);

    cube.inverseTurn(Ui);
    cube.inverseTurn(Ui);
    cube.inverseTurn(Ui);
    cube.inverseTurn(Ui);

    cube.inverseTurn(R);
    cube.inverseTurn(R);
    cube.turn(R2);
    cube.turn(R);
    cube.turn(R);
    cube.inverseTurn(R2);

    cube.inverseTurn(Ri);
    cube.inverseTurn(Ri);
    cube.turn(R2);
    cube.turn(Ri);
    cube.turn(Ri);
    cube.inverseTurn(R2);

    cube.inverseTurn(U);
    cube.inverseTurn(U);
    cube.turn(U2);
    cube.turn(U);
    cube.turn(U);
    cube.inverseTurn(U2);

    cube.inverseTurn(Ui);
    cube.inverseTurn(Ui);
    cube.turn(U2);
    cube.turn(Ui);
    cube.turn(Ui);
    cube.inverseTurn(U2);

    ASSERT_TRUE(cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
}

TEST(ruLutCubeTest, scrambleAndScrambleInversionTest) {
    ruLutCube cube;

    const std::vector<uint8_t> moves{R, U, R2, U2, Ri, Ui, R, U, R, U, R2, Ui, Ri, Ui};
    cube.scramble(moves);

    cube.inverseScramble(moves);
    ASSERT_TRUE(cube.isSolved(ruLutCube::allEdgesMask, ruLutCube::allCornersMask));
}

TEST(ruLutCubeTest, isInDominoTest) {
    ruLutCube cube;

    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({R2, U2, R2, U2, R2, U2});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({R2, U, R2, Ui, R2, U, R2, U, R2, Ui, R2, Ui, R2, U, R2, U2, R2, Ui, R2, U2, R2, U2, R2, Ui, R2, Ui});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({R, U, Ri, U, R, U2, Ri});
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({R, U, Ri, U, R, U2, Ri});
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({U, R, U, Ri, U, R, Ui, Ri, U, R, U2, R});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({R2, U, Ri, Ui, Ri, Ui, Ri, U, R, U, Ri});
    ASSERT_FALSE(cube.isInDomino());
}

TEST(ruLutCubeTest, singleTurnNegativeTest) {
    ruLutCube cube;

    const std::vector<uint8_t> invalidTurns {
        6, 7, 8, 9, 10, 11, 12, 15, 20, 30, 100, 255
    };

    for (const auto &i: invalidTurns) {
        try {
            cube.turn(i);
        } catch (const ruCubeTurnException &e) {
            ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), e.what());
        }
    }
}

TEST(ruLutCubeTest, singleTurnInversionNegativeTest) {
    ruLutCube cube;

    const std::vector<uint8_t> invalidTurns {
        6, 7, 8, 9, 10, 11, 12, 15, 20, 30, 100, 255
    };

    for (const auto &i: invalidTurns) {
        try {
            cube.inverseTurn(i);
        } catch (const ruCubeTurnException &e) {
            ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), e.what());
        }
    }
}

TEST(ruLutCubeTest, scrambleNegativeTest) {
    ruLutCube cube;

    const std::vector<std::vector<uint8_t>> invalidScrambles {
        { 6 },
        { R, U, R2, U2, Ri, Ui, 10, U2, R2, 8, 10 },
        { R, U, R2, Ri, R2, Ri, 6 }
    };

    const std::vector<uint8_t> firstInvalidTurn {
        6,
        10,
        6
    };

    int i = 0;
    for (const auto &scr: invalidScrambles) {
        try {
            cube.scramble(scr);
        } catch (const ruCubeTurnException &e) {
            ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(firstInvalidTurn[i]) + ") out of range (which is [0:5])"), e.what());
        }
        ++i;
    }
}

TEST(ruLutCubeTest, scrambleInversionNegativeTest) {
    ruLutCube cube;

    const std::vector<std::vector<uint8_t>> invalidScrambleInversions {
        { 6 },
        { R, U, R2, U2, Ri, Ui, 10, U2, R2, 8, 10 },
        { R, U, R2, Ri, R2, Ri, 6 }
    };

    const std::vector<uint8_t> firstInvalidTurn {
        6,
        10,
        6
    };

    int i = 0;
    for (const auto &scr: invalidScrambleInversions) {
        try {
            cube.scramble(scr);
        } catch (const ruCubeTurnException &e) {
            ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(firstInvalidTurn[i]) + ") out of range (which is [0:5])"), e.what());
        }
        ++i;
    }
}

TEST(ruLutCubeTest, predefinedIsSolvedFilterTest) {
    const std::vector<std::vector<uint8_t>> scrambles {
        { R2, U2, R2, U2, R2, U2 },
        { R,  U,  Ri, U,  R,  U2, Ri, U2 },
        { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
        { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
        { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
        { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
    };

    const std::vector<std::pair<uint32_t, uint64_t>> filters {
        { ruLutCube::allEdgesMask,  ruLutCube::allCornersMask },
        { ruLutCube::allEdgesMask,  0x0 },
        { 0x0,                      ruLutCube::allCornersMask },
        { 0x0,                      0x0 },
        { 0x0,                      ruLutCube::allCornersOrientMask },
        { 0x0,                      ruLutCube::allCornersPermMask },
        { ruLutCube::allEdgesMask,  ruLutCube::allCornersOrientMask },
        { ruLutCube::allEdgesMask,  ruLutCube::allCornersPermMask },
    };

    const std::vector<std::vector<bool>> expected {
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, false, true,  false, true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, true,  false, true,  false, false, false, false },
        { false, true,  false, true,  false, true,  false, true  },
    };

    for (uint8_t i = 0 ; i < size(scrambles); ++i) {
        ruLutCube cube;
        cube.scramble(scrambles[i]);
        for (uint8_t j = 0; j < size(filters); ++j) {
            ASSERT_EQ(expected[i][j], cube.isSolved(filters[j].first, filters[j].second));
        }
    }
}

TEST(ruLutCubeTest, customIsSolvedFilterTest) {
    const std::vector<std::vector<uint8_t>> scrambles {
        { R2, U2, R2, U2, R2, U2 },
        { R,  U,  Ri, U,  R,  U2, Ri, U2 },
        { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
        { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
        { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
        { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
    };

    const std::vector<std::pair<uint32_t, uint64_t>> filters {
        { 0b0'0101010'111'0000'0,   0b111111'0001'0'000000000000000000000'111111'0000'0 },
        { 0b0'0101010'111'0000'0,   0b111111'0001'0'000000000000000000000'110111'0000'0 },
        { 0b0'0100010'010'0000'0,   0b000010'0001'0'000000000000000000000'111111'0000'0 },

        { 0b0'0101010'111'0000'0,   0b111111'0001'0'000000000000000000000'111111'0000'0 },
        { 0b0'0000010'000'0000'0,   0b000010'0000'0'000000000000000000000'100000'0000'0 },
        { 0b0'0101000'000'0000'0,   0b010000'0000'0'000000000000000000000'000100'0000'0 },

        { 0b0'0000010'000'0000'0,   0b000001'0000'0'000000000000000000000'100000'0000'0 },
        { 0b0'0100010'000'0000'0,   0b111001'0000'0'000000000000000000000'000000'0000'1 },
        { 0b0'0001000'000'0000'0,   0b101010'0100'1'000000000000000000000'100000'0000'0 },

        { 0b0'0001000'000'0000'1,   0b111111'0001'0'000000000000000000000'111111'0000'0 },
        { 0b0'1000000'000'0000'0,   0b000010'0000'0'000000000000000000000'100000'0000'0 },
        { 0b0'0010000'000'0000'0,   0b010000'0000'0'000000000000000000000'000100'0000'0 },

        { 0b0'0001000'000'0000'1,   0b010000'0000'0'000000000000000000000'000100'0000'0 },
        { 0b0'0001000'000'0000'1,   0b010000'0000'0'000000000000000000000'000100'0000'0 },
        { 0b0'0001000'000'0000'1,   0b010000'0000'0'000000000000000000000'000100'0000'0 },

        { 0b0'0101010'111'0000'0,   0b000000'0000'0'000000000000000000000'000000'0000'0 },
        { 0b0'0101010'000'0000'0,   0b000000'0000'1'000000000000000000000'000000'0000'1 },
        { 0b0'0101010'100'0000'1,   0b111111'1111'1'000000000000000000000'111111'1111'1 }

    };

    const std::vector<std::vector<bool>> expected {
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    true , true , false },
        { false, false, true,       false, true,  false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, false, false,    false, false, false,    true , false, false },
        { false, false, false,      false, false, true,     true,  true,  false,    false, false, true,     true,  true,  true,     true , false, false },
    };

    for (uint8_t i = 0 ; i < size(scrambles); ++i) {
        ruLutCube cube;
        cube.scramble(scrambles[i]);
        for (uint8_t j = 0; j < size(filters); ++j) {
            std::cout << "i = " << (int)i << "; j = " << (int) j << std::endl;
            ASSERT_EQ(expected[i][j], cube.isSolved(filters[j].first, filters[j].second));
        }
    }
}

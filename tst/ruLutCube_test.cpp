#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"


TEST(ruLutCubeTest, initialStateTest) {
    ruLutCube cube;

    ASSERT_EQ (ruLutCube::solvedLexIndexCornersOrient, cube.getEdges());
    ASSERT_EQ (ruLutCube::solvedLexIndexCornersPerm, cube.getCornersPerm());
    ASSERT_EQ (ruLutCube::solvedLexIndexCornersOrient, cube.getCornersOrient());

    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruLutCubeTest, settersGettersTest) {
    ruLutCube cube;

    cube.setEdges(1234);
    cube.setCorners(3432243);
    ASSERT_EQ (1234, cube.getEdges());
    ASSERT_EQ (3432243, cube.getCorners());

    cube.reset();
    cube.setCube(423234, 1234);
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
    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));

    cube.setEdges(2234);
    cube.setCorners(344);
    ASSERT_FALSE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));

    cube.reset();
    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
}

TEST(ruLutCubeTest, singleTurnTest) {
    ruLutCube cube;
    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));

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

    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));

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

    ASSERT_TRUE (cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
}

TEST(ruLutCubeTest, singleTurnInversionTest) {
    ruLutCube cube;

    for (int trn = R; trn <= Ui; ++trn) {
        cube.turn(trn);
        ASSERT_FALSE(cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
        cube.inverseTurn(trn);
        ASSERT_TRUE(cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
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

    ASSERT_TRUE(cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
}

TEST(ruLutCubeTest, scrambleAndScrambleInversionTest) {
    ruLutCube cube;

    const std::vector<uint8_t> moves{R, U, R2, U2, Ri, Ui, R, U, R, U, R2, Ui, Ri, Ui};
    cube.scramble(moves);

    cube.inverseScramble(moves);
    ASSERT_TRUE(cube.isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask));
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

    size_t i = 0;
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

    size_t i = 0;
    for (const auto &scr: invalidScrambleInversions) {
        try {
            cube.inverseScramble(scr);
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

    const std::vector<std::pair<uint64_t, uint32_t>> masks {
        { ruLutCube::allCornersMask,       ruLutCube::allEdgesMask },
        { 0x0,                             ruLutCube::allEdgesMask },
        { ruLutCube::allCornersMask,       0x0                     },
        { 0x0,                             0x0                     },
        { ruLutCube::allCornersOrientMask, 0x0                     },
        { ruLutCube::allCornersPermMask,   0x0                     },
        { ruLutCube::allCornersOrientMask, ruLutCube::allEdgesMask },
        { ruLutCube::allCornersPermMask,   ruLutCube::allEdgesMask },
    };

    const std::vector<std::vector<bool>> expected {
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, false, true,  false, true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, true,  false, true,  false, false, false, false },
        { false, true,  false, true,  false, true,  false, true  },
    };

    for (size_t scrInd = 0 ; scrInd < size(scrambles); ++scrInd) {
        ruLutCube cube;
        cube.scramble(scrambles[scrInd]);
        for (size_t mskInd = 0; mskInd < size(masks); ++mskInd) {
            auto &[cornersMask, edgesMask] = masks[mskInd];
            ASSERT_EQ(expected[scrInd][mskInd], cube.isSolved(cornersMask, edgesMask));
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

    const std::vector<std::pair<uint64_t, uint32_t>> masks {
        { 0b0001011111100000000000000000000000000111111, 0b111000000101010 },
        { 0b0001011111100000000000000000000000000111011, 0b111000000101010 },
        { 0b0001001000000000000000000000000000000111111, 0b010000000100010 },
        { 0b0001011111100000000000000000000000000111111, 0b111000000101010 },
        { 0b0000001000000000000000000000000000000000001, 0b000000000100000 },
        { 0b0000000001000000000000000000000000000001000, 0b000000000001010 },
        { 0b0000010000000000000000000000000000000000001, 0b000000000100000 },
        { 0b0000010011100000000000000000000000001000000, 0b000000000100010 },
        { 0b0100101010100000000000000000000000000000001, 0b000000000001000 },
        { 0b0001011111100000000000000000000000000111111, 0b000000010001000 },
        { 0b0000001000000000000000000000000000000000001, 0b000000000000001 },
        { 0b0000000001000000000000000000000000000001000, 0b000000000000100 },
        { 0b0000000001000000000000000000000000000001000, 0b000000010001000 },
        { 0b0000000001000000000000000000000000000001000, 0b000000010001000 },
        { 0b0000000001000000000000000000000000000001000, 0b000000010001000 },
        { 0b0000000000000000000000000000000000000000000, 0b111000000101010 },
        { 0b0000100000000000000000000000000000001000000, 0b000000000101010 },
        { 0b1111111111100000000000000000000011111111111, 0b100000010101010 },
    };

    const std::vector<std::vector<bool>> expected {
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    true , true , false },
        { false, false, true,       false, true,  false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, true,  true,     false, false, false,    false, false, false },
        { false, false, false,      false, false, false,    false, false, false,    false, false, false,    false, false, false,    true , false, false },
        { false, false, false,      false, false, true,     true,  true,  false,    false, false, true,     true,  true,  true,     true , false, false },
    };

    for (size_t scrInd = 0 ; scrInd < size(scrambles); ++scrInd) {
        ruLutCube cube;
        cube.scramble(scrambles[scrInd]);
        for (size_t mskInd = 0; mskInd < size(masks); ++mskInd) {
            auto &[cornersMask, edgesMask] = masks[mskInd];
            ASSERT_EQ(expected[scrInd][mskInd], cube.isSolved(cornersMask, edgesMask));
        }
    }
}

TEST(ruLutCubeTest, toStringTest) {
    std::vector<std::tuple<uint64_t, uint32_t>> cubes {
        { 0101112131415, 00234651 },
        { 0101112131415, 00234516 },
        { 0101112131415, 00234165 },
        { 0101112131415, 00231456 },

        { 0101112131415, 00213465 },
        { 0101112131415, 00123456 },
        { 0101112131415, 01023465 },
        { 0101114121513, 00234561 },

        { 0101114121513, 00234615 },
        { 0101114121513, 00234156 },
        { 0101114121513, 00231465 },
        { 0101114121513, 00213456 },

        { 0101114121513, 00123465 },
        { 0101114121513, 01023456 },
        { 0101113151214, 00234561 },
        { 0101113151214, 00234615 },
    };

    std::vector<std::string> expectedStrCubes {
        "000102030405;0234651",
        "000102030405;0234516",
        "000102030405;0234165",
        "000102030405;0231456",

        "000102030405;0213465",
        "000102030405;0123456",
        "000102030405;1023465",
        "000104020503;0234561",

        "000104020503;0234615",
        "000104020503;0234156",
        "000104020503;0231465",
        "000104020503;0213456",

        "000104020503;0123465",
        "000104020503;1023456",
        "000103050204;0234561",
        "000103050204;0234615",
    };

    ruCubeStateConverter conv;
    for (size_t i = 0; i < size(expectedStrCubes); ++i) {
        const auto &[corners, edges] = cubes[i];
        ruLutCube cube(conv.intCornersToLexIndexCornersOrient(corners), conv.intCornersToLexIndexCornersPerm(corners), conv.intEdgesToLexIndexEdges(edges));
        ASSERT_EQ(expectedStrCubes[i], cube.toString());
    }
}

TEST(ruLutCubeTest, toStringWithIgnoredTest) {
    std::vector<std::tuple<uint64_t, uint32_t, std::bitset<ruBaseCube::noOfCorners>, std::bitset<ruBaseCube::noOfCorners>, std::bitset<ruBaseCube::noOfEdges>>> cubes {
        { 0101112131415, 00234651, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00234516, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00234165, 0b000000, 0b000000, 0b0000000 },
        { 0101112131415, 00231456, 0b000000, 0b000000, 0b0000000 },

        { 0101112131415, 00213465, 0b000000, 0b111111, 0b0000000 },
        { 0101112131415, 00123456, 0b111111, 0b000000, 0b0000000 },
        { 0101112131415, 01023465, 0b000000, 0b000000, 0b1111111 },
        { 0101114121513, 00234561, 0b111111, 0b111111, 0b1111111 },

        { 0101114121513, 00234615, 0b100000, 0b100000, 0b1000000 },
        { 0101114121513, 00234156, 0b010000, 0b010000, 0b0100000 },
        { 0101114121513, 00231465, 0b001000, 0b001000, 0b0010000 },
        { 0101114121513, 00213456, 0b000100, 0b000100, 0b0001000 },

        { 0101114121513, 00123465, 0b000010, 0b000010, 0b0000100 },
        { 0101114121513, 01023456, 0b000001, 0b000001, 0b0000010 },
        { 0101113151214, 00234561, 0b111100, 0b111100, 0b0000001 },
        { 0101113151214, 00234615, 0b111100, 0b111100, 0b0000011 },
    };

    std::vector<std::string> expectedStrCubes {
        "000102030405;0234651",
        "000102030405;0234516",
        "000102030405;0234165",
        "000102030405;0231456",

        "0-0-0-0-0-0-;0213465",
        "-0-1-2-3-4-5;0123456",
        "000102030405;-------",
        "------------;-------",

        "00010402--03;0234-15",
        "0001--020503;02341-6",
        "0001040205--;0231-65",
        "000104--0503;021-456",

        "00--04020503;01-3465",
        "--0104020503;-023456",
        "0001--------;-234561",
        "0001--------;-2346-5",
    };

    ruCubeStateConverter conv;

    for (size_t i = 0; i < size(expectedStrCubes); ++i) {
        const auto &[corners, edges, coi, cpi, epi] = cubes[i];
        ruLutCubeIgnoredPieces ignoredPieces { coi, cpi, epi };
        ruLutCube cube( conv.intCornersToLexIndexCornersOrient(corners),
                        conv.intCornersToLexIndexCornersPerm(corners),
                        conv.intEdgesToLexIndexEdges(edges),
                        ignoredPieces);
        ASSERT_EQ(expectedStrCubes[i], cube.toString());
    }
}

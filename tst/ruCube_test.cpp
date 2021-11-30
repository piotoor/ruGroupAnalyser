#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"


TEST(ruCubeTest, initialStateTest) {
    ruCube cube;

    ASSERT_EQ (ruCube::solvedEdges, cube.getEdges());
    ASSERT_EQ (ruCube::solvedCorners, cube.getCorners());
    ASSERT_TRUE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruCubeTest, settersGettersTest) {
    ruCube cube;

    cube.setEdges(076543210);
    cube.setCorners(01511413121110);
    ASSERT_EQ (076543210, cube.getEdges());
    ASSERT_EQ (01511413121110, cube.getCorners());

    cube.setCube(01011112151413, 001234765);
    ASSERT_EQ (001234765, cube.getEdges());
    ASSERT_EQ (01011112151413, cube.getCorners());
}

TEST(ruCubeTest, cubeStateResetTest) {
    ruCube cube;

    ASSERT_TRUE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
    cube.setEdges(076543210);
    cube.setCorners(01511413121110);
    ASSERT_FALSE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
    cube.reset();
    ASSERT_TRUE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
}

TEST(ruCubeTest, singleTurnTest) {
    ruCube cube;

    cube.turn(R);
    ASSERT_EQ(00126345, cube.getEdges());
    ASSERT_EQ(0251112402344, cube.getCorners());
    cube.turn(U);
    ASSERT_EQ(06012345, cube.getEdges());
    ASSERT_EQ(0402511122344, cube.getCorners());
    cube.turn(R2);
    ASSERT_EQ(06014523, cube.getEdges());
    ASSERT_EQ(0232511444012, cube.getCorners());
    cube.turn(U2);
    ASSERT_EQ(01460523, cube.getEdges());
    ASSERT_EQ(0114423254012, cube.getCorners());
    cube.turn(Ri);
    ASSERT_EQ(01465230, cube.getEdges());
    ASSERT_EQ(0454423202241, cube.getCorners());
    cube.turn(Ui);
    ASSERT_EQ(04651230, cube.getEdges());
    ASSERT_EQ(0442320452241, cube.getCorners());

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

    ASSERT_EQ(04651230, cube.getEdges());
    ASSERT_EQ(0442320452241, cube.getCorners());
}

TEST(ruCubeTest, singleTurnInversionTest) {
    ruCube cube;

    for (int trn = R; trn <= Ui; ++trn) {
        cube.turn(trn);
        ASSERT_FALSE(cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
        cube.inverseTurn(trn);
        ASSERT_TRUE(cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
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

    ASSERT_TRUE(cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
}

TEST(ruCubeTest, scrambleTest) {
    ruCube cube;

    cube.scramble({ R, U, R2, U2, Ri, Ui });
    ASSERT_EQ(04651230, cube.getEdges());
    ASSERT_EQ(0442320452241, cube.getCorners());

    cube.scramble({ R2, U2, R2, U2, R, U, Ri, Ui });
    ASSERT_EQ(04130265, cube.getEdges());
    ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, scrambleInversionTest) {
    ruCube cube;

    cube.inverseScramble({ U, R, U2, R2, Ui, Ri });
    ASSERT_EQ(04651230, cube.getEdges());
    ASSERT_EQ(0442320452241, cube.getCorners());

    cube.inverseScramble({ U, R, Ui, Ri, U2, R2, U2, R2 });
    ASSERT_EQ(04130265, cube.getEdges());
    ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, isInDominoTest) {
    ruCube cube;

    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({ R2, U2, R2, U2, R2, U2 });
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({ R2, U, R2, Ui, R2, U, R2, U, R2, Ui, R2, Ui, R2, U, R2, U2, R2, Ui, R2, U2, R2, U2, R2, Ui, R2, Ui });
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({ R, U, Ri, U, R, U2, Ri });
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({ R, U, Ri, U, R, U2, Ri });
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({ U, R, U, Ri, U, R, Ui, Ri, U, R, U2, R });
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({ R2, U, Ri, Ui, Ri, Ui, Ri, U, R, U, Ri });
    ASSERT_FALSE(cube.isInDomino());
}

TEST(ruCubeTest, singleTurnNegativeTest) {
    ruCube cube;

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

TEST(ruCubeTest, singleTurnInversionNegativeTest) {
    ruCube cube;

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

TEST(ruCubeTest, scrambleNegativeTest) {
    ruCube cube;

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

TEST(ruCubeTest, scrambleInversionNegativeTest) {
    ruCube cube;

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

TEST(ruCubeTest, predefinedIsSolvedFilterTest) {
    const std::vector<std::vector<uint8_t>> scrambles {
        { R2, U2, R2, U2, R2, U2 },
        { R,  U,  Ri, U,  R,  U2, Ri, U2 },
        { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
        { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
        { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
        { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
    };

    const std::vector<std::pair<uint64_t, uint32_t>> masks {
        { ruCube::allCornersMask,         ruCube::allEdgesMask },
        { 00,                             ruCube::allEdgesMask },
        { ruCube::allCornersMask,         00                   },
        { 00,                             00                   },
        { ruCube::cornersOrientationMask, 00                   },
        { ruCube::cornersPermutationMask, 00                   },
        { ruCube::cornersOrientationMask, ruCube::allEdgesMask },
        { ruCube::cornersPermutationMask, ruCube::allEdgesMask }
    };

    const std::vector<std::vector<bool>> expected {
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, false, true,  false, true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, false, true,  true,  true,  true,  false, false },
        { false, true,  false, true,  false, false, false, false },
        { false, true,  false, true,  false, true,  false, true  }
    };

    for (size_t scrInd = 0 ; scrInd < size(scrambles); ++scrInd) {
        ruCube cube;
        cube.scramble(scrambles[scrInd]);
        for (size_t mskInd = 0; mskInd < size(masks); ++mskInd) {
            auto &[cornersMask, edgesMask] = masks[mskInd];
            ASSERT_EQ(expected[scrInd][mskInd], cube.isSolved(cornersMask, edgesMask));
        }
    }
}

TEST(ruCubeTest, customIsSolvedFilterTest) {
    const std::vector<std::vector<uint8_t>> scrambles {
        { R2, U2, R2, U2, R2, U2 },
        { R,  U,  Ri, U,  R,  U2, Ri, U2 },
        { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
        { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
        { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
        { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
    };

    const std::vector<std::pair<uint64_t, uint32_t>> masks {
        { 0000000000077, 00000070 },
        { 0000000000007, 00000070 },
        { 0000000000070, 00000070 },

        { 0000000007700, 00000070 },
        { 0000000000700, 00000070 },
        { 0000000007000, 00000070 },

        { 0000000770000, 00000070 },
        { 0000000070000, 00000070 },
        { 0000000700000, 00000070 },

        { 0000000000077, 07000070 },
        { 0000000000007, 07000070 },
        { 0000000000070, 07000070 },

        { 0000000007700, 07000070 },
        { 0000000000700, 07000070 },
        { 0000000007000, 07000070 },

        { 0000000770000, 07000070 },
        { 0000000070000, 07000070 },
        { 0000000700000, 07000070 }
    };

    const std::vector<std::vector<bool>> expected {
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false },
        { true,  true,  true,       true,  true,  true,     false, true,  false,    false, false, false,    false, false, false,    false, false, false },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true  },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false },
        { false, false, true,       true,  true,  true,     false, false, false,    false, false, true,     true,  true,  true,     false, false, false },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true  }
    };

    for (size_t scrInd = 0 ; scrInd < size(scrambles); ++scrInd) {
        ruCube cube;
        cube.scramble(scrambles[scrInd]);
        for (size_t mskInd = 0; mskInd < size(masks); ++mskInd) {
            auto &[cornersMask, edgesMask] = masks[mskInd];
            ASSERT_EQ(expected[scrInd][mskInd], cube.isSolved(cornersMask, edgesMask));
        }
    }
}

TEST(ruCubeTest, getPartialEdgesTest) {
    const std::vector<uint32_t> edgesMasks {
        0b0000001,
        0b0000010,
        0b0000100,
        0b0001000,
        0b0010000,
        0b0100000,
        0b1000000,

        0b1111111,
        0b0000111,
        0b0001111,
        0b1111000,
        0b0000000,
    };

    const std::vector<uint32_t> intEdges {
        00123456,
        06543210,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialEdges {
        {   07777776,
            07777757,
            07777477,
            07773777,
            07727777,
            07177777,
            00777777,

            00123456,
            07777456,
            07773456,
            00123777,
            07777777    },

        {   06777777,
            07577777,
            07747777,
            07773777,
            07777277,
            07777717,
            07777770,

            06543210,
            06547777,
            06543777,
            07773210,
            07777777    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialEdges); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(edgesMasks); ++maskInd) {
            cube.setEdges(intEdges[expectedInd]);
            ASSERT_EQ(expectedPartialEdges[expectedInd][maskInd], cube.getPartialEdges(edgesMasks[maskInd]));
        }
    }
}

TEST(ruCubeTest, getPartialCornersPermTest) {
    const std::vector<uint64_t> cornersMasks {
        0b000001,
        0b000010,
        0b000100,
        0b001000,
        0b010000,
        0b100000,

        0b111111,
        0b000111,
        0b001111,
        0b111000,
        0b000000,
        0b110010
    };

    const std::vector<uint64_t> intCorners {
        0000102030405,
        0050403020100,
        0442142251013,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialCornersPerms {
        {   0777775,
            0777747,
            0777377,
            0772777,
            0717777,
            0077777,

            0012345,
            0777345,
            0772345,
            0012777,
            0777777,
            0017747    },

        {   0577777,
            0747777,
            0773777,
            0777277,
            0777717,
            0777770,

            0543210,
            0543777,
            0543277,
            0777210,
            0777777,
            0747710    },

        {   0777577,
            0477777,
            0777773,
            0772777,
            0717777,
            0777707,

            0412503,
            0477573,
            0472573,
            0712707,
            0777777,
            0417707    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialCornersPerms); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(cornersMasks); ++maskInd) {
            cube.setCorners(intCorners[expectedInd]);
            ASSERT_EQ(expectedPartialCornersPerms[expectedInd][maskInd], cube.getPartialCornersPerm(cornersMasks[maskInd]));
        }
    }
}

TEST(ruCubeTest, getPartialCornersOrientTest) {
    const std::vector<uint64_t> cornersMasks {
        0b000001,
        0b000010,
        0b000100,
        0b001000,
        0b010000,
        0b100000,

        0b111111,
        0b000111,
        0b001111,
        0b111000,
        0b000000,
        0b110010
    };

    const std::vector<uint64_t> intCorners {
        0000102030405,
        0151413121110,
        0442142251013,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialCornersOrients {
        {   0777770,
            0777707,
            0777077,
            0770777,
            0707777,
            0077777,

            0000000,
            0777000,
            0770000,
            0000777,
            0777777,
            0007707    },

        {   0177777,
            0717777,
            0771777,
            0777177,
            0777717,
            0777771,

            0111111,
            0111777,
            0111177,
            0777111,
            0777777,
            0717711    },

        {   0777277,
            0477777,
            0777771,
            0774777,
            0727777,
            0777717,

            0424211,
            0477271,
            0474271,
            0724717,
            0777777,
            0427717    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialCornersOrients); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(cornersMasks); ++maskInd) {
            cube.setCorners(intCorners[expectedInd]);
            ASSERT_EQ(expectedPartialCornersOrients[expectedInd][maskInd], cube.getPartialCornersOrient(cornersMasks[maskInd]));
        }
    }
}

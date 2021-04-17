#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"


TEST(ruCubeTest, initialStateTest) {
    ruCube cube;

    ASSERT_EQ (ruCube::solvedEdges, cube.getEdges());
    ASSERT_EQ (ruCube::solvedCorners, cube.getCorners());
    ASSERT_TRUE (cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruCubeTest, settersGettersTest) {
    ruCube cube;
    cube.setEdges(076543210);
    cube.setCorners(01511413121110);
    ASSERT_EQ (076543210, cube.getEdges());
    ASSERT_EQ (01511413121110, cube.getCorners());

    cube.setCube(001234765, 01011112151413);
    ASSERT_EQ (001234765, cube.getEdges());
    ASSERT_EQ (01011112151413, cube.getCorners());
}

TEST(ruCubeTest, cubeStateResetTest) {
    ruCube cube;
    ASSERT_TRUE (cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
    cube.setEdges(076543210);
    cube.setCorners(01511413121110);
    ASSERT_FALSE (cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
    cube.reset();
    ASSERT_TRUE (cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
}

TEST(ruCubeTest, singleTurnTest) {
	/*
	 *	0 - R
	 * 	1 - R2
	 * 	2 - R'
	 *  3 - U
	 *  4 - U2
	 *  5 - U'
	 *
	 * const unsigned long int edgesSolved = 00123456;
	 * const unsigned long int cornersSolved = 0000102030405;
	 */
    ruCube cube;

	cube.turn(R); // R
	ASSERT_EQ(00126345, cube.getEdges());
	ASSERT_EQ(0251112402344, cube.getCorners());
	cube.turn(U); // U
	ASSERT_EQ(06012345, cube.getEdges());
	ASSERT_EQ(0402511122344, cube.getCorners());
	cube.turn(R2); // R2
	ASSERT_EQ(06014523, cube.getEdges());
	ASSERT_EQ(0232511444012, cube.getCorners());
	cube.turn(U2); // U2
	ASSERT_EQ(01460523, cube.getEdges());
	ASSERT_EQ(0114423254012, cube.getCorners());
	cube.turn(Ri); // R'
	ASSERT_EQ(01465230, cube.getEdges());
	ASSERT_EQ(0454423202241, cube.getCorners());
	cube.turn(Ui); // U'
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
        ASSERT_FALSE(cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
        cube.inverseTurn(trn);
        ASSERT_TRUE(cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
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

    ASSERT_TRUE(cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
}

TEST(ruCubeTest, scrambleTest) {
    	/*
	 *	0 - R
	 * 	1 - R2
	 * 	2 - R'
	 *  3 - U
	 *  4 - U2
	 *  5 - U'
	 */
    ruCube cube;
    std::vector<uint8_t> moves{R, U, R2, U2, Ri, Ui};
    cube.scramble(moves);
    ASSERT_EQ(04651230, cube.getEdges());
	ASSERT_EQ(0442320452241, cube.getCorners());

	cube.scramble({R2, U2, R2, U2, R, U, Ri, Ui});
	ASSERT_EQ(04130265, cube.getEdges());
	ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, scrambleInversionTest) {
    ruCube cube;
    std::vector<uint8_t> moves{U, R, U2, R2, Ui, Ri};
    cube.inverseScramble(moves);
    ASSERT_EQ(04651230, cube.getEdges());
	ASSERT_EQ(0442320452241, cube.getCorners());

	cube.inverseScramble({U, R, Ui, Ri, U2, R2, U2, R2});
	ASSERT_EQ(04130265, cube.getEdges());
	ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, isInDominoTest) {
    ruCube cube;
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
    std::vector<std::vector<uint8_t>> invalidScrambles {
        { 6 },
        { R, U, R2, U2, Ri, Ui, 10, U2, R2, 8, 10 },
        { R, U, R2, Ri, R2, Ri, 6 }
    };

    std::vector<uint8_t> firstInvalidTurn {
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

TEST(ruCubeTest, scrambleInversionNegativeTest) {
    ruCube cube;
    std::vector<std::vector<uint8_t>> invalidScrambleInversions {
        { 6 },
        { R, U, R2, U2, Ri, Ui, 10, U2, R2, 8, 10 },
        { R, U, R2, Ri, R2, Ri, 6 }
    };

    std::vector<uint8_t> firstInvalidTurn {
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

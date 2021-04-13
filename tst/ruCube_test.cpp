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

	cube.turn(0); // R
	ASSERT_EQ(00126345, cube.getEdges());
	ASSERT_EQ(0251112402344, cube.getCorners());
	cube.turn(3); // U
	ASSERT_EQ(06012345, cube.getEdges());
	ASSERT_EQ(0402511122344, cube.getCorners());
	cube.turn(1); // R2
	ASSERT_EQ(06014523, cube.getEdges());
	ASSERT_EQ(0232511444012, cube.getCorners());
	cube.turn(4); // U2
	ASSERT_EQ(01460523, cube.getEdges());
	ASSERT_EQ(0114423254012, cube.getCorners());
	cube.turn(2); // R'
	ASSERT_EQ(01465230, cube.getEdges());
	ASSERT_EQ(0454423202241, cube.getCorners());
	cube.turn(5); // U'
	ASSERT_EQ(04651230, cube.getEdges());
	ASSERT_EQ(0442320452241, cube.getCorners());

	cube.turn(0);
	cube.turn(0);
	cube.turn(0);
	cube.turn(0);

	cube.turn(1);
	cube.turn(1);

	cube.turn(2);
	cube.turn(2);
	cube.turn(2);
	cube.turn(2);

	cube.turn(3);
	cube.turn(3);
	cube.turn(3);
	cube.turn(3);

	cube.turn(4);
	cube.turn(4);

	cube.turn(5);
	cube.turn(5);
	cube.turn(5);
	cube.turn(5);

    ASSERT_EQ(04651230, cube.getEdges());
    ASSERT_EQ(0442320452241, cube.getCorners());
}

TEST(ruCubeTest, singleTurnInversionTest) {
    ruCube cube;

	for (int trn = 0; trn < 6; ++trn) {
        cube.turn(trn);
        ASSERT_FALSE(cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
        cube.inverseTurn(trn);
        ASSERT_TRUE(cube.isSolved(ruCube::allEdgesMask, ruCube::allCornersMask));
	}

    cube.inverseTurn(0);
	cube.inverseTurn(0);
	cube.inverseTurn(0);
	cube.inverseTurn(0);

	cube.inverseTurn(1);
	cube.inverseTurn(1);

	cube.inverseTurn(2);
	cube.inverseTurn(2);
	cube.inverseTurn(2);
	cube.inverseTurn(2);

	cube.inverseTurn(3);
	cube.inverseTurn(3);
	cube.inverseTurn(3);
	cube.inverseTurn(3);

	cube.inverseTurn(4);
	cube.inverseTurn(4);

	cube.inverseTurn(5);
	cube.inverseTurn(5);
	cube.inverseTurn(5);
	cube.inverseTurn(5);

	cube.inverseTurn(0);
	cube.inverseTurn(0);
	cube.turn(1);
	cube.turn(0);
	cube.turn(0);
	cube.inverseTurn(1);

    cube.inverseTurn(2);
	cube.inverseTurn(2);
	cube.turn(1);
	cube.turn(2);
	cube.turn(2);
	cube.inverseTurn(1);

    cube.inverseTurn(3);
	cube.inverseTurn(3);
	cube.turn(4);
	cube.turn(3);
	cube.turn(3);
	cube.inverseTurn(4);

    cube.inverseTurn(5);
	cube.inverseTurn(5);
	cube.turn(4);
	cube.turn(5);
	cube.turn(5);
	cube.inverseTurn(4);

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
    std::vector<uint8_t> moves{0, 3, 1, 4, 2, 5};
    cube.scramble(moves);
    ASSERT_EQ(04651230, cube.getEdges());
	ASSERT_EQ(0442320452241, cube.getCorners());

	cube.scramble({1, 4, 1, 4, 0, 3, 2, 5});
	ASSERT_EQ(04130265, cube.getEdges());
	ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, scrambleInversionTest) {
    ruCube cube;
    std::vector<uint8_t> moves{3, 0, 4, 1, 5, 2};
    cube.inverseScramble(moves);
    ASSERT_EQ(04651230, cube.getEdges());
	ASSERT_EQ(0442320452241, cube.getCorners());

	cube.inverseScramble({3, 0, 5, 2, 4, 1, 4, 1});
	ASSERT_EQ(04130265, cube.getEdges());
	ASSERT_EQ(0434541142042, cube.getCorners());
}

TEST(ruCubeTest, isInDominoTest) {
    ruCube cube;
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({1, 4, 1, 4, 1, 4});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({1, 3, 1, 5, 1, 3, 1, 3, 1, 5, 1, 5, 1, 3, 1, 4, 1, 5, 1, 4, 1, 4, 1, 5, 1, 5});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({0, 3, 2, 3, 0, 4, 2});
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({0, 3, 2, 3, 0, 4, 2});
    ASSERT_FALSE(cube.isInDomino());
    cube.scramble({3, 0, 3, 2, 3, 0, 5, 2, 3, 0, 4, 0});
    ASSERT_TRUE(cube.isInDomino());
    cube.scramble({0, 2, 3, 2, 5, 2, 5, 2, 3, 0, 3, 1, 0});
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
        { 0, 3, 1, 4, 2, 5, 10, 4, 1, 8, 10 },
        { 0, 3, 1, 2, 1, 2, 6 }
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
        { 0, 3, 1, 4, 2, 5, 10, 4, 1, 8, 10 },
        { 0, 3, 1, 2, 1, 2, 6 }
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

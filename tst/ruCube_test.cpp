#include "gtest/gtest.h"
#include "ruCube.h"



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
}


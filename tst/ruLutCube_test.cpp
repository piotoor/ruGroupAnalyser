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

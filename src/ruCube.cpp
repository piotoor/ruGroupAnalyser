#include "ruCube.h"
#include "ruException.h"
#include <iostream>

ruCube::ruCube() {
    initializeMovesVectors();
    reset();
}

ruCube::~ruCube() {

}

ruCube::ruCube(uint32_t edges, uint64_t corners): edges(edges), corners(corners) {
    initializeMovesVectors();
    reset();
}

ruCube::ruCube(const ruCube& other) {
    initializeMovesVectors();
    this->corners = other.getCorners();
    this->edges = other.getEdges();
}

uint32_t ruCube::getEdges() const{
    return this->edges;
}

uint64_t ruCube::getCorners() const{
    return this->corners;
}

void ruCube::setEdges(uint32_t edges){
    this->edges = edges;
}

void ruCube::setCorners(uint64_t corners) {
    this->corners = corners;
}

void ruCube::setCube(uint32_t edges, uint64_t corners) {
    setEdges(edges);
    setCorners(corners);
}

bool ruCube::isSolved(uint32_t edgesMask, uint64_t cornersMask) const {
    return isSolvedEdges(edgesMask) && isSolvedCorners(cornersMask);
}

bool ruCube::isSolvedEdges(uint32_t edgesMask) const {
    return (edges & edgesMask) == (solvedEdges & edgesMask);
}

bool ruCube::isSolvedCorners(uint64_t cornersMask) const {
    return (corners & cornersMask) == (solvedCorners & cornersMask);
}

bool ruCube::isSolvedCornersO() const {
    return (corners & 0707070707070) == (solvedCorners & 0707070707070);
}

bool ruCube::isSolvedEEinE() const {
	uint32_t mEdges = edges & 00000707;
	return ((00000406 == mEdges) || (00000604 == mEdges));
}

bool ruCube::isSolvedMEinM() const {
	uint32_t mEdges = edges & 07070000;
	return ((00020000 == mEdges) || (02000000 == mEdges));
}

bool ruCube::isSolvedSEinS() const {
	uint32_t mEdges = edges & 00707070;
	return ((00103050 == mEdges) || (00105030 == mEdges) || (00301050 == mEdges)
		 || (00305010 == mEdges) || (00503010 == mEdges) || (00501030 == mEdges));
}

bool ruCube::isInDomino() const {
    return isSolvedCornersO() && isSolvedEEinE();
}

void ruCube::reset() {
    edges = ruCube::solvedEdges;
    corners = ruCube::solvedCorners;
}

void ruCube::turn(uint8_t turnIndex) {
    if (turnIndex > 5) {
        throw ruCubeTurnException(turnIndex);
    } else {
        (this->*(movesVect[turnIndex]))();
    }
}

void ruCube::inverseTurn(uint8_t turnIndex) {
    if (turnIndex > 5) {
        throw ruCubeTurnException(turnIndex);
    } else {
        (this->*(movesInvertionsVect[turnIndex]))();
    }
}

void ruCube::scramble(std::vector<uint8_t> moves) {
    for (const auto &m: moves) {
        turn(m);
    }
}

void ruCube::inverseScramble(std::vector<uint8_t> moves) {
    for (int i = size(moves) - 1; i >= 0; --i) {
        inverseTurn(moves[i]);
    }
}

void ruCube::R() {
	// EP
	edges = (edges & 07770000) | ((edges & 00007770) >> 3) | ((edges & 00000007) << 9);

	// CO sum modulo 3
	corners = ((corners & 0600000006000) >> 1) | ((corners & 0100000001000) << 2) |
			  ((corners & 0000000300030) << 1) | ((corners & 0000000400040) >> 2) |
			   (corners & 0077777070707);

	// CP
	tmp = cornersPB.URF;
	cornersPB.URF = cornersPB.DFR;
	cornersPB.DFR = cornersPB.DRB;
	cornersPB.DRB = cornersPB.UBR;
	cornersPB.UBR = tmp;
}

void ruCube::R2() {
	// EP
	edges = (edges & 07770000) | ((edges & 00007700) >> 6) | ((edges & 00000077) << 6);

	// CP
	tmp = cornersPB.URF;
	cornersPB.URF = cornersPB.DRB;
	cornersPB.DRB = tmp;
	tmp = cornersPB.UBR;
	cornersPB.UBR = cornersPB.DFR;
	cornersPB.DFR = tmp;
}

void ruCube::Ri() {
	// EP
	edges = (edges & 07770000) | ((edges & 00000777) << 3) | ((edges & 00007000) >> 9);

	// CO
	corners = ((corners & 0600000006000) >> 1) | ((corners & 0100000001000) << 2) |
			  ((corners & 0000000300030) << 1) | ((corners & 0000000400040) >> 2) |
			   (corners & 0077777070707);

	// CP
	tmp = cornersPB.URF;
	cornersPB.URF = cornersPB.UBR;
	cornersPB.UBR = cornersPB.DRB;
	cornersPB.DRB = cornersPB.DFR;
	cornersPB.DFR = tmp;
}

void ruCube::U() {
	// EP
	edges = (edges & 00000777) | ((edges & 07770000) >> 3) | ((edges & 00007000) << 9);

	// CP
	corners = (corners & 07777) | ((corners & 0777777000000) >> 6) | ((corners & 0000000770000) << 18);
}

void ruCube::U2() {
	// EP
	edges = (edges & 0777) | ((edges & 07700000) >> 6) | ((edges & 00077000) << 6);
	// CP
	corners = (corners & 07777) | ((corners & 0777700000000) >> 12) | ((corners & 077770000) << 12);
}

void ruCube::Ui() {
	// EP
	edges = (edges & 0777) | ((edges & 00777000) << 3) | ((edges & 07000000) >> 9);

	// CP
	corners = (corners & 07777) | ((corners & 0007777770000) << 6) | ((corners & 0770000000000) >> 18);
}

void ruCube::initializeMovesVectors() {
    movesVect = {
        &ruCube::R,
        &ruCube::R2,
        &ruCube::Ri,
        &ruCube::U,
        &ruCube::U2,
        &ruCube::Ui,
    };

    movesInvertionsVect = {
        &ruCube::Ri,
        &ruCube::R2,
        &ruCube::R,
        &ruCube::Ui,
        &ruCube::U2,
        &ruCube::U,
    };
}



#include "ruCube.h"
#include "ruException.h"
#include <iostream>
#include <iomanip>

ruBaseCube:: ruBaseCube() {
    movesVect = {
        &ruBaseCube::R,
        &ruBaseCube::R2,
        &ruBaseCube::Ri,
        &ruBaseCube::U,
        &ruBaseCube::U2,
        &ruBaseCube::Ui,
    };

    movesInvertionsVect = {
        &ruBaseCube::Ri,
        &ruBaseCube::R2,
        &ruBaseCube::R,
        &ruBaseCube::Ui,
        &ruBaseCube::U2,
        &ruBaseCube::U,
    };
}

ruBaseCube::~ruBaseCube() {
}

void ruBaseCube::turn(uint8_t turnIndex) {
    if (turnIndex > 5) {
        throw ruCubeTurnException(turnIndex);
    } else {
        (this->*(movesVect[turnIndex]))();
    }
}

void ruBaseCube::inverseTurn(uint8_t turnIndex) {
    if (turnIndex > 5) {
        throw ruCubeTurnException(turnIndex);
    } else {
        (this->*(movesInvertionsVect[turnIndex]))();
    }
}

void ruBaseCube::scramble(std::vector<uint8_t> moves) {
    for (const auto &m: moves) {
        turn(m);
    }
}

void ruBaseCube::inverseScramble(std::vector<uint8_t> moves) {
    for (int i = size(moves) - 1; i >= 0; --i) {
        inverseTurn(moves[i]);
    }
}

ruCube::ruCube() {
    reset();
}

ruCube::~ruCube() {

}

ruCube::ruCube(uint32_t edges, uint64_t corners): edges(edges), corners(corners) {
    reset();
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

bool ruCube::isPruningPossible(uint8_t remainingMoves) const {
    return remainingMoves and 0;
}

std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfEdgesPermutations>    ruLutCube::edgesPermMoveMap     = lutGenerators::generateEdgesPermMoveMap();
std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfCornersPermutations>  ruLutCube::cornersPermMoveMap   = lutGenerators::generateCornersPermMoveMap();
std::array<std::array<uint16_t, lutGenerators::noOfTurns>, lutGenerators::noOfCornersOrientations>  ruLutCube::cornersOrientMoveMap = lutGenerators::generateCornersOrientMoveMap();

std::array<std::bitset<lutGenerators::noOfEdgesPermSolvedStates>, lutGenerators::noOfEdgesPermutations>          ruLutCube::edgesPermSolvedTable    = lutGenerators::generateEdgesPermSolvedTable();
std::array<std::bitset<lutGenerators::noOfCornersPermSolvedStates>, lutGenerators::noOfCornersPermutations>      ruLutCube::cornersPermSolvedTable  = lutGenerators::generateCornersPermSolvedTable();
std::array<std::bitset<lutGenerators::noOfCornersOrientSolvedStates>, lutGenerators::noOfCornersOrientations>    ruLutCube::cornersOrientSolvedTable = lutGenerators::generateCornersOrientSolvedTable();

std::array<int8_t, lutGenerators::noOfEdgesPermutations>                                                        ruLutCube::edgesPermPruningTable   = lutGenerators::generateEdgesPermPruningTable();
std::array<std::array<int8_t, lutGenerators::noOfCornersOrientations>, lutGenerators::noOfCornersPermutations>  ruLutCube::cornersPruningTable     = lutGenerators::generateCornersPruningTable();
std::vector<std::vector<std::vector<int8_t>>>  ruLutCube::fullCubePruningTable = lutGenerators::generateFullCubePruningTable();
std::array<std::bitset<lutGenerators::noOfEdgesPermutations>, lutGenerators::noOfCornersPermutations>    ruLutCube::permutationValidityTable = lutGenerators::generatePermutationValidityTable();

ruLutCube::ruLutCube() {
    reset();
}

ruLutCube::ruLutCube(uint16_t edgesPerm, uint16_t cornersPerm, uint16_t cornersOrient) {
    setEdges(edgesPerm);
    this->cornersPerm = cornersPerm;
    this->cornersOrient = cornersOrient;
}

ruLutCube::~ruLutCube() {

}

ruLutCube& ruLutCube::operator=(const ruLutCube& other) {
    edgesPerm = other.edgesPerm;
    cornersPerm = other.cornersPerm;
    cornersOrient = other.cornersOrient;
    return *this;
}

bool ruLutCube::operator==(const ruLutCube &other) const {
    return  edgesPerm == other.edgesPerm and
            cornersPerm == other.cornersPerm and
            cornersOrient == other.cornersOrient;
}

uint32_t ruLutCube::getEdges() const {
    return this->edgesPerm;
}

uint64_t ruLutCube::getCorners() const {
    return static_cast<uint64_t>((cornersOrient << sizeof(uint16_t) * 8) | cornersPerm);
}

void ruLutCube::setEdges(uint32_t edges) {
    this->edgesPerm = edges;
}

void ruLutCube::setCorners(uint64_t corners) {
    this->cornersPerm = corners & setCornersPermMask;
    this->cornersOrient = (corners & setCornersOrientMask) >> (sizeof(uint16_t) * 8);
}

void ruLutCube::setCube(uint32_t edges, uint64_t corners) {
    setEdges(edges);
    setCorners(corners);
}

bool ruLutCube::isSolved(uint32_t edgesMask, uint64_t cornersMask) const {
    return isSolvedEdges(edgesMask) and isSolvedCorners(cornersMask);
}

bool ruLutCube::isSolvedEdges(uint32_t edgesMask) const {
    return (edgesPermSolvedTable[edgesPerm].to_ulong() & edgesMask) == (lutGenerators::edgesSolvedBitmask & edgesMask);
}

bool ruLutCube::isSolvedCorners(uint64_t cornersMask) const {
    uint32_t cornersPermMask    = cornersMask & 0xFFFFFFFF;
    uint32_t cornersOrientMask  = (cornersMask >> (sizeof(uint32_t) * 8)) & 0xFFFFFFFF;
    return ((cornersPermSolvedTable[cornersPerm].to_ullong() & cornersPermMask) == (lutGenerators::cornersPermSolvedBitMask & cornersPermMask)) and ((cornersOrientSolvedTable[cornersOrient].to_ulong() & cornersOrientMask) == (lutGenerators::cornersOrientSolvedBitMask & cornersOrientMask));
}

bool ruLutCube::isInDomino() const {
    return isSolvedCornersO() and isSolvedEEinE();
}

bool ruLutCube::isSolvedCornersO() const {
    return cornersPermSolvedTable[cornersOrient][static_cast<uint8_t>(lutGenerators::cornersOrientSolvedState::allCorners)];
}

bool ruLutCube::isSolvedEEinE() const {
    return edgesPermSolvedTable[edgesPerm][static_cast<uint8_t>(lutGenerators::edgesPermSolvedState::eEdgesInE)];
}

bool ruLutCube::isSolvedMEinM() const {
    return edgesPermSolvedTable[edgesPerm][static_cast<uint8_t>(lutGenerators::edgesPermSolvedState::mEdgesInM)];
}

bool ruLutCube::isSolvedSEinS() const {
    return edgesPermSolvedTable[edgesPerm][static_cast<uint8_t>(lutGenerators::edgesPermSolvedState::sEdgesInS)];
}

void ruLutCube::reset() {
    this->edgesPerm = solvedLexIndexEdgesPerm;
    this->cornersPerm = solvedLexIndexCornersPerm;
    this->cornersOrient = solvedLexIndexCornersOrient;
}

bool ruLutCube::isPruningPossible(uint8_t remainingMoves) const {
    return  this->edgesPermPruningTable[this->edgesPerm] > remainingMoves or
            this->cornersPruningTable[this->cornersPerm][this->cornersOrient] > remainingMoves or
            this->fullCubePruningTable[this->cornersPerm][this->cornersOrient][this->edgesPerm] > remainingMoves;
}

void ruLutCube::R() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::R];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::R];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::R];
}

void ruLutCube::R2() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::R2];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::R2];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::R2];
}

void ruLutCube::Ri() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::Ri];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::Ri];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::Ri];
}

void ruLutCube::U() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::U];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::U];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::U];
}

void ruLutCube::U2() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::U2];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::U2];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::U2];
}

void ruLutCube::Ui() {
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::Ui];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::Ui];
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::Ui];
}

uint16_t ruLutCube::getCornersOrient() const {
    return this->cornersOrient;
}

uint16_t ruLutCube::getCornersPerm() const {
    return this->cornersPerm;
}

void ruLutCube::setCornersPerm(uint16_t cornersPerm) {
    this->cornersPerm = cornersPerm;
}

void ruLutCube::setCornersOrient(uint16_t cornersOrient) {
    this->cornersOrient = cornersOrient;
}

bool ruLutCube::isPermutationSolveable(uint16_t cornersPerm, uint16_t edgesPerm) {
    return  cornersPerm < lutGenerators::noOfCornersPermutations and
            edgesPerm < lutGenerators::noOfEdgesPermutations and
            permutationValidityTable[cornersPerm][edgesPerm];
}

bool ruLutCube::isCornersOrientationSolveable(uint16_t cornersOrient) {
    return  cornersOrient < lutGenerators::noOfCornersOrientations and
            cornersPruningTable[0][cornersOrient] != -1;
}

bool ruLutCube::isCubeSolveable(uint16_t edgesPerm, uint16_t cornersPerm, uint16_t cornersOrient) {
    return isPermutationSolveable(cornersPerm, edgesPerm) and isCornersOrientationSolveable(cornersOrient);
}

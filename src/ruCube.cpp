#include "ruCube.h"
#include "lutGenerators.h"
#include "ruException.h"
#include <iostream>
#include <iomanip>
#include <sstream>

std::array<std::array<uint16_t, ruBaseCube::noOfTurns>, ruBaseCube::noOfCornersOrientations>  ruLutCube::cornersOrientMoveMap = lutGenerators::generateCornersOrientMoveMap();
std::array<std::array<uint16_t, ruBaseCube::noOfTurns>, ruBaseCube::noOfCornersPermutations>  ruLutCube::cornersPermMoveMap   = lutGenerators::generateCornersPermMoveMap();
std::array<std::array<uint16_t, ruBaseCube::noOfTurns>, ruBaseCube::noOfEdgesPermutations>    ruLutCube::edgesPermMoveMap     = lutGenerators::generateEdgesPermMoveMap();

std::array<std::bitset<ruBaseCube::noOfCornersOrientSolvedStates>, ruBaseCube::noOfCornersOrientations>    ruLutCube::cornersOrientSolvedTable = lutGenerators::generateCornersOrientSolvedTable();
std::array<std::bitset<ruBaseCube::noOfCornersPermSolvedStates>, ruBaseCube::noOfCornersPermutations>      ruLutCube::cornersPermSolvedTable  = lutGenerators::generateCornersPermSolvedTable();
std::array<std::bitset<ruBaseCube::noOfEdgesPermSolvedStates>, ruBaseCube::noOfEdgesPermutations>          ruLutCube::edgesPermSolvedTable    = lutGenerators::generateEdgesPermSolvedTable();

std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersOrientCases>, ruBaseCube::noOfCornersOrientations>    ruLutCube::cornersOrientPruningTable = lutGenerators::generateCornersOrientPruningTable();
std::array<std::array<int8_t, ruBaseCube::noOfPartialCornersPermCases>, ruBaseCube::noOfCornersPermutations>      ruLutCube::cornersPermPruningTable = lutGenerators::generateCornersPermPruningTable();
std::array<std::array<int8_t, ruBaseCube::noOfPartialEdgesPermCases>, ruBaseCube::noOfEdgesPermutations>          ruLutCube::edgesPermPruningTable   = lutGenerators::generateEdgesPermPruningTable();
std::array<std::array<int8_t, ruBaseCube::noOfCornersOrientations>, ruBaseCube::noOfCornersPermutations>          ruLutCube::cornersPruningTable     = lutGenerators::generateCornersPruningTable();
std::vector<std::vector<std::vector<int8_t>>>                                                                     ruLutCube::fullCubePruningTable = lutGenerators::generateFullCubePruningTable();

std::array<std::bitset<ruBaseCube::noOfEdgesPermutations>, ruBaseCube::noOfCornersPermutations>    ruLutCube::permutationValidityTable = lutGenerators::generatePermutationValidityTable();

ruBaseCube:: ruBaseCube() {
    movesVect = {
        &ruBaseCube::moveR,
        &ruBaseCube::moveR2,
        &ruBaseCube::moveRi,
        &ruBaseCube::moveU,
        &ruBaseCube::moveU2,
        &ruBaseCube::moveUi,
    };

    movesInvertionsVect = {
        &ruBaseCube::moveRi,
        &ruBaseCube::moveR2,
        &ruBaseCube::moveR,
        &ruBaseCube::moveUi,
        &ruBaseCube::moveU2,
        &ruBaseCube::moveU,
    };
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
    for (int i = static_cast<int>(size(moves)) - 1; i >= 0; --i) {
        inverseTurn(moves[i]);
    }
}

ruCube::ruCube() {
    reset();
}

ruCube::ruCube(uint64_t corners, uint32_t edges): corners(corners), edges(edges) {
    reset();
}

uint64_t ruCube::getCorners() const{
    return this->corners;
}

uint32_t ruCube::getEdges() const{
    return this->edges;
}

void ruCube::setCorners(uint64_t corners) {
    this->corners = corners;
}

void ruCube::setEdges(uint32_t edges){
    this->edges = edges;
}

void ruCube::setCube(uint64_t corners, uint32_t edges) {
    setEdges(edges);
    setCorners(corners);
}

uint32_t ruCube::getPartialCornersOrient(uint8_t mask) const {
    uint32_t partialCornersOrient = 0;

    for (uint8_t i = 0; i < ruCube::noOfCorners; ++i) {
        uint64_t curr = getPermPartOfCorner(getCorners(), i);
        uint64_t currOrient = getOrientPartOfCorner(getCorners(), i);

        if (isPartOfCornerIgnored(curr, mask)) {
            setCorner(partialCornersOrient, i, 07);
        } else {
            setCorner(partialCornersOrient, i, currOrient);
        }
    }
    return partialCornersOrient;
}

uint32_t ruCube::getOrientPartOfCorner(uint64_t corners, uint8_t i) const {
    return ((UINT64_C(07) << (i * cornerBitLength + cornerPermBitLength)) & corners) >> (i * cornerBitLength + cornerPermBitLength);
}

bool ruCube::isPartOfCornerIgnored(uint8_t currCorner, uint8_t mask) const {
    return (mask & (1 << (ruCube::noOfCorners - currCorner - 1))) == 0;
}

uint32_t ruCube::getPermPartOfCorner(uint64_t corners, uint8_t i) const {
    return ((UINT64_C(07) << (i * cornerBitLength)) & corners) >> (i * cornerBitLength);
}

void ruCube::setCorner(uint32_t &corners, uint8_t i, uint32_t val) const {
    corners |= (val << (i * outputCornerBitLength));
}

uint32_t ruCube::getPartialCornersPerm(uint8_t mask) const {
    uint32_t partialCornersPerm = 0;

    for (uint8_t i = 0; i < ruCube::noOfCorners; ++i) {
        uint64_t curr = getPermPartOfCorner(getCorners(), i);

        if (isPartOfCornerIgnored(curr, mask)) {
            setCorner(partialCornersPerm, i, 07);
        } else {
            setCorner(partialCornersPerm, i, curr);
        }
    }
    return partialCornersPerm;
}

uint32_t ruCube::getEdge(uint32_t edges, uint8_t i) const {
    return ((UINT32_C(07) << (i * edgeBitLength)) & edges) >> (i * edgeBitLength);
}

bool ruCube::isEdgeIgnored(uint8_t currEdge, uint8_t mask) const {
    return (mask & (1 << (ruCube::noOfEdges - currEdge - 1))) == 0;
}

void ruCube::setEdge(uint32_t &edges, uint8_t i, uint32_t val) const {
    edges |= (val << (i * edgeBitLength));
}

uint32_t ruCube::getPartialEdges(uint8_t mask) const {
    uint32_t partialEdges = getEdges();

    for (uint8_t i = 0; i < ruCube::noOfEdges; ++i) {
        uint32_t currEdge = getEdge(partialEdges, i);

        if (isEdgeIgnored(currEdge, mask)) {
            setEdge(partialEdges, i, 07);
        }
    }

    return partialEdges;
}

bool ruCube::isSolved() const {
    return isSolved(ruCube::allCornersMask, ruCube::allEdgesMask);
}

bool ruCube::isSolved(uint64_t cornersMask, uint32_t edgesMask) const {
    return isSolvedEdges(edgesMask) && isSolvedCorners(cornersMask);
}

bool ruCube::isSolvedCornersOrient() const {
    return (corners & 0707070707070) == (solvedCorners & 0707070707070);
}

bool ruCube::isSolvedCorners(uint64_t cornersMask) const {
    return (corners & cornersMask) == (solvedCorners & cornersMask);
}

bool ruCube::isSolvedEdges(uint32_t edgesMask) const {
    return (edges & edgesMask) == (solvedEdges & edgesMask);
}

bool ruCube::isSolvedEEinE() const {
    uint32_t eEdges = edges & 00000707;

    return (00000406 == eEdges) || (00000604 == eEdges);
}

bool ruCube::isSolvedMEinM() const {
    uint32_t mEdges = edges & 07070000;

    return (00020000 == mEdges) || (02000000 == mEdges);
}

bool ruCube::isSolvedSEinS() const {
    uint32_t sEdges = edges & 00707070;

    return (00103050 == sEdges) || (00105030 == sEdges) || (00301050 == sEdges)
        || (00305010 == sEdges) || (00503010 == sEdges) || (00501030 == sEdges);
}

bool ruCube::isInDomino() const {
    return isSolvedCornersOrient() && isSolvedEEinE();
}

void ruCube::reset() {
    corners = ruCube::solvedCorners;
    edges = ruCube::solvedEdges;
}

void ruCube::moveR() {
    edges = (edges & 07770000) | ((edges & 00007770) >> 3) | ((edges & 00000007) << 9);
    corners = ((corners & 0600000006000) >> 1) | ((corners & 0100000001000) << 2) |
              ((corners & 0000000300030) << 1) | ((corners & 0000000400040) >> 2) |
              (corners & 0077777070707);

    tmp = cornersPB.URF;
    cornersPB.URF = cornersPB.DFR;
    cornersPB.DFR = cornersPB.DRB;
    cornersPB.DRB = cornersPB.UBR;
    cornersPB.UBR = tmp;
}

void ruCube::moveR2() {
    edges = (edges & 07770000) | ((edges & 00007700) >> 6) | ((edges & 00000077) << 6);

    tmp = cornersPB.URF;
    cornersPB.URF = cornersPB.DRB;
    cornersPB.DRB = tmp;
    tmp = cornersPB.UBR;
    cornersPB.UBR = cornersPB.DFR;
    cornersPB.DFR = tmp;
}

void ruCube::moveRi() {
    edges = (edges & 07770000) | ((edges & 00000777) << 3) | ((edges & 00007000) >> 9);
    corners = ((corners & 0600000006000) >> 1) | ((corners & 0100000001000) << 2) |
                ((corners & 0000000300030) << 1) | ((corners & 0000000400040) >> 2) |
                 (corners & 0077777070707);

    tmp = cornersPB.URF;
    cornersPB.URF = cornersPB.UBR;
    cornersPB.UBR = cornersPB.DRB;
    cornersPB.DRB = cornersPB.DFR;
    cornersPB.DFR = tmp;
}

void ruCube::moveU() {
    edges = (edges & 00000777) | ((edges & 07770000) >> 3) | ((edges & 00007000) << 9);
    corners = (corners & 07777) | ((corners & 0777777000000) >> 6) | ((corners & 0000000770000) << 18);
}

void ruCube::moveU2() {
    edges = (edges & 0777) | ((edges & 07700000) >> 6) | ((edges & 00077000) << 6);
    corners = (corners & 07777) | ((corners & 0777700000000) >> 12) | ((corners & 077770000) << 12);
}

void ruCube::moveUi() {
    edges = (edges & 0777) | ((edges & 00777000) << 3) | ((edges & 07000000) >> 9);
    corners = (corners & 07777) | ((corners & 0007777770000) << 6) | ((corners & 0770000000000) >> 18);
}

bool ruCube::isPruningPossible(uint8_t remainingMoves, uint64_t cornersMask, uint32_t edgesPermMask) const {
    return remainingMoves and cornersMask and edgesPermMask and 0;
}

ruLutCube::ruLutCube() {
    reset();
}

ruLutCube::ruLutCube(uint16_t cornersOrient, uint16_t cornersPerm, uint16_t edgesPerm, const ruLutCubeIgnoredPieces &ignored): ignoredPieces(ignored) {
    this->cornersOrient = cornersOrient;
    this->cornersPerm = cornersPerm;
    setEdges(edgesPerm);
}

ruLutCube& ruLutCube::operator=(const ruLutCube& other) {
    cornersOrient = other.cornersOrient;
    cornersPerm = other.cornersPerm;
    edgesPerm = other.edgesPerm;
    ignoredPieces = other.ignoredPieces;
    return *this;
}

bool ruLutCube::operator==(const ruLutCube &other) const {
    return  cornersOrient == other.cornersOrient and
            cornersPerm == other.cornersPerm and
            edgesPerm == other.edgesPerm;
}

uint64_t ruLutCube::getCorners() const {
    return static_cast<uint64_t>((cornersOrient << sizeof(uint16_t) * 8) | cornersPerm);
}

uint32_t ruLutCube::getEdges() const {
    return this->edgesPerm;
}

void ruLutCube::setCorners(uint64_t corners) {
    this->cornersPerm = corners & setCornersPermMask;
    this->cornersOrient = (corners & setCornersOrientMask) >> (sizeof(uint16_t) * 8);
}

void ruLutCube::setEdges(uint32_t edges) {
    this->edgesPerm = edges;
}

void ruLutCube::setCube(uint64_t corners, uint32_t edges) {
    setEdges(edges);
    setCorners(corners);
}

bool ruLutCube::isSolved() const {
    return isSolved(ruLutCube::allCornersMask, ruLutCube::allEdgesMask);
}

bool ruLutCube::isSolved(uint64_t cornersMask, uint32_t edgesMask) const {
    return isSolvedCorners(cornersMask) and isSolvedEdges(edgesMask);
}

bool ruLutCube::isSolvedCornersOrient() const {
    return cornersPermSolvedTable[cornersOrient][static_cast<uint8_t>(lutGenerators::cornersOrientSolvedState::allCorners)];
}

bool ruLutCube::isSolvedCorners(uint64_t cornersMask) const {
    uint32_t cornersPermMask    = cornersMask & 0xFFFFFFFF;
    uint32_t cornersOrientMask  = (cornersMask >> (sizeof(uint32_t) * 8)) & 0xFFFFFFFF;

    return ((cornersPermSolvedTable[cornersPerm].to_ullong() & cornersPermMask) == (lutGenerators::cornersPermSolvedBitMask & cornersPermMask)) and ((cornersOrientSolvedTable[cornersOrient].to_ulong() & cornersOrientMask) == (lutGenerators::cornersOrientSolvedBitMask & cornersOrientMask));
}

bool ruLutCube::isSolvedEdges(uint32_t edgesMask) const {
    return (edgesPermSolvedTable[edgesPerm].to_ulong() & edgesMask) == (lutGenerators::edgesSolvedBitmask & edgesMask);
}

bool ruLutCube::isInDomino() const {
    return isSolvedCornersOrient() and isSolvedEEinE();
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
    this->cornersOrient = solvedLexIndexCornersOrient;
    this->cornersPerm = solvedLexIndexCornersPerm;
    this->edgesPerm = solvedLexIndexEdgesPerm;
    this->ignoredPieces = ruLutCubeIgnoredPieces();
}

bool ruLutCube::isPruningPossible(uint8_t remainingMoves, uint64_t cornersMask, uint32_t edgesPermMask) const {
    if (edgesPermMask != ruLutCube::allEdgesMask or cornersMask != ruLutCube::allCornersMask) {
        uint32_t cornersPermMask = cornersMask & 0x3F;
        uint32_t cornersOrientMask = (cornersMask >> UINT64_C(32)) & 0x3F;

        return  this->edgesPermPruningTable[this->edgesPerm][static_cast<uint8_t>(edgesPermMask & 0x7F)] > (int8_t)remainingMoves or
                this->cornersPermPruningTable[this->cornersPerm][static_cast<uint8_t>(cornersPermMask)] > (int8_t)remainingMoves or
                this->cornersOrientPruningTable[this->cornersOrient][static_cast<uint8_t>(cornersOrientMask)] > (int8_t)remainingMoves;
    } else {
        return this->fullCubePruningTable[this->cornersPerm][this->cornersOrient][this->edgesPerm] > (int8_t)remainingMoves;
    }
}

void ruLutCube::moveR() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::R];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::R];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::R];
}

void ruLutCube::moveR2() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::R2];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::R2];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::R2];
}

void ruLutCube::moveRi() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::Ri];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::Ri];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::Ri];
}

void ruLutCube::moveU() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::U];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::U];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::U];
}

void ruLutCube::moveU2() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::U2];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::U2];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::U2];
}

void ruLutCube::moveUi() {
    cornersOrient = cornersOrientMoveMap[cornersOrient][ruCubeMove::Ui];
    cornersPerm = cornersPermMoveMap[cornersPerm][ruCubeMove::Ui];
    edgesPerm = edgesPermMoveMap[edgesPerm][ruCubeMove::Ui];
}

uint16_t ruLutCube::getCornersOrient() const {
    return this->cornersOrient;
}

uint16_t ruLutCube::getCornersPerm() const {
    return this->cornersPerm;
}

void ruLutCube::setCornersOrient(uint16_t cornersOrient) {
    this->cornersOrient = cornersOrient;
}

void ruLutCube::setCornersPerm(uint16_t cornersPerm) {
    this->cornersPerm = cornersPerm;
}

bool ruLutCube::isCornersOrientationSolveable(uint16_t cornersOrient) {
    return  cornersOrient < ruBaseCube::noOfCornersOrientations and
            cornersPruningTable[0][cornersOrient] != -1;
}

bool ruLutCube::isPermutationSolveable(uint16_t cornersPerm, uint16_t edgesPerm) {
    return  cornersPerm < ruBaseCube::noOfCornersPermutations and
            edgesPerm < ruBaseCube::noOfEdgesPermutations and
            permutationValidityTable[cornersPerm][edgesPerm];
}

bool ruLutCube::isCubeSolveable(uint16_t cornersOrient, uint16_t cornersPerm, uint16_t edgesPerm) {
    return isPermutationSolveable(cornersPerm, edgesPerm) and isCornersOrientationSolveable(cornersOrient);
}

std::string ruLutCube::toString() {
    ruCubeStateConverter conv;
    const auto &[co, cp, ep] = ignoredPieces;

    return  conv.lexIndexCornersToIntCornersAsStrWithIgnored(cornersPerm, cornersOrient, cp, co) + ";" +
            conv.lexIndexEdgesToIntEdgesAsStrWithIgnored(edgesPerm, ep);
}

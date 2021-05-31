#ifndef LUTGENERATORS_H
#define LUTGENERATORS_H

namespace lutGenerators {
    inline static const uint8_t noOfTurns = 6;
    inline static const uint16_t noOfEdgesPermutations = 5040;

    std::array<std::array<uint16_t, noOfTurns>, noOfEdgesPermutations> generateEdgesPermMoveMap ();
}


#endif // LUTGENERATORS_H

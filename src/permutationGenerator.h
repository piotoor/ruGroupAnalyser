#ifndef PERMUTATIONGENERATOR_H
#define PERMUTATIONGENERATOR_H

#include <vector>
#include <cstdint>

class permutationGenerator
{
    public:
        permutationGenerator();
        virtual ~permutationGenerator();

        std::vector<std::vector<int8_t>> generatePermutations(int8_t n);
        std::vector<std::vector<int8_t>> generatePermutationsWithLockedPieces(int8_t n, const std::vector<int8_t> &locked);
        std::vector<std::vector<int8_t>> generatePermutationsWithIgnoredPieces(int8_t n, const std::vector<int8_t> &ignored);

    private:
        void initializePermutation(int8_t n);
        std::vector<int8_t> pieces;

};

#endif // PERMUTATIONGENERATOR_H

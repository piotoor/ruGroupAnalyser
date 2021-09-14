#ifndef PERMUTATIONGENERATOR_H
#define PERMUTATIONGENERATOR_H

#include <vector>
#include <set>
#include <cstdint>

class permutationGenerator
{
    public:
        permutationGenerator();
        explicit permutationGenerator(const permutationGenerator &other) = delete;
        permutationGenerator& operator=(const permutationGenerator &other) = delete;
        virtual ~permutationGenerator();

        std::vector<std::vector<int8_t>> generatePermutations(int8_t n, const std::vector<int8_t> &locked = {}, const std::vector<int8_t> &ignored = {});

    private:
        void cleanup(int8_t n);
        void generateAns(const std::vector<int8_t> &locked);
        std::multiset<int8_t> pieces;
        std::multiset<int8_t> permuteablePieces;
        std::vector<std::vector<int8_t>> ans;

};

#endif // PERMUTATIONGENERATOR_H

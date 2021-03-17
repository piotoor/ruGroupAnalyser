#ifndef ORIENTATIONGENERATOR_H
#define ORIENTATIONGENERATOR_H

#include <vector>
#include <cstdint>

class orientationGenerator
{
    public:
        orientationGenerator();
        virtual ~orientationGenerator();
        std::vector<std::vector<int8_t>> generateOrientations(int8_t n);
        std::vector<std::vector<int8_t>> generateOrientationsWithLockedPieces(int8_t n, const std::vector<int8_t> &locked);
        std::vector<std::vector<int8_t>> generateOrientationsWithIgnoredPieces(int8_t n, const std::vector<int8_t> &ignored);

    protected:

    private:
        void dfs(uint8_t depth, uint8_t maxDepth);
        void cleanup();

        std::vector<std::vector<int8_t>> ans;
        std::vector<int8_t> curr;
        int8_t currSum;
};

#endif // ORIENTATIONGENERATOR_H

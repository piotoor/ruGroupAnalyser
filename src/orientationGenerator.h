#ifndef ORIENTATIONGENERATOR_H
#define ORIENTATIONGENERATOR_H

#include <vector>
#include <cstdint>

class orientationGenerator
{
    public:
        orientationGenerator();
        virtual ~orientationGenerator();
        std::vector<std::vector<int8_t>> generateOrientations(int8_t n, const std::vector<int8_t> &locked = {}, const std::vector<int8_t> &ignored = {});

    protected:

    private:
        void dfs(uint8_t depth, uint8_t maxDepth, const std::vector<int8_t> &locked = {}, const std::vector<int8_t> &ignored = {});
        void cleanup();

        std::vector<std::vector<int8_t>> ans;
        std::vector<int8_t> curr;
        int8_t currSum = 0;
        bool hasIgnoredPiece = false;
};

#endif // ORIENTATIONGENERATOR_H

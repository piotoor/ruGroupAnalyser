#ifndef ORIENTATIONGENERATOR_H
#define ORIENTATIONGENERATOR_H

#include "ruCube.h"
#include <vector>
#include <array>
#include <cstdint>

using cornersArray = std::array<int8_t, 6>;

class orientationGenerator
{
    public:
        orientationGenerator();
        explicit orientationGenerator(const orientationGenerator &other) = delete;
        orientationGenerator& operator=(const orientationGenerator &other) = delete;
        virtual ~orientationGenerator();
        std::vector<cornersArray> generateOrientations(const cornersArray &locked = { -1, -1, -1, -1, -1, -1 }, const cornersArray &ignored = { 0, 0, 0, 0, 0, 0 });

    protected:

    private:
        void dfs(uint8_t depth, uint8_t maxDepth, const cornersArray &locked = { -1, -1, -1, -1, -1, -1 }, const cornersArray &ignored = { 0, 0, 0, 0, 0, 0 });
        void cleanup();

        std::vector<cornersArray> ans;
        cornersArray curr;
        int8_t currSum = 0;
        bool hasIgnoredPiece = false;
};

#endif // ORIENTATIONGENERATOR_H

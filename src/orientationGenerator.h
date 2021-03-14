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
};

#endif // ORIENTATIONGENERATOR_H

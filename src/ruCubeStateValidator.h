#ifndef RUCUBESTATEVALIDATOR_H
#define RUCUBESTATEVALIDATOR_H

#include "ruCubeStateConverter.h"
#include "ruCube.h"
#include <vector>
#include <cstdint>

using cornersArray = std::array<int8_t, 6>;

class ruCubeStateValidator
{
    public:
        ruCubeStateValidator();
        explicit ruCubeStateValidator(const ruCubeStateValidator &other) = delete;
        ruCubeStateValidator& operator=(const ruCubeStateValidator &other) = delete;
        virtual ~ruCubeStateValidator();
        bool isVectCornersValid(const cornersArray &orient, const std::vector<int8_t> &perm);
        bool isVectCornersOrientValid(const cornersArray &orient);
        bool isVectCornersPermValid(const std::vector<int8_t> &perm);
        bool isVectEdgesValid(const std::vector<int8_t> &perm);

        bool isVectCubeStateSolveableQuick( const cornersArray &cornersOrient,
                                            const std::vector<int8_t> &cornersPerm,
                                            const std::vector<int8_t> &edgesPerm);

        bool isVectCubeStateSolveableFull(  const cornersArray &cornersOrient,
                                            const std::vector<int8_t> &cornersPerm,
                                            const std::vector<int8_t> &edgesPerm);
        bool isVectCubePermSolveableQuick(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm);
        bool isVectCubePermSolveableFull(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm);
        bool isVectCornersOrientSolveableQuick(const cornersArray &cornersOrient);
        bool isVectCornersOrientSolveableFull(const cornersArray &cornersOrient);

    private:
        bool isPermutationValid(const std::vector<int8_t> &perm);

        ruLutCube cube;
        ruCubeStateConverter converter;
};

#endif // RUCUBESTATEVALIDATOR_H

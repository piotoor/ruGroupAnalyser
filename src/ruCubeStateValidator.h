#ifndef RUCUBESTATEVALIDATOR_H
#define RUCUBESTATEVALIDATOR_H

#include "ruCubeStateConverter.h"
#include "ruCube.h"
#include <vector>
#include <cstdint>

class ruCubeStateValidator
{
    public:
        ruCubeStateValidator();
        explicit ruCubeStateValidator(const ruCubeStateValidator &other) = delete;
        ruCubeStateValidator& operator=(const ruCubeStateValidator &other) = delete;
        virtual ~ruCubeStateValidator();
        bool isVectCornersValid(const std::vector<int8_t> &orient, const std::vector<int8_t> &perm);
        bool isVectCornersOrientValid(const std::vector<int8_t> &orient);
        bool isVectCornersPermValid(const std::vector<int8_t> &perm);
        bool isVectEdgesValid(const std::vector<int8_t> &perm);

        bool isVectCubeStateSolveableQuick( const std::vector<int8_t> &cornersOrient,
                                            const std::vector<int8_t> &cornersPerm,
                                            const std::vector<int8_t> &edgesPerm);

        bool isVectCubeStateSolveableFull(  const std::vector<int8_t> &cornersOrient,
                                            const std::vector<int8_t> &cornersPerm,
                                            const std::vector<int8_t> &edgesPerm);
        bool isVectCubePermSolveableQuick(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm);
        bool isVectCubePermSolveableFull(const std::vector<int8_t>& cornersPerm, const std::vector<int8_t>& edgesPerm);
        bool isVectCornersOrientSolveableQuick(const std::vector<int8_t>& cornersOrient);
        bool isVectCornersOrientSolveableFull(const std::vector<int8_t>& cornersOrient);

    private:
        bool isPermutationValid(const std::vector<int8_t> &perm);
        bool isOrientationValid(const std::vector<int8_t> &orient);

        ruLutCube cube;
        ruCubeStateConverter converter;
};

#endif // RUCUBESTATEVALIDATOR_H

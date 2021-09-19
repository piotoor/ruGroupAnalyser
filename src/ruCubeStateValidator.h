#ifndef RUCUBESTATEVALIDATOR_H
#define RUCUBESTATEVALIDATOR_H

#include "ruCubeStateConverter.h"
#include "ruCube.h"
#include <vector>
#include <cstdint>

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

class ruCubeStateValidator
{
    public:
        ruCubeStateValidator();
        explicit ruCubeStateValidator(const ruCubeStateValidator &other) = delete;
        ruCubeStateValidator& operator=(const ruCubeStateValidator &other) = delete;
        virtual ~ruCubeStateValidator();
        bool isVectCornersValid(const cornersArray &orient, const cornersArray &perm);
        bool isVectCornersOrientValid(const cornersArray &orient);
        bool isVectCornersPermValid(const cornersArray &perm);
        bool isVectEdgesValid(const edgesArray &perm);

        bool isVectCubeStateSolveableQuick( const cornersArray &cornersOrient,
                                            const cornersArray &cornersPerm,
                                            const edgesArray &edgesPerm);

        bool isVectCubeStateSolveableFull(  const cornersArray &cornersOrient,
                                            const cornersArray &cornersPerm,
                                            const edgesArray &edgesPerm);
        bool isVectCubePermSolveableQuick(const cornersArray& cornersPerm, const edgesArray& edgesPerm);
        bool isVectCubePermSolveableFull(const cornersArray& cornersPerm, const edgesArray& edgesPerm);
        bool isVectCornersOrientSolveableQuick(const cornersArray &cornersOrient);
        bool isVectCornersOrientSolveableFull(const cornersArray &cornersOrient);

    private:
        template <typename T>
        bool isPermutationValid(const T &perm);

        ruLutCube cube;
        ruCubeStateConverter converter;
};

#endif // RUCUBESTATEVALIDATOR_H

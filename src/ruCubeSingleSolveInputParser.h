#ifndef RUCUBESINGLESOLVEINPUTPARSER_H
#define RUCUBESINGLESOLVEINPUTPARSER_H
#include "ruCubeStateParser.h"
#include "ruCubeStateValidator.h"
#include "ruCubeStateConverter.h"
#include "ruCubeScrambleParser.h"
#include "ruCube.h"

class ruCubeSingleSolveInputParser {
    public:
        ruCubeSingleSolveInputParser();
        virtual ~ruCubeSingleSolveInputParser();

        ruLutCube getCubeFromScramble(std::string scramble);
        ruLutCube getCubeFromState(std::string state);

    private:
        ruCubeStateConverter converter;
        ruCubeStateValidator validator;
};

#endif // RUCUBESINGLESOLVEINPUTPARSER_H

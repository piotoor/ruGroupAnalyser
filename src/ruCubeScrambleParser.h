#ifndef RUCUBESCRAMBLEPARSER_H
#define RUCUBESCRAMBLEPARSER_H
#include "ruCube.h"
#include <unordered_map>

namespace ruCubeScrambleParser
{
    inline static const std::vector<std::string> ruCubeMovesStrings {
        "R", "R2", "R'", "U", "U2", "U'"
    };

    inline static const std::vector<std::string> ruCubeMovesStringsAlnum {
        "R", "R2", "Ri", "U", "U2", "Ui"
    };

    inline static const std::unordered_map<std::string, ruCubeMove> ruCubeMovesInts {
        { "R",  ruCubeMove::R   },
        { "R2", ruCubeMove::R2  },
        { "R'", ruCubeMove::Ri  },
        { "U",  ruCubeMove::U   },
        { "U2", ruCubeMove::U2  },
        { "U'", ruCubeMove::Ui  }
    };

    std::string vectorScrambleToStringScramble(const std::vector<uint8_t> &moves, bool compressSolution = false, bool alnumMoves = false);
    std::vector<uint8_t> stringScrambleToVectorScramble(const std::string &moves);
}

#endif // RUCUBESCRAMBLEPARSER_H

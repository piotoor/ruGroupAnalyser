#include "ruCubeScrambleParser.h"
#include <numeric>
#include <regex>
#include <string>
#include <cctype>
#include <algorithm>

namespace ruCubeScrambleParser {

    std::string vectorScrambleToStringScramble(const std::vector<uint8_t> &moves) {
        std::string ans = std::accumulate(  begin(moves),
                                            end(moves),
                                            std::string(""),
                                            [] (const auto &lhs, const auto &rhs) {
                                                return rhs < 6 ? lhs + std::string(" ") + ruCubeMovesStrings[rhs] : lhs;
                                            });

        return ans.substr(1);
    }

    std::vector<uint8_t> stringScrambleToVectorScramble(const std::string &moves) {
        std::vector<uint8_t> ans;

        std::regex r("[RU][[:space:]]*['2]?");
        auto moves_begin = std::sregex_iterator(moves.begin(), moves.end(), r);
        auto moves_end = std::sregex_iterator();

        for (std::sregex_iterator it = moves_begin; it != moves_end; ++it) {
            std::smatch match = *it;
            std::string match_str = match.str();

            auto jt = std::remove_if(begin(match_str), end(match_str), ::isspace);
            match_str.erase(jt, end(match_str));
            try {
                ans.push_back(static_cast<uint8_t>(ruCubeMovesInts.at(match_str)));
            } catch (const std::out_of_range& e) {
                break;
            }
        }

        return ans;
    }

}

#include "permutationGenerator.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>


template <class T>
std::vector<T> permutationGenerator<T>::generatePermutations(const std::set<int8_t> &locked, const std::set<int8_t> &ignored) {
    cleanup();

    for (const auto &x: ignored) {
        if (size(pieces) > static_cast<uint8_t>(x)) {
            pieces[x] = -1;
        }
    }

    sort(begin(pieces), end(pieces));
    std::set_difference( begin(pieces),
                    end(pieces),
                    begin(locked),
                    end(locked),
                    back_inserter(permuteablePieces));


    generateAns(locked);
    return ans;
}

template <class T>
void permutationGenerator<T>::cleanup() {
    permuteablePieces.clear();
    ans.clear();
    pieces.resize(size(tmp));

    std::iota(begin(pieces),
              end(pieces),
              0);

    tmp.fill(-2);
}

template <class T>
void permutationGenerator<T>::generateAns(const std::set<int8_t> &locked) {
    for (const auto &x: locked) {
        tmp[x] = x;
    }

    do {
        ans.push_back(tmp);
        for (size_t i = 0, k = 0; i < size(ans.back()); ++i) {
            if (ans.back()[i] == -2) {
                ans.back()[i] = permuteablePieces[k++];
            }
        }

    } while (std::next_permutation( begin(permuteablePieces),
                                    end(permuteablePieces)));
}

template class permutationGenerator<cornersArray>;
template class permutationGenerator<edgesArray>;

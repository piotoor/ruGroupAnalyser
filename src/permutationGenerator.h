#ifndef PERMUTATIONGENERATOR_H
#define PERMUTATIONGENERATOR_H

#include <vector>
#include <set>
#include <cstdint>
#include <array>
#include <type_traits>

using cornersArray = std::array<int8_t, 6>;
using edgesArray = std::array<int8_t, 7>;

template <class T>
class permutationGenerator
{
//    static_assert(!(std::is_convertible_v<T, cornersArray> or std::is_convertible_v<T, edgesArray>),
//                  "Only cornersArray and edgesArray are allowed.");
    public:
        permutationGenerator();
        explicit permutationGenerator(const permutationGenerator &other) = delete;
        permutationGenerator& operator=(const permutationGenerator &other) = delete;
        virtual ~permutationGenerator();

        std::vector<T> generatePermutations(const std::vector<int8_t> &locked = {}, const std::vector<int8_t> &ignored = {});

    private:
        void cleanup();
        void generateAns(const std::vector<int8_t> &locked);
        //std::multiset<int8_t> pieces;
        std::vector<int8_t> pieces;
        //std::multiset<int8_t> permuteablePieces;
        std::vector<int8_t> permuteablePieces;
        std::vector<T> ans;
        T tmp;

};

#endif // PERMUTATIONGENERATOR_H

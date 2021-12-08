#ifndef TESTCUSTOMDEFINITIONS_H
#define TESTCUSTOMDEFINITIONS_H
#include "gtest/gtest.h"
#include <vector>

namespace testDataGenerators {
    template<class T1, class T2, class T3>
    std::vector<std::tuple<T1, T2, T3>> combineWithExpected(std::vector<T1> v1, std::vector<T2> v2, std::vector<T3> expected) {
        std::vector<std::tuple<T1, T2, T3>> ans;

        size_t expectedInd = 0;
        for (const auto &x: v1) {
            for (const auto &y: v2) {
                ans.emplace_back(x, y, expected[expectedInd++]);
            }
        }

        return ans;
    }
}

namespace testCustomAsserts {
    template <class T>
    testing::AssertionResult AssertEqOct(const char* a_expr,
                                         const char* b_expr,
                                         T a,
                                         T b) {
        if (a == b) {
            return testing::AssertionSuccess();
        }
        std::stringstream ss;
        ss  << "Expected equality of these values:\n"
            << "\t" << a_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << a << "\n"
            << "\t" << b_expr << "\n"
            << "\t\t" << "Which is: " << std::oct << b;

        return testing::AssertionFailure() << ss.str();
    }
}

#endif

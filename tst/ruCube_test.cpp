#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>

namespace testDataGenerators {
//    template<class T1, class T2>
//    std::vector<std::tuple<T1, T2>> combine(std::vector<T1> v1, std::vector<T2> v2) {
//        std::vector<std::tuple<T1, T2>> ans;
//
//
//        return ans;
//    }

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


TEST(ruCubeTest, initialStateTest) {
    ruCube cube;

    ASSERT_EQ (ruCube::solvedEdges, cube.getEdges());
    ASSERT_EQ (ruCube::solvedCorners, cube.getCorners());
    ASSERT_TRUE (cube.isSolved(ruCube::allCornersMask, ruCube::allEdgesMask));
    ASSERT_TRUE (cube.isInDomino());
}

TEST(ruCubeTest, customIsSolvedFilterTest) {
    const std::vector<std::vector<uint8_t>> scrambles {
        { R2, U2, R2, U2, R2, U2 },
        { R,  U,  Ri, U,  R,  U2, Ri, U2 },
        { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
        { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
        { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
        { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
    };

    const std::vector<std::pair<uint64_t, uint32_t>> masks {
        { 0000000000077, 00000070 },
        { 0000000000007, 00000070 },
        { 0000000000070, 00000070 },

        { 0000000007700, 00000070 },
        { 0000000000700, 00000070 },
        { 0000000007000, 00000070 },

        { 0000000770000, 00000070 },
        { 0000000070000, 00000070 },
        { 0000000700000, 00000070 },

        { 0000000000077, 07000070 },
        { 0000000000007, 07000070 },
        { 0000000000070, 07000070 },

        { 0000000007700, 07000070 },
        { 0000000000700, 07000070 },
        { 0000000007000, 07000070 },

        { 0000000770000, 07000070 },
        { 0000000070000, 07000070 },
        { 0000000700000, 07000070 }
    };

    const std::vector<std::vector<bool>> expected {
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false },
        { true,  true,  true,       true,  true,  true,     false, true,  false,    false, false, false,    false, false, false,    false, false, false },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true  },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     false, false, false,    false, false, false,    false, false, false },
        { false, false, true,       true,  true,  true,     false, false, false,    false, false, true,     true,  true,  true,     false, false, false },
        { true,  true,  true,       true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true,     true,  true,  true  }
    };

    for (size_t scrInd = 0 ; scrInd < size(scrambles); ++scrInd) {
        ruCube cube;
        cube.scramble(scrambles[scrInd]);
        for (size_t mskInd = 0; mskInd < size(masks); ++mskInd) {
            auto &[cornersMask, edgesMask] = masks[mskInd];
            ASSERT_EQ(expected[scrInd][mskInd], cube.isSolved(cornersMask, edgesMask));
        }
    }
}

namespace {
    class ruCubePartialStateTests: public testing::TestWithParam<std::tuple<uint32_t, uint32_t, uint32_t>> {
        public:
           struct toString {
              template <class ParamType>
              std::string operator()(const testing::TestParamInfo<ParamType>& testData) const {
                 const auto& [intEdges, edgesMask, expected] = testData.param;

                 std::stringstream ss;
                 ss << std::oct << "edges_" << std::setw(7) << std::setfill('0') << intEdges << "_edgesMask_" << std::bitset<8>(edgesMask);
                 return ss.str();
              }
           };

        protected:
            ruCube cube;
    };

    INSTANTIATE_TEST_SUITE_P (
        getPartialEdgesTest,
        ruCubePartialStateTests,
        ::testing::ValuesIn(testDataGenerators::combineWithExpected<uint32_t, uint32_t, uint32_t> (
            {
                00123456,
                06543210,
            },
            {
                0b0000001,
                0b0000010,
                0b0000100,
                0b0001000,
                0b0010000,
                0b0100000,
                0b1000000,

                0b1111111,
                0b0000111,
                0b0001111,
                0b1111000,
                0b0000000,
            },
            {
                07777776,
                07777757,
                07777477,
                07773777,
                07727777,
                07177777,
                00777777,

                00123456,
                07777456,
                07773456,
                00123777,
                07777777,

                06777777,
                07577777,
                07747777,
                07773777,
                07777277,
                07777717,
                07777770,

                06543210,
                06547777,
                06543777,
                07773210,
                07777777
            }
        )),
        ruCubePartialStateTests::toString()
    );

    TEST_P(ruCubePartialStateTests, getPartialEdgesTest) {
        const auto& [intEdges, edgesMask, expectedPartialEdges] = GetParam();

        cube.setEdges(intEdges);
        ASSERT_EQ(expectedPartialEdges, cube.getPartialEdges(edgesMask));
    }
}


TEST(ruCubeTest, getPartialEdgesTest) {
    const std::vector<uint32_t> edgesMasks {
        0b0000001,
        0b0000010,
        0b0000100,
        0b0001000,
        0b0010000,
        0b0100000,
        0b1000000,

        0b1111111,
        0b0000111,
        0b0001111,
        0b1111000,
        0b0000000,
    };

    const std::vector<uint32_t> intEdges {
        00123456,
        06543210,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialEdges {
        {   07777776,
            07777757,
            07777477,
            07773777,
            07727777,
            07177777,
            00777777,

            00123456,
            07777456,
            07773456,
            00123777,
            07777777    },

        {   06777777,
            07577777,
            07747777,
            07773777,
            07777277,
            07777717,
            07777770,

            06543210,
            06547777,
            06543777,
            07773210,
            07777777    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialEdges); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(edgesMasks); ++maskInd) {
            cube.setEdges(intEdges[expectedInd]);
            ASSERT_EQ(expectedPartialEdges[expectedInd][maskInd], cube.getPartialEdges(edgesMasks[maskInd]));
        }
    }
}

TEST(ruCubeTest, getPartialCornersPermTest) {
    const std::vector<uint64_t> cornersMasks {
        0b000001,
        0b000010,
        0b000100,
        0b001000,
        0b010000,
        0b100000,

        0b111111,
        0b000111,
        0b001111,
        0b111000,
        0b000000,
        0b110010
    };

    const std::vector<uint64_t> intCorners {
        0000102030405,
        0050403020100,
        0442142251013,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialCornersPerms {
        {   0777775,
            0777747,
            0777377,
            0772777,
            0717777,
            0077777,

            0012345,
            0777345,
            0772345,
            0012777,
            0777777,
            0017747    },

        {   0577777,
            0747777,
            0773777,
            0777277,
            0777717,
            0777770,

            0543210,
            0543777,
            0543277,
            0777210,
            0777777,
            0747710    },

        {   0777577,
            0477777,
            0777773,
            0772777,
            0717777,
            0777707,

            0412503,
            0477573,
            0472573,
            0712707,
            0777777,
            0417707    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialCornersPerms); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(cornersMasks); ++maskInd) {
            cube.setCorners(intCorners[expectedInd]);
            ASSERT_EQ(expectedPartialCornersPerms[expectedInd][maskInd], cube.getPartialCornersPerm(cornersMasks[maskInd]));
        }
    }
}

TEST(ruCubeTest, getPartialCornersOrientTest) {
    const std::vector<uint64_t> cornersMasks {
        0b000001,
        0b000010,
        0b000100,
        0b001000,
        0b010000,
        0b100000,

        0b111111,
        0b000111,
        0b001111,
        0b111000,
        0b000000,
        0b110010
    };

    const std::vector<uint64_t> intCorners {
        0000102030405,
        0151413121110,
        0442142251013,
    };

    const std::vector<std::vector<uint32_t>> expectedPartialCornersOrients {
        {   0777770,
            0777707,
            0777077,
            0770777,
            0707777,
            0077777,

            0000000,
            0777000,
            0770000,
            0000777,
            0777777,
            0007707    },

        {   0177777,
            0717777,
            0771777,
            0777177,
            0777717,
            0777771,

            0111111,
            0111777,
            0111177,
            0777111,
            0777777,
            0717711    },

        {   0777277,
            0477777,
            0777771,
            0774777,
            0727777,
            0777717,

            0424211,
            0477271,
            0474271,
            0724717,
            0777777,
            0427717    },
    };

    ruCube cube;
    for (size_t expectedInd = 0; expectedInd < size(expectedPartialCornersOrients); ++expectedInd) {
        for (size_t maskInd = 0; maskInd < size(cornersMasks); ++maskInd) {
            cube.setCorners(intCorners[expectedInd]);
            ASSERT_EQ(expectedPartialCornersOrients[expectedInd][maskInd], cube.getPartialCornersOrient(cornersMasks[maskInd]));
        }
    }
}

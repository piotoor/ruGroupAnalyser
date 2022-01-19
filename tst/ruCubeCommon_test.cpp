#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"
#include "testCustomDefinitions.h"
#include "ruCubeFactory.h"
#include "ruCubeScrambleParser.h"
#include <vector>

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonCubeStateTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonCubeStateTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonCubeStateTests() {
            }

            std::unique_ptr<ruBaseCube> cube;
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonCubeStateTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonCubeStateTests, commonSettersGettersTest) {
        this->cube->setEdges(1234);
        this->cube->setCorners(3432243);
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, UINT32_C(1234), this->cube->getEdges());
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, UINT64_C(3432243), this->cube->getCorners());

        this->cube->setCube(423234, 1234);
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, UINT32_C(1234), this->cube->getEdges());
        EXPECT_PRED_FORMAT2(testCustomAsserts::AssertEqOct, UINT32_C(423234), this->cube->getCorners());
    }

    TYPED_TEST(ruCubeAndLutCubeCommonCubeStateTests, cubeStateResetTest) {
        std::vector<uint8_t> turns;

        for (const auto &t: { R, U, Ri, U, R, U2, Ri, U2, R2, Ui, Ri }) {
            turns.push_back(t);
            SCOPED_TRACE("turn = " + ruCubeScrambleParser::vectorScrambleToStringScramble(turns));

            this->cube->turn(t);
            ASSERT_FALSE(this->cube->isSolved());
            this->cube->reset();
            ASSERT_TRUE(this->cube->isSolved());
        }
    }
}

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonSingleTurnTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonSingleTurnTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonSingleTurnTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<uint8_t> turns {
                R, R, R, R,
                R2, R2,
                U2, U2,
                Ui, Ui, Ui, Ui,
                Ri, U, Ri, Ui, Ri, Ui, Ri, U, R, U, R2,
                R2, U2, R2, U2, R2, U2, R2, U2, R2, U2, R2, U2,
                Ri, U, Ri, Ui, Ri, Ui, Ri, U, R, U, R2,
                Ri, U, Ri, Ui, Ri, Ui, Ri, U, R, U, R2,
                R, U, Ri, U, R, U2, Ri, U2,
                R, U, Ri, U, R, U2, Ri, U2,
                R, U, Ri, U, R, U2, Ri, U2
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonSingleTurnTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonSingleTurnTests, singleTurnTest) {
        for (const auto &t: this->turns) {
            this->cube->turn(t);
        }

        ASSERT_TRUE(this->cube->isSolved());
    }

    TYPED_TEST(ruCubeAndLutCubeCommonSingleTurnTests, singleTurnInversionTest) {
        for (const auto &t: this->turns) {
            this->cube->inverseTurn(t);
        }

        ASSERT_TRUE(this->cube->isSolved());
    }
}

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonSingleTurnNegativeTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonSingleTurnNegativeTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonSingleTurnNegativeTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<uint8_t> invalidTurns {
                6, 7, 8, 9, 10, 11, 12, 15, 20, 30, 100, 255
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonSingleTurnNegativeTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonSingleTurnNegativeTests, singleTurnNegativeTest) {
        for (const auto &i: this->invalidTurns) {
            SCOPED_TRACE("i = " + std::to_string(i));

            ASSERT_THROW (
                try {
                    this->cube->turn(i);
                } catch (const ruCubeTurnException &e) {
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), std::string(e.what()));
                    throw;
                },
                ruCubeTurnException
            );
        }
    }

    TYPED_TEST(ruCubeAndLutCubeCommonSingleTurnNegativeTests, singleTurnInversionNegativeTest) {
        for (const auto &i: this->invalidTurns) {
            SCOPED_TRACE("i = " + std::to_string(i));

            ASSERT_THROW (
                try {
                    this->cube->inverseTurn(i);
                } catch (const ruCubeTurnException &e) {
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), std::string(e.what()));
                    throw;
                },
                ruCubeTurnException
            );
        }
    }
}

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::tuple<std::vector<uint8_t>, bool, bool, bool, bool>> testData {
                                                                                                  //domino    M       E       S
                {{ R2 },                                                                            true,   true,   true,   true  },
                {{ U },                                                                             true,   false,  true,   false },
                {{ U2 },                                                                            true,   true,   true,   true  },
                {{ Ui },                                                                            true,   false,  true,   false },
                {{ R2, U },                                                                         true,   false,  true,   false },
                {{ R2, U2 },                                                                        true,   true,   true,   true  },
                {{ R2, Ui },                                                                        true,   false,  true,   false },
                {{ R2, U2, R2, U2, R2, U2 },                                                        true,   true,   true,   true  },
                {{ R2, U, R2, Ui, R2, U, R2, U, R2, Ui, R2, Ui, R2, U, R2, U2, R2, Ui, R2, U2 },    true,   false,  true,   false },
                {{ Ri, U, Ri, Ui, Ri, Ui, Ri, U, R, U, R2 },                                        true,   false,  true,   false },
                {{ R2, U, R2, U2, R2, Ui, R2, Ui, R2 },                                             true,   false,  true,   false },
                {{ R2, U, R2, U2, R2, Ui, R2, U, R },                                               false,  false,  false,  false },
                {{ R2, U, R2, U2, R, Ui, R2, Ui, R2 },                                              false,  false,  false,  false },
                {{ R },                                                                             false,  true,   false,  false },
                {{ Ri },                                                                            false,  true,   false,  false },
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests, isInDominoTest) {
        for (const auto &data: this->testData) {
            auto scr = std::get<0>(data);
            auto expected = std::get<1>(data);
            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

            this->cube->reset();
            this->cube->scramble(scr);
            ASSERT_EQ(expected, this->cube->isInDomino());
        }
    }

    TYPED_TEST(ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests, isSolvedMEinMTest) {
        for (const auto &data: this->testData) {
            auto scr = std::get<0>(data);
            auto expected = std::get<2>(data);
            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

            this->cube->reset();
            this->cube->scramble(scr);
            ASSERT_EQ(expected, this->cube->isSolvedMEinM());
        }
    }

    TYPED_TEST(ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests, isSolvedEEinETest) {
        for (const auto &data: this->testData) {
            auto scr = std::get<0>(data);
            auto expected = std::get<3>(data);
            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

            this->cube->reset();
            this->cube->scramble(scr);
            ASSERT_EQ(expected, this->cube->isSolvedEEinE());
        }
    }

    TYPED_TEST(ruCubeAndLutCubeCommonIsPartOfTheCubeSolvedTests, isSolvedSEinSTest) {
        for (const auto &data: this->testData) {
            auto scr = std::get<0>(data);
            auto expected = std::get<4>(data);
            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

            this->cube->reset();
            this->cube->scramble(scr);
            ASSERT_EQ(expected, this->cube->isSolvedSEinS());
        }
    }
}

namespace {
template <class T>
    class ruCubeAndLutCubeCommonScrambleTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonScrambleTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonScrambleTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::vector<uint8_t>> scrambles {
                { R },
                { R2 },
                { Ri },
                { U },
                { U2 },
                { Ui },
                { R, U },
                { R, U2 },
                { R, Ui },
                { R2, U },
                { R2, U2 },
                { R2, Ui },
                { Ri, U },
                { Ri, U2 },
                { Ri, Ui },
                { R, U, Ri, U, R, U2, Ri },
                { R2, U2, R2, U2, R2, U2 },
                { R2, U, R2, U2, R, Ui, R2, Ui, R2 },
                { R2, U, R2, Ui, R2, U, R2, U, R2, Ui, R2, Ui, R2, U, R2, U2, R2, Ui, R2, U2 }
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonScrambleTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonScrambleTests, scrambleInverseScrambleCancellingOutTest) {
            for (const auto &scr: this->scrambles) {
                SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));

                this->cube->scramble(scr);
                this->cube->inverseScramble(scr);
                ASSERT_TRUE(this->cube->isSolved());
        }
    }
}

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonScrambleNegativeTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonScrambleNegativeTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonScrambleNegativeTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::vector<uint8_t>> invalidScrambles {
                { 6 },
                { R, U, R2, U2, Ri, Ui, 10, U2, R2, 8, 10 },
                { R, U, R2, Ri, R2, Ri, 6 }
            };

            static inline const std::vector<uint8_t> firstInvalidTurn {
                6,
                10,
                6
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonScrambleNegativeTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonScrambleNegativeTests, scrambleNegativeTest) {
        size_t i = 0;
        for (const auto &scr: this->invalidScrambles) {
            SCOPED_TRACE("i = " + std::to_string(i));

            ASSERT_THROW (
                try {
                    this->cube->scramble(scr);
                } catch (const ruCubeTurnException &e) {
                    std::cout << std::string(e.what()) << std::endl;
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(this->firstInvalidTurn[i]) + ") out of range (which is [0:5])"), std::string(e.what()));
                    throw;
                },
                ruCubeTurnException
            );

            ++i;
        }
    }

    TYPED_TEST(ruCubeAndLutCubeCommonScrambleNegativeTests, scrambleInversionNegativeTest) {
        size_t i = 0;
        for (const auto &scr: this->invalidScrambles) {
            SCOPED_TRACE("i = " + std::to_string(i));

            ASSERT_THROW (
                try {
                    this->cube->inverseScramble(scr);
                } catch (const ruCubeTurnException &e) {
                    std::cout << std::string(e.what()) << std::endl;
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(this->firstInvalidTurn[i]) + ") out of range (which is [0:5])"), std::string(e.what()));
                    throw;
                },
                ruCubeTurnException
            );

            ++i;
        }
    }
}

namespace {
    template <class T>
    class ruCubeAndLutCubeCommonIsSolvedTests: public testing::Test {
        protected:
            ruCubeAndLutCubeCommonIsSolvedTests(): cube(std::make_unique<T>()) {
            }

            virtual ~ruCubeAndLutCubeCommonIsSolvedTests() {
            }

            std::unique_ptr<ruBaseCube> cube;

            static inline const std::vector<std::vector<uint8_t>> scrambles {
                { R2, U2, R2, U2, R2, U2 },
                { R,  U,  Ri, U,  R,  U2, Ri, U2 },
                { Ri, U,  Ri, Ui, Ri, Ui, Ri, U,  R,  U,  R2 },
                { R2, U2, R2, U2, R2, U,  R2, U2, R2, U2, R2, Ui },
                { R,  U,  Ri, Ui, R,  U,  Ri, Ui, R,  U,  Ri, Ui },
                { Ri, Ui, R,  Ui, Ri, U2, R,  U2, R,  U,  Ri, U,  R,  U2, Ri, U2 }
            };

            static inline const std::vector<std::pair<uint64_t, uint32_t>> masks {
                { T::allCornersMask,         T::allEdgesMask },
                { 00,                        T::allEdgesMask },
                { T::allCornersMask,         00              },
                { 00,                        00              },
                { T::allCornersOrientMask,   00              },
                { T::allCornersPermMask,     00              },
                { T::allCornersOrientMask,   T::allEdgesMask },
                { T::allCornersPermMask,     T::allEdgesMask }
            };

            static inline const std::vector<std::vector<bool>> expected {
                { false, false, true,  true,  true,  true,  false, false },
                { false, false, false, true,  false, true,  false, false },
                { false, false, true,  true,  true,  true,  false, false },
                { false, false, true,  true,  true,  true,  false, false },
                { false, true,  false, true,  false, false, false, false },
                { false, true,  false, true,  false, true,  false, true  }
            };
    };

    using testing::Types;
    using Implementations = Types<ruCube, ruLutCube>;
    TYPED_TEST_SUITE(ruCubeAndLutCubeCommonIsSolvedTests, Implementations);

    TYPED_TEST(ruCubeAndLutCubeCommonIsSolvedTests, predefinedIsSolvedFilterTest) {
        for (size_t scrInd = 0 ; scrInd < size(this->scrambles); ++scrInd) {

            this->cube->reset();
            this->cube->scramble(this->scrambles[scrInd]);
            for (size_t mskInd = 0; mskInd < size(this->masks); ++mskInd) {
                auto &[cornersMask, edgesMask] = this->masks[mskInd];
                SCOPED_TRACE("\nscrInd = " + std::to_string(scrInd) + "\nmskInd = " + std::to_string(mskInd));
                ASSERT_EQ(this->expected[scrInd][mskInd], this->cube->isSolved(cornersMask, edgesMask));
            }
        }
    }
}

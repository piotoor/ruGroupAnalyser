#include "gtest/gtest.h"
#include "ruCube.h"
#include "ruException.h"
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
        ASSERT_EQ (1234, this->cube->getEdges());
        ASSERT_EQ (3432243, this->cube->getCorners());

        this->cube->setCube(423234, 1234);
        ASSERT_EQ (1234, this->cube->getEdges());
        ASSERT_EQ (423234, this->cube->getCorners());
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
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), e.what());
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
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(i) + ") out of range (which is [0:5])"), e.what());
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

//    TYPED_TEST(ruCubeAndLutCubeCommonScrambleTests, scrambleAndScrambleInversionTest) {
//        for (const auto &data: this->testData) {
//            auto &[scr, expected] = data;
//            SCOPED_TRACE("scr = " + ruCubeScrambleParser::vectorScrambleToStringScramble(scr));
//
//            this->cube->scramble(scr);
//            this->cube->inverseScramble(scr);
//            ASSERT_TRUE(this->cube->isSolved());
//        }
//    }
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
                    std::cout << e.what() << std::endl;
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(this->firstInvalidTurn[i]) + ") out of range (which is [0:5])"), e.what());
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
                    std::cout << e.what() << std::endl;
                    ASSERT_EQ(std::string("ruCubeTurnException: Cube turn index (which is " + std::to_string(this->firstInvalidTurn[i]) + ") out of range (which is [0:5])"), e.what());
                    throw;
                },
                ruCubeTurnException
            );

            ++i;
        }
    }
}

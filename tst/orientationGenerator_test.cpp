#include "gtest/gtest.h"
#include "orientationGenerator.h"

#include <vector>
#include <iostream>
using namespace std;


TEST(orientationGeneratorTest, generateOrientationtTest) {
    orientationGenerator gen;

    auto orients = gen.generateOrientations(0);
    std::vector<std::vector<int8_t>> expectedOrients = {
        { }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(1);
    expectedOrients = {
        { 0 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(2);
    expectedOrients = {
        { 0, 0 },
        { 1, 2 },
        { 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(3);
    expectedOrients = {
        { 0, 0, 0 },
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 1, 1 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 },
        { 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(4);
    expectedOrients = {
        { 0, 0, 0, 0 },
        { 0, 0, 1, 2 },
        { 0, 0, 2, 1 },
        { 0, 1, 0, 2 },
        { 0, 1, 1, 1 },
        { 0, 1, 2, 0 },
        { 0, 2, 0, 1 },
        { 0, 2, 1, 0 },
        { 0, 2, 2, 2 },
        { 1, 0, 0, 2 },
        { 1, 0, 1, 1 },
        { 1, 0, 2, 0 },
        { 1, 1, 0, 1 },
        { 1, 1, 1, 0 },
        { 1, 1, 2, 2 },
        { 1, 2, 0, 0 },
        { 1, 2, 1, 2 },
        { 1, 2, 2, 1 },
        { 2, 0, 0, 1 },
        { 2, 0, 1, 0 },
        { 2, 0, 2, 2 },
        { 2, 1, 0, 0 },
        { 2, 1, 1, 2 },
        { 2, 1, 2, 1 },
        { 2, 2, 0, 2 },
        { 2, 2, 1, 1 },
        { 2, 2, 2, 0 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    orients = gen.generateOrientations(5);
    expectedOrients = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2 },
        { 0, 0, 0, 2, 1 },
        { 0, 0, 1, 0, 2 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 1, 2, 0 },
        { 0, 0, 2, 0, 1 },
        { 0, 0, 2, 1, 0 },
        { 0, 0, 2, 2, 2 },
        { 0, 1, 0, 0, 2 },
        { 0, 1, 0, 1, 1 },
        { 0, 1, 0, 2, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 1, 2, 2 },
        { 0, 1, 2, 0, 0 },
        { 0, 1, 2, 1, 2 },
        { 0, 1, 2, 2, 1 },
        { 0, 2, 0, 0, 1 },
        { 0, 2, 0, 1, 0 },
        { 0, 2, 0, 2, 2 },
        { 0, 2, 1, 0, 0 },
        { 0, 2, 1, 1, 2 },
        { 0, 2, 1, 2, 1 },
        { 0, 2, 2, 0, 2 },
        { 0, 2, 2, 1, 1 },
        { 0, 2, 2, 2, 0 },
        { 1, 0, 0, 0, 2 },
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 2, 0 },
        { 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 0, 1, 2, 2 },
        { 1, 0, 2, 0, 0 },
        { 1, 0, 2, 1, 2 },
        { 1, 0, 2, 2, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 1, 0, 2, 2 },
        { 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 2 },
        { 1, 1, 1, 2, 1 },
        { 1, 1, 2, 0, 2 },
        { 1, 1, 2, 1, 1 },
        { 1, 1, 2, 2, 0 },
        { 1, 2, 0, 0, 0 },
        { 1, 2, 0, 1, 2 },
        { 1, 2, 0, 2, 1 },
        { 1, 2, 1, 0, 2 },
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 0 },
        { 1, 2, 2, 0, 1 },
        { 1, 2, 2, 1, 0 },
        { 1, 2, 2, 2, 2 },
        { 2, 0, 0, 0, 1 },
        { 2, 0, 0, 1, 0 },
        { 2, 0, 0, 2, 2 },
        { 2, 0, 1, 0, 0 },
        { 2, 0, 1, 1, 2 },
        { 2, 0, 1, 2, 1 },
        { 2, 0, 2, 0, 2 },
        { 2, 0, 2, 1, 1 },
        { 2, 0, 2, 2, 0 },
        { 2, 1, 0, 0, 0 },
        { 2, 1, 0, 1, 2 },
        { 2, 1, 0, 2, 1 },
        { 2, 1, 1, 0, 2 },
        { 2, 1, 1, 1, 1 },
        { 2, 1, 1, 2, 0 },
        { 2, 1, 2, 0, 1 },
        { 2, 1, 2, 1, 0 },
        { 2, 1, 2, 2, 2 },
        { 2, 2, 0, 0, 2 },
        { 2, 2, 0, 1, 1 },
        { 2, 2, 0, 2, 0 },
        { 2, 2, 1, 0, 1 },
        { 2, 2, 1, 1, 0 },
        { 2, 2, 1, 2, 2 },
        { 2, 2, 2, 0, 0 },
        { 2, 2, 2, 1, 2 },
        { 2, 2, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}


TEST(orientationGeneratorTest, generateOrientationtWithLockedPiecesTest) {
    orientationGenerator gen;

    std::vector<int8_t> lockedPieces = {};
    auto orients = gen.generateOrientations(0, lockedPieces);
    std::vector<std::vector<int8_t>> expectedOrients = {
        { }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {};
    orients = gen.generateOrientations(1, lockedPieces);
    expectedOrients = {
        { 0 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {};
    orients = gen.generateOrientations(2, lockedPieces);
    expectedOrients = {
        { 0, 0 },
        { 1, 2 },
        { 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { -1, 2 };
    orients = gen.generateOrientations(2, lockedPieces);
    expectedOrients = {
        { 1, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { -1, -1 };
    orients = gen.generateOrientations(2, lockedPieces);
    expectedOrients = {
        { 0, 0 },
        { 1, 2 },
        { 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { -1, -1, -1 };
    orients = gen.generateOrientations(3, lockedPieces);
    expectedOrients = {
        { 0, 0, 0 },
        { 0, 1, 2 },
        { 0, 2, 1 },
        { 1, 0, 2 },
        { 1, 1, 1 },
        { 1, 2, 0 },
        { 2, 0, 1 },
        { 2, 1, 0 },
        { 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { -1, -1, 2 };
    orients = gen.generateOrientations(3, lockedPieces);
    expectedOrients = {
        { 0, 1, 2 },
        { 1, 0, 2 },
        { 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { 0, -1, 2 };
    orients = gen.generateOrientations(3, lockedPieces);
    expectedOrients = {
        { 0, 1, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { 1, 0, 2 };
    orients = gen.generateOrientations(3, lockedPieces);
    expectedOrients = {
        { 1, 0, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = { 1, 0, 2, -1, -1, -1 };
    orients = gen.generateOrientations(6, lockedPieces);
    expectedOrients = {
        { 1, 0, 2, 0, 0, 0 },
        { 1, 0, 2, 0, 1, 2 },
        { 1, 0, 2, 0, 2, 1 },
        { 1, 0, 2, 1, 0, 2 },
        { 1, 0, 2, 1, 1, 1 },
        { 1, 0, 2, 1, 2, 0 },
        { 1, 0, 2, 2, 0, 1 },
        { 1, 0, 2, 2, 1, 0 },
        { 1, 0, 2, 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}



TEST(orientationGeneratorTest, generateOrientationtWithIgnoredPiecesTest) {
    orientationGenerator gen;
    std::vector<int8_t> lockedPieces = {};
    std::vector<int8_t> ignoredPieces = {};


    auto orients = gen.generateOrientations(0, lockedPieces, ignoredPieces);
    std::vector<std::vector<int8_t>> expectedOrients = {
        { }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2 },
        { 0, 0, 0, 2, 1 },
        { 0, 0, 1, 0, 2 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 1, 2, 0 },
        { 0, 0, 2, 0, 1 },
        { 0, 0, 2, 1, 0 },
        { 0, 0, 2, 2, 2 },
        { 0, 1, 0, 0, 2 },
        { 0, 1, 0, 1, 1 },
        { 0, 1, 0, 2, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 1, 2, 2 },
        { 0, 1, 2, 0, 0 },
        { 0, 1, 2, 1, 2 },
        { 0, 1, 2, 2, 1 },
        { 0, 2, 0, 0, 1 },
        { 0, 2, 0, 1, 0 },
        { 0, 2, 0, 2, 2 },
        { 0, 2, 1, 0, 0 },
        { 0, 2, 1, 1, 2 },
        { 0, 2, 1, 2, 1 },
        { 0, 2, 2, 0, 2 },
        { 0, 2, 2, 1, 1 },
        { 0, 2, 2, 2, 0 },
        { 1, 0, 0, 0, 2 },
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 2, 0 },
        { 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 0, 1, 2, 2 },
        { 1, 0, 2, 0, 0 },
        { 1, 0, 2, 1, 2 },
        { 1, 0, 2, 2, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 1, 0, 2, 2 },
        { 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 2 },
        { 1, 1, 1, 2, 1 },
        { 1, 1, 2, 0, 2 },
        { 1, 1, 2, 1, 1 },
        { 1, 1, 2, 2, 0 },
        { 1, 2, 0, 0, 0 },
        { 1, 2, 0, 1, 2 },
        { 1, 2, 0, 2, 1 },
        { 1, 2, 1, 0, 2 },
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 0 },
        { 1, 2, 2, 0, 1 },
        { 1, 2, 2, 1, 0 },
        { 1, 2, 2, 2, 2 },
        { 2, 0, 0, 0, 1 },
        { 2, 0, 0, 1, 0 },
        { 2, 0, 0, 2, 2 },
        { 2, 0, 1, 0, 0 },
        { 2, 0, 1, 1, 2 },
        { 2, 0, 1, 2, 1 },
        { 2, 0, 2, 0, 2 },
        { 2, 0, 2, 1, 1 },
        { 2, 0, 2, 2, 0 },
        { 2, 1, 0, 0, 0 },
        { 2, 1, 0, 1, 2 },
        { 2, 1, 0, 2, 1 },
        { 2, 1, 1, 0, 2 },
        { 2, 1, 1, 1, 1 },
        { 2, 1, 1, 2, 0 },
        { 2, 1, 2, 0, 1 },
        { 2, 1, 2, 1, 0 },
        { 2, 1, 2, 2, 2 },
        { 2, 2, 0, 0, 2 },
        { 2, 2, 0, 1, 1 },
        { 2, 2, 0, 2, 0 },
        { 2, 2, 1, 0, 1 },
        { 2, 2, 1, 1, 0 },
        { 2, 2, 1, 2, 2 },
        { 2, 2, 2, 0, 0 },
        { 2, 2, 2, 1, 2 },
        { 2, 2, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }




    ignoredPieces = { 1, 1, 0 };
    orients = gen.generateOrientations(3, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, -1, 0 },
        { -1, -1, 1 },
        { -1, -1, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    ignoredPieces = { 1, 1, 1};
    orients = gen.generateOrientations(3, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, -1, -1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    ignoredPieces = { 1, 0, 0 };
    orients = gen.generateOrientations(3, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 0 },
        { -1, 0, 1 },
        { -1, 0, 2 },
        { -1, 1, 0 },
        { -1, 1, 1 },
        { -1, 1, 2 },
        { -1, 2, 0 },
        { -1, 2, 1 },
        { -1, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    ignoredPieces = { 0, 1, 1 };
    orients = gen.generateOrientations(3, lockedPieces, ignoredPieces);
    expectedOrients = {
        { 0, -1, -1 },
        { 1, -1, -1 },
        { 2, -1, -1 }
    };

    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }


    ignoredPieces = { 0, 1, 1, 0 };
    orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    expectedOrients = {
        { 0, -1, -1, 0 },
        { 0, -1, -1, 1 },
        { 0, -1, -1, 2 },
        { 1, -1, -1, 0 },
        { 1, -1, -1, 1 },
        { 1, -1, -1, 2 },
        { 2, -1, -1, 0 },
        { 2, -1, -1, 1 },
        { 2, -1, -1, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}


TEST(orientationGeneratorTest, generateOrientationtWithIgnoredAndLockedPiecesTest) {
    orientationGenerator gen;
    std::vector<int8_t> lockedPieces = {-1, -1, 2, 1};
    std::vector<int8_t> ignoredPieces = {1, 1, 0, 0};
    auto orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    std::vector<std::vector<int8_t>>  expectedOrients = {
        { -1, -1, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, 1};
    ignoredPieces = {1, 0, 0, 0};
    orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, 1 },
        { -1, 1, 2, 1 },
        { -1, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, -1};
    ignoredPieces = {1, 0, 0, 0};
    orients = gen.generateOrientations(4, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, 0 },
        { -1, 0, 2, 1 },
        { -1, 0, 2, 2 },
        { -1, 1, 2, 0 },
        { -1, 1, 2, 1 },
        { -1, 1, 2, 2 },
        { -1, 2, 2, 0 },
        { -1, 2, 2, 1 },
        { -1, 2, 2, 2 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, 2, -1, 1};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, -1, 1},
        { -1, 1, 2, -1, 1},
        { -1, 2, 2, -1, 1}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }




    lockedPieces = {-1, -1, 2, -1, 1};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 2, -1, 1},
        { -1, 1, 2, -1, 1},
        { -1, 2, 2, -1, 1}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, 0};
    ignoredPieces = {1, 0, 0, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, 0, 0, -1, 0},
        { -1, 0, 1, -1, 0},
        { -1, 0, 2, -1, 0},
        { -1, 1, 0, -1, 0},
        { -1, 1, 1, -1, 0},
        { -1, 1, 2, -1, 0},
        { -1, 2, 0, -1, 0},
        { -1, 2, 1, -1, 0},
        { -1, 2, 2, -1, 0}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, -1};
    ignoredPieces = {0, 0, 0, 0, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 2 },
        { 0, 0, 0, 2, 1 },
        { 0, 0, 1, 0, 2 },
        { 0, 0, 1, 1, 1 },
        { 0, 0, 1, 2, 0 },
        { 0, 0, 2, 0, 1 },
        { 0, 0, 2, 1, 0 },
        { 0, 0, 2, 2, 2 },
        { 0, 1, 0, 0, 2 },
        { 0, 1, 0, 1, 1 },
        { 0, 1, 0, 2, 0 },
        { 0, 1, 1, 0, 1 },
        { 0, 1, 1, 1, 0 },
        { 0, 1, 1, 2, 2 },
        { 0, 1, 2, 0, 0 },
        { 0, 1, 2, 1, 2 },
        { 0, 1, 2, 2, 1 },
        { 0, 2, 0, 0, 1 },
        { 0, 2, 0, 1, 0 },
        { 0, 2, 0, 2, 2 },
        { 0, 2, 1, 0, 0 },
        { 0, 2, 1, 1, 2 },
        { 0, 2, 1, 2, 1 },
        { 0, 2, 2, 0, 2 },
        { 0, 2, 2, 1, 1 },
        { 0, 2, 2, 2, 0 },
        { 1, 0, 0, 0, 2 },
        { 1, 0, 0, 1, 1 },
        { 1, 0, 0, 2, 0 },
        { 1, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 0 },
        { 1, 0, 1, 2, 2 },
        { 1, 0, 2, 0, 0 },
        { 1, 0, 2, 1, 2 },
        { 1, 0, 2, 2, 1 },
        { 1, 1, 0, 0, 1 },
        { 1, 1, 0, 1, 0 },
        { 1, 1, 0, 2, 2 },
        { 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 2 },
        { 1, 1, 1, 2, 1 },
        { 1, 1, 2, 0, 2 },
        { 1, 1, 2, 1, 1 },
        { 1, 1, 2, 2, 0 },
        { 1, 2, 0, 0, 0 },
        { 1, 2, 0, 1, 2 },
        { 1, 2, 0, 2, 1 },
        { 1, 2, 1, 0, 2 },
        { 1, 2, 1, 1, 1 },
        { 1, 2, 1, 2, 0 },
        { 1, 2, 2, 0, 1 },
        { 1, 2, 2, 1, 0 },
        { 1, 2, 2, 2, 2 },
        { 2, 0, 0, 0, 1 },
        { 2, 0, 0, 1, 0 },
        { 2, 0, 0, 2, 2 },
        { 2, 0, 1, 0, 0 },
        { 2, 0, 1, 1, 2 },
        { 2, 0, 1, 2, 1 },
        { 2, 0, 2, 0, 2 },
        { 2, 0, 2, 1, 1 },
        { 2, 0, 2, 2, 0 },
        { 2, 1, 0, 0, 0 },
        { 2, 1, 0, 1, 2 },
        { 2, 1, 0, 2, 1 },
        { 2, 1, 1, 0, 2 },
        { 2, 1, 1, 1, 1 },
        { 2, 1, 1, 2, 0 },
        { 2, 1, 2, 0, 1 },
        { 2, 1, 2, 1, 0 },
        { 2, 1, 2, 2, 2 },
        { 2, 2, 0, 0, 2 },
        { 2, 2, 0, 1, 1 },
        { 2, 2, 0, 2, 0 },
        { 2, 2, 1, 0, 1 },
        { 2, 2, 1, 1, 0 },
        { 2, 2, 1, 2, 2 },
        { 2, 2, 2, 0, 0 },
        { 2, 2, 2, 1, 2 },
        { 2, 2, 2, 2, 1 }
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }



    lockedPieces = {-1, -1, -1, -1, 0};
    ignoredPieces = {1, 1, 1, 1, 0};
    orients = gen.generateOrientations(5, lockedPieces, ignoredPieces);
    expectedOrients = {
        { -1, -1, -1, -1, 0}
    };
    ASSERT_EQ(expectedOrients.size(), orients.size());
    for (uint8_t i = 0; i < expectedOrients.size(); ++i) {
        ASSERT_EQ(expectedOrients[i], orients[i]);
    }
}

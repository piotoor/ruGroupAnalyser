#include "gtest/gtest.h"
#include "dummy.h"

TEST(dummyTest, test) {
    EXPECT_EQ (foo(2, 4), 0);
}

TEST(dummyTest, test2) {
    EXPECT_EQ (foo(2, 6), 0);
}

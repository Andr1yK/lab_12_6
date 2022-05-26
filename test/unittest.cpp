#include <gtest/gtest.h>

#include "../src/extends/functions.cpp"

TEST(PASSED, alwaysIsTrue) {
  bool TRUE = true;

  EXPECT_EQ(TRUE, true);
}

TEST(FAILED, alwaysIsFalse) {
  bool TRUE = true;

  EXPECT_EQ(TRUE, false);
}
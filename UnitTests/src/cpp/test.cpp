#include <gtest/gtest.h>

TEST(AddTest, CheckAdd) {
    int ten = 5 + 5;
    EXPECT_EQ(ten, 10);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

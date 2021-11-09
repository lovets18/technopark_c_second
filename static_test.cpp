#include <gtest/gtest.h>

extern "C" {
  #include "static.c"
}

TEST(GET_NUMS_ARRS, Assert_True) {
  int real_res_first[10] = { 0 };
  int real_res_second[10] = { 0 };
  int exp_res_first[10];
  int exp_res_second[10];
  int n = 10;
  int first[10] = { 0 };
  int second[10] = { 0 };
  for (int i = 0; i < n; ++i) {
      first[i] = i;
      second[i] = i;
      exp_res_first[i] = 1;
      exp_res_second[i] = 1;
  }
  get_nums_arrs(real_res_first, real_res_second, first, second, n);
  bool equal = true;
  for (int i = 0; i < 10; ++i) {
      if ((real_res_first[i] != exp_res_first[i]) || (real_res_second[i] != exp_res_second[i])) equal = false;
  }
  EXPECT_TRUE(equal);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

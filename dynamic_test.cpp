#include <gtest/gtest.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <err.h>
#include <sysexits.h>

extern "C" {
  #include "dynamic.c"
}



TEST(ARR_BIGGER_ZERO, Assert_True) {
  
  int arr[5] = { 1, 2, 3, 4, 5 };
  int flag = arr_bigger_zero(arr, 5);
  
  EXPECT_TRUE(flag);
}

TEST(ARR_BIGGER_ZERO, Assert_False) {
  
  int arr[5] = { 0, 1, 2, 3, 4 };
  int flag = arr_bigger_zero(arr, 5);
  
  EXPECT_FALSE(flag);
}



TEST(SUM_ARRS, Assert_True) {
  int arr1[5] = { 0, 1, 2, 3, 4 };
  int arr2[5] = { 0, 1, 2, 3, 4 };
  int expected_result[5] = { 0, 2, 4, 6, 8 };
  int real_result[5] = { 0 };
  sum_arrs(arr1, arr2, 5);
  bool equal = true;
  for (int i = 0; i < 5; ++i) {
      if (arr1[i] != expected_result[i]) equal = false;
  }
  EXPECT_TRUE(equal);

}


TEST(WAIT_CHILDS, Assert_Eq) {
  
  int p[2];
  int status = 1;
  if ((p[0] = fork()) == 0) {
    sleep(0.5);
    exit(0);
  }
  if ((p[1] = fork()) == 0) {
    sleep(0.5);
    exit(0);
  }
  wait_childs(p, 2);

  if (!waitpid(p[0], &status, 0)) status = 0;
  if (!waitpid(p[1], &status, 0)) status = 0;
  
  EXPECT_EQ(status, 1);
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

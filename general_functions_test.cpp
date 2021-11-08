#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
  #include "general_functions.c"
}



TEST(GET_NUMS, Assert_True) {
  int number = 12345;
  int expected_result[10] = { 0, 1 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 };
  int real_result[10] = { 0 };
  get_nums(number, real_result);
  bool equal = true;
  for (int i = 0; i < 10; ++i) {
      if (real_result[i] != expected_result[i]) equal = false;
  }
  EXPECT_TRUE(equal);
}

TEST(WRITE_READ_FILE, Assert_True) {
  int expected_result[4] = { 0 };
  int real_result[4] = { 1, 2, 3, 4 };
  write_file("testfile.txt", real_result, 4);
  read_file("testfile.txt", expected_result, 4);
  bool equal = true;
  for (int i = 0; i < 4; ++i) {
      if (real_result[i] != expected_result[i]) equal = false;
  }
  EXPECT_TRUE(equal);
}


TEST(WRITE_READ_BIGGER_FILE, Assert_True) {
  int expected_result[4] = { 0 };
  int real_result[6] = { 1, 2, 3, 4, 5, 6 };
  write_file("testfile.txt", real_result, 4);
  read_file("testfile.txt", expected_result, 4);
  bool equal = true;
  for (int i = 0; i < 4; ++i) {
      if (real_result[i] != expected_result[i]) equal = false;
  }
  EXPECT_TRUE(equal);
}

TEST(GET_MEDIAN, Assert_True) {
  int arr[5] = { 5, 1, 4, 3, 2};
  EXPECT_EQ(3, get_median(arr, 5));
}

TEST(SORT_ARR, Assert_Eq) {
  int expected_result[5] = { 1, 2, 3, 4, 5 };
  int real_result[5] = { 5, 1, 4, 3, 2};
  sort(real_result, 5);
  bool equal = true;
  for (int i = 0; i < 5; ++i) {
      if (real_result[i] != expected_result[i]) equal = false;
  }
  EXPECT_TRUE(equal);
}


TEST(PRINT_ARR, Assert_Eq) {
  
  /*FILE* f;
  if ((f = fopen("printarr.txt", "w")) == NULL)
    fprintf(stderr, "Failed to open file for write\n");
  else {
    int real_result[5] = { 1, 2, 3, 4, 5};
    printarr(f, real_result, 5);

    if (fclose(f)) {
      fprintf(stderr, "Failed to close file\n"); 
      
    }

  }
  char str[39] = "string";

  if ((f = fopen("printarr.txt", "r")) == NULL) {
      fprintf(stderr, "Failed to open file for read\n");
  }
  else {
    if (fread(str, sizeof(str), 1, f) < 0) {
      fprintf(stderr, "Failed to read\n");
    }

    if (fclose(f)) {
      fprintf(stderr, "Failed to close file");
    }
  }
  printf("STR %s\n", str);
  EXPECT_EQ(strcmp(str, "| 0: 1 || 1: 2 || 2: 3 || 3: 4 || 4: 5 "), 0);
  EXPECT_EQ(1, 1);*/

  FILE* f;

  if ((f = fopen("printarr.txt", "w")) == NULL)
    fprintf(stderr, "Failed to open file for write\n");

  else {
    int real_result[2] = { 1, 2 };
    printarr(f, real_result, 2);
    if (fclose(f)) {
      fprintf(stderr, "Failed to close file\n"); 
      
    }
  }
  
  char str[18]="str";
  if ((f = fopen("printarr.txt", "r")) == NULL) {
      fprintf(stderr, "Failed to open file for read\n");
  }
  else {
    while (!feof(f))
      if (fread(str, sizeof(str), 1, f) != 0) {
        fprintf(stderr, "Failed to read\n");
      }

    if (fclose(f)) {
      fprintf(stderr, "Failed to close file");
    }
  }
      
  EXPECT_EQ(strcmp(str, "| 0: 1 || 1: 2 |\n"), 0);
}


TEST(PRINT_HIST, Assert_Eq) {
  FILE* f;

  if ((f = fopen("printhist.txt", "w")) == NULL)
    fprintf(stderr, "Failed to open file for write\n");

  else {
    int real_result[2] = { 1, 2 };
    print_hist(f, real_result, 2, 2, '#');
    if (fclose(f)) {
      fprintf(stderr, "Failed to close file\n"); 
      
    }
  }
  
  char str[5]="str";
  if ((f = fopen("printhist.txt", "r")) == NULL) {
      fprintf(stderr, "Failed to open file for read\n");
  }
  else {
    if (fread(str, sizeof(str), 1, f) == 0) {
      fprintf(stderr, "Failed to read\n");
    }

    if (fclose(f)) {
      fprintf(stderr, "Failed to close file");
    }
  }
      
  EXPECT_EQ(strcmp(str, "\n0 |#"), 0);

}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

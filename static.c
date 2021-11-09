#include <stdio.h>
#include <string.h>

#include "interface.h"


void get_nums_arrs(int *sum_first, int *sum_second, int *first, int *second, size_t size) {
    for (int i = 0; i < size; ++i) {
        get_nums(first[i], sum_first);
        get_nums(second[i], sum_second);
    }
}

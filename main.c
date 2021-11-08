#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "interface.h"


int main()
{
    int n = 100000000;
    int * first = (int*)malloc(n * sizeof(int));
    int * second = (int*)malloc(n * sizeof(int));
    
    int digits_first[10] = { 0 };
    int digits_second[10] = { 0 };

    static const char* file_name_first = "first.txt";
    static const char* file_name_second = "second.txt";

    //file preparing

    for (int i = 0; i < n; ++i) {
        first[i] = rand() % 10;
        second[i] = rand() % 10;
    }

    write_file(file_name_first, first, n);
    write_file(file_name_second, second, n);

    //read array from prepared files

    read_file(file_name_first, first, n);
    read_file(file_name_second, second, n);

    //procesing

    get_nums_arrs(digits_first, digits_second, first, second, n);


    // open file for printing results

    FILE* f;
    f = fopen("result.txt", "w");

    fprintf(f, "MED1: %d\n", get_median(digits_first, 10));
    fprintf(f, "MED2: %d\n", get_median(digits_second, 10));

    fprintf(f, "SUM:\n");
    printarr(f, digits_first, 10);
    printarr(f, digits_second, 10);

    print_hist(f, digits_first, 10, 40, '#');
    fprintf(f, "\n==============================================\n");
    print_hist(f, digits_second, 10, 40, '#');

    if (fclose(f)) {
        fprintf(stderr, "Failed to close file\n"); 
        return 1;
    }

    free(first);
    free(second);

    return 0;
}

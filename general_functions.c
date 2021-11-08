
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <string.h>
#include <err.h>
#include <sysexits.h>

#include "interface.h"



//write arr to file
void write_file(const char* filename, int* arr, int n) {
    FILE* f;
    f = fopen(filename, "w");

    if (!f) {
        fprintf(stderr, "Failed to open file for write\n");
    }

    for (int i = 0; i < n; ++i) {
        if (fwrite(&arr[i], sizeof(int), 1, f) != 1) {
            fprintf(stderr, "Failed to write struct into file\n");
        }
    }

    if (fclose(f)) {
        fprintf(stderr, "Failed to close file\n");
    }
}

//read arr from file
void read_file(const char* filename, int* arr, int n) {
    FILE* f;

    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open file for read\n");
    }
    else {
        for (int i = 0; i < n && !feof(f); ++i) {
            if (fread(&arr[i], sizeof(int), 1, f) != 1) {
                printf("%d\n", i);
                fprintf(stderr, "Failed to read\n");
            }
        }

        if (fclose(f)) {
            fprintf(stderr, "Failed to close file\n"); //return 1;
        }
    }
}


// get the digits from int
void get_nums(int number, int* num_count) {
    char str[10];
    sprintf(str, "%d", number);
    for (int i = 0; i < strlen(str); ++i) {
        num_count[str[i] - '0'] += 1;
    }
}


void sort(int* arr,int n){
	for(int i=1;i<n;i++){
		for(int j=i; j>0 && arr[j-1]>arr[j];j--){
			int tmp=arr[j-1];
			arr[j-1]=arr[j];
			arr[j]=tmp;
		}
	}
}


int get_median(int* arr, int size) {
    int *sort_arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        sort_arr[i] = arr[i];
    }
    sort(sort_arr, size);
    int result = sort_arr[size / 2];
    free(sort_arr);
    return result;
}


//print the histogramm of array indexes and values
void print_hist(FILE * f, int* arr, int size, int scale, char sym) {
    int max = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > max) max = arr[i];
    }

    for (int i = 0; i < size; ++i) {
        fprintf(f, "\n%d |", i);
        fprintf(f, "%.*s", (int)((scale * (arr[i] / (max * 1.0)))), "############################################################");
    }
    fprintf(f, "\n");
}



void printarr(FILE * f, int *arr, int size) {

    if (!f) fprintf(stderr, "INCORRECT STREAM\n");

    else {
        for (int i = 0; i < size; ++i) {
            fprintf(f, "| %d: %d |", i, arr[i]);
        }
        fprintf(f, "\n");
    }
        
}
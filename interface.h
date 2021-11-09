#pragma once


void get_nums(int number, int* num_count);

void write_file(const char* filename, int* arr, size_t n);

void read_file(const char* filename, int* arr, size_t n);

void get_nums(int number, int* num_count);

int get_median(int* arr, size_t size);

void print_hist(FILE * f, int* arr, size_t size, int scale, char sym);

void printarr(FILE *f, int *arr, size_t size);

void get_nums_arrs(int *sum_first, int *sum_second, int *first, int *second, size_t size);

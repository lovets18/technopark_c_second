#pragma once


void get_nums(int number, int* num_count);

void write_file(const char* filename, int* arr, int n);

void read_file(const char* filename, int* arr, int n);

void get_nums(int number, int* num_count);

int get_median(int* arr, int size);

void print_hist(FILE * f, int* arr, int size, int scale, char sym);

void printarr(FILE *f, int *arr, int size);

void get_nums_arrs(int *sum_first, int *sum_second, int *first, int *second, int size);

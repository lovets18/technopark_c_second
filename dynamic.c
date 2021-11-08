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

// check that arr elems are > 0
static int arr_bigger_zero(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] <= 0) return 0;
    }
    return 1;
}

// sum 2 arrs, the result in the first one
static void sum_arrs(int *arr1, int* arr2, int size) {
    for (int i = 0; i < size; ++i) {
        arr1[i] += arr2[i];
    }
}

// process data, that wasn't processed by childs, as remainder of the division of data elems and procs count
static void parent_sum_arr( int *nums_first, int *nums_second, 
                            int *first, int *second, 
                            int* sum_first, int* sum_second,
                            int *fd[], int n_proc,
                            int curID, int size) {
    if (read(fd[n_proc-1][0], &curID, sizeof(curID)) < 0) err(EX_SOFTWARE, "read pipes curID");                               
    for (int i = curID; i < size; ++i) {
        get_nums(first[i], nums_first);
        get_nums(second[i], nums_second);        
    }
    sum_arrs(sum_first, nums_first, 10);
    sum_arrs(sum_second, nums_second, 10);
}


//wait child processes
static void wait_childs(int *p, int n_proc) {
    for (int i = 0; i < n_proc; ++i) {
        int status;
        pid_t result = waitpid(-1, &status, 0);
        if (result) {
            printf("PID: %d. ", p[i]);
            if (WIFEXITED(status)) {
                printf("Exited with code %d\n", WEXITSTATUS(status));
            } 
            else if (WIFSIGNALED(status)) {
                printf("Killed by signal %d\n", WTERMSIG(status));
            }
            else if (WIFSTOPPED(status)) {
                printf("Stopped by signal %d\n", WSTOPSIG(status));
            }        
        }
    }
}

void get_nums_arrs(int *sum_first, int *sum_second, int *first, int *second, int size) {
    //prepare variables
    int n_proc = 2 * sysconf(_SC_NPROCESSORS_ONLN); // the number of cores * 2 = the number of procs
    pid_t *p = (pid_t*)malloc(n_proc*sizeof(pid_t));;
    int **fd = (int**)malloc(2*n_proc*sizeof(int*));
    for (int i = 0; i < 2*n_proc; ++i) {
        fd[i] = (int*)malloc(2*sizeof(int));
        if (pipe(fd[i])) err(EX_OSERR, "pipe");
    }

    int nums_first[10] = { 0 };
    int nums_second[10] = { 0 };
    const int step = size / n_proc;
    int curID = 0;

    //processing data
    for (int i = 0; i<n_proc; ++i) {
        //check that all returned values are ok
        if (arr_bigger_zero(p,i) && (p[i] = fork()) == 0) {

            if (i) read(fd[i-1][0], &curID, sizeof(curID)); //read from pipe if not fisrt child-proc
            curID += step;
            write(fd[i][1], &curID, sizeof(curID));
            for (int j = curID - step; j < curID; ++j) {
                get_nums(first[j], nums_first);
                get_nums(second[j], nums_second);
            }
            write(fd[n_proc + i][1], nums_first, sizeof(nums_first));
            write(fd[n_proc + i][1], nums_second, sizeof(nums_second));
            exit(0);
        }
    }

    wait_childs(p, n_proc);
    parent_sum_arr(nums_first,nums_second, first, second, sum_first, sum_second, fd, n_proc, curID, size);

    //read data from childs and summarize it
    for (int i = n_proc; i < (2*n_proc); ++i) {
        if ((read(fd[i][0], nums_first, sizeof(nums_first))) < 0 ||
        (read(fd[i][0], nums_second, sizeof(nums_second))) < 0) {
            err(EX_SOFTWARE, "read pipes");
        }
        sum_arrs(sum_first, nums_first, 10);
        sum_arrs(sum_second, nums_second, 10);
    }
    
    free(p);
    for (int i = 0; i < 2 * n_proc; ++i) {
        free(fd[i]);
    }
    free(fd);
}
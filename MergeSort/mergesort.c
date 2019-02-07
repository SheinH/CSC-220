#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <time.h>

#define ARRAY_LENGTH 25
#define RAND_LIM 100

typedef struct {
    int *ar, len;
} Array;

void merge_sort(int *a, int *aux, int length) {
    if (length > 2) {
        int third = length / 3;
        Array sections[] = {{a,             third},
                            {a + third,     third},
                            {a + 2 * third, length - (2 * third)}};
        int i;
        for (i = 0; i < 3; i++) {
            // Recursive call
            merge_sort(sections[i].ar, aux, sections[i].len);
        }
        // Merge sections
        int sec_index[] = {0, 0, 0}; // Start of unmerged ints in each section
        for (i = 0; i < length; i++) {
            int min = INT_MAX; // Minimum unmerged
            int min_sec; // Section containing the minimum value
            int section;
            for (section = 0; section < 3; section++) {
                int n = sections[section].ar[sec_index[section]];
                if (n < min && sec_index[section] < sections[section].len) {
                    min = n;
                    min_sec = section;
                }
            }
            aux[i] = min;
            sec_index[min_sec]++;
        }
        memcpy(a, aux, sizeof(int) * length);
    } else if (length == 2) {
        if (a[0] > a[1]) {
            int temp = a[1];
            a[1] = a[0];
            a[0] = temp;
        }
    }
}

void printArray(Array a) {
    int i;
    putchar('{');
    for (i = 0; i < a.len - 1; i++) {
        printf(" %d,", a.ar[i]);
    }
    printf(" %d }\n", a.ar[i]);
}

int main() {
    int nums[ARRAY_LENGTH], aux[ARRAY_LENGTH], i;
    srand(time(NULL));

    for (i = 0; i < ARRAY_LENGTH; i++) {
        nums[i] = rand() % RAND_LIM;
    }
    Array array = {nums, ARRAY_LENGTH};
    puts("Unsorted:");
    printArray(array);
    merge_sort(nums, aux, ARRAY_LENGTH);
    puts("Sorted:");
    printArray(array);
    return 0;
}
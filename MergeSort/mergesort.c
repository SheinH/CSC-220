#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>
#include <time.h>

#define ARRAY_LENGTH 25
#define RAND_LIM 10


void merge_sort(int *a, int *aux, int length) {

	typedef struct {
		int *ar, len, index;
	} Section;

	if (length == 2 && a[0] > a[1]) {
		int temp = a[1];
		a[1] = a[0];
		a[0] = temp;
	} else if (length > 2) {
		// Cut up the array into 3 sections, index is set to 0 for all 3
		int third = length / 3;
		Section sections[] = {{a,             third},
							  {a + third,     third},
							  {a + 2 * third, length - (2 * third)}};
		// Mergesort each section
		int i;
		for (i = 0; i < 3; i++)
			merge_sort(sections[i].ar, aux, sections[i].len);

		// Merge all three sections
		for (i = 0; i < length; i++) {
			int min = INT_MAX; // Minimum value
			int min_sec; // Section containing the minimum value
			int s; // Section
			//Iterate over each section, find lowest value to merge
			for (s = 0; s < 3; s++) {
				Section *sec = sections + s;
				if (sec->index < sec->len) {
					int n = sec->ar[sec->index];
					if (n < min) {
						min = n;
						min_sec = s;
					}
				}
			}
			//Write min to aux and increment the containing section's index
			aux[i] = min;
			sections[min_sec].index++;
		}
		//Copy aux to a
		memcpy(a, aux, sizeof(int) * length);
	}
}

void print_array(int *arr, int len) {
	int i;
	putchar('{');
	for (i = 0; i < len - 1; i++) {
		printf(" %d,", arr[i]);
	}
	printf(" %d }\n", arr[i]);
}

int main() {
	int i, nums[ARRAY_LENGTH], aux[ARRAY_LENGTH];
	srand(time(NULL));

	for (i = 0; i < ARRAY_LENGTH; i++)
		nums[i] = rand() % RAND_LIM;

	puts("Unsorted:");
	print_array(nums, ARRAY_LENGTH);

	merge_sort(nums, aux, ARRAY_LENGTH);

	puts("Sorted:");
	print_array(nums, ARRAY_LENGTH);
	return 0;
}
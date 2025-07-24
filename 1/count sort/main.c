#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int array[], int size, int range) {
    int count[range + 1], i;
    memset(count, 0, sizeof(count));

    // Store the count of each element
    for (i = 0; i < size; i++) {
        count[array[i]]++;
    }

    // Modify the count array by adding the previous counts
    for (i = 1; i <= range; i++) {
        count[i] += count[i - 1];
    }

    // Output array
    int output[size];
    for (i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // Copy the output array to the original array
    for (i = 0; i < size; i++) {
        array[i] = output[i];
    }
}

int main() {
    int array[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(array) / sizeof(array[0]);
    int range = 8; // The range of the input values (should be known)

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");

    countingSort(array, n, range);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}

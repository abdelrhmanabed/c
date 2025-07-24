//Abdelrhman abed  1193191
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void combSort(int arr[], int n) {
    int gap = n;
    float shrink = 1.3;
    int sorted = 0;

    while (!sorted) {
        gap = (int)(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = 1;
        }

        int i = 0;
        while (i + gap < n) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                sorted = 0;
            }
            i++;
        }
    }
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {8, 4, 1, 56, 3, -44, 23, -6, 28, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Before sorting array:\n");
    printArray(arr, n);

    combSort(arr, n);

    printf("After sorting array:\n");
    printArray(arr, n);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void selectionSort(int* arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[minIdx] > arr[j])
                minIdx = j;
        if (minIdx != i) swap(&arr[minIdx], &arr[i]);
    }
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    print_array(arr, n);
    selectionSort(arr, n);
    print_array(arr, n);
    free(arr);
    return 0;
}
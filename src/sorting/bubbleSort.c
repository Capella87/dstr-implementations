#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void bubbleSort(int* arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    print_array(arr, n);
    bubbleSort(arr, n);
    print_array(arr, n);
    free(arr);
    return 0;
}
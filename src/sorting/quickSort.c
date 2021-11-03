#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

int partition(int* arr, int left, int right)
{
    int* pivot = arr + left;
    int low = left + 1;
    int high = right;

    while (low <= high)
    {
        while (*pivot > arr[low] && low <= right)
            low++;
        while (*pivot < arr[high] && high > left)
            high--;
        if (low <= high) swap(arr + low, arr + high);
    }
    swap(pivot, &arr[high]);
    return high;
}

void quickSort(int* arr, int left, int right)
{
    if (left > right) return;
    int pivot_idx = partition(arr, left, right);
    quickSort(arr, left, pivot_idx - 1);
    quickSort(arr, pivot_idx + 1, right);
    return;
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printArray(arr, n);
    quickSort(arr, 0, n - 1);
    printArray(arr, n);

    free(arr);
    return 0;
}
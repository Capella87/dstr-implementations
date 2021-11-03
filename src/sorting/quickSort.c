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

void quick_sort(int* arr, int left, int right)
{
    if (left > right) return;
    int pivot_idx = partition(arr, left, right);
    quick_sort(arr, left, pivot_idx - 1);
    quick_sort(arr, pivot_idx + 1, right);
    return;
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    print_array(arr, n);
    quick_sort(arr, 0, n - 1);
    print_array(arr, n);

    free(arr);
    return 0;
}

/*
input:
5
5 4 3 2 1

output:
5 4 3 2 1
1 2 3 4 5
*/
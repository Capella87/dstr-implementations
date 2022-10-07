#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./_common_/common.h"

int get_pivot(int min, int max)
{
    srand((unsigned)time(NULL));
    return min + rand() % (max - min);
}

int partition(int* arr, int left, int right, int pivot_idx)
{
    if (pivot_idx != right) swap(&arr[pivot_idx], &arr[right]);
    int i = left, j = right - 1;
    int* pivot = arr + right;

    while (i <= j)
    {
        while (i <= j && arr[i] <= *pivot)
            i++;
        while (i <= j && *pivot <= arr[j])
            j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[i], pivot);

    return i;
}

void quick_sort(int* arr, int left, int right)
{
    if (left >= right) return;

    int pivot_idx = get_pivot(left, right);

    pivot_idx = partition(arr, left, right, pivot_idx);
    quick_sort(arr, left, pivot_idx - 1);
    quick_sort(arr, pivot_idx + 1, right);
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
Input:
5
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
*/
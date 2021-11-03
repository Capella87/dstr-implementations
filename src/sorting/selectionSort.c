#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void selection_sort(int* arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[min_idx] > arr[j])
                min_idx = j;
        if (min_idx != i) swap(&arr[min_idx], &arr[i]);
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
    selection_sort(arr, n);
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
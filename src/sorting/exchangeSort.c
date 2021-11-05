#include <stdio.h>
#include <stdlib.h>
#include "../_common_/common.h"

void exchange_sort(int* arr, const int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (arr[i] > arr[j]) swap(&arr[i], &arr[j]);
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    print_array(arr, n);
    exchange_sort(arr, n);
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
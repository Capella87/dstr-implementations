#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./_common_/common.h"

void cocktail_sort(int* arr, const int size)
{
    int half = size / 2;
    bool is_swapped = false;
    
    for (int i = 0; i < half; i++)
    {
        for (int j = i; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                is_swapped = true;
            }
        }
        for (int j = size - i - 2; j > i; j--)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(&arr[j - 1], &arr[j]);
                is_swapped = true;
            }
        }
        if (!is_swapped) break;
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
    cocktail_sort(arr, n);
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
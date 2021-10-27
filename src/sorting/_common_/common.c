#include <stdio.h>
#include "common.h"

inline void printArray(int* arr, const int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

inline void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
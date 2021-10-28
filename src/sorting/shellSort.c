#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void shellSort(int* arr, const int size)
{
    for (int interval = size / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < size; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval)
                arr[j] = arr[j - interval];
            arr[j] = temp;
        }
    }
}

int main(void)
{
    int n;
    
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printArray(arr, n);
    shellSort(arr, n);
    printArray(arr, n);

    free(arr);
    return 0;
}
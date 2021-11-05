#include <stdio.h>
#include <stdlib.h>
#include "./_common_/common.h"

void shell_sort(int* arr, const int size)
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
    print_array(arr, n);
    shell_sort(arr, n);
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
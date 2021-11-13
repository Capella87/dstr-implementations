#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./_common_/common.h"
#define MAX 10000

void counting_sort(int* arr, int* counting, const int size)
{
    int idx = 0;
    for (int i = 0; i <= MAX; i++)
    {
        for (int j = 0; j < counting[i]; j++)
            arr[idx++] = i;
        if (idx == size) break;
    }
    return;
}

int main(void)
{
    int n;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    int* counter = (int*)malloc(sizeof(int) * (MAX + 1));
    memset(counter, 0, sizeof(int) * (MAX + 1));
    printf("Type numbers (0 - 10000):\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        counter[arr[i]]++;
    }
    print_array(arr, n);
    counting_sort(arr, counter, n);
    print_array(arr, n);

    free(arr);
    free(counter);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sorting/_common_/common.h"

int interpolation_search(int* arr, const int size, const int target)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + ((right - left) / (arr[right] - arr[left])) * (target - arr[left]); // Formula
        if (arr[mid] == target) return mid;
        else if (target < arr[mid]) right = mid - 1;
        else left = mid + 1;
    }

    return -1;
}

int comparer(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main(void)
{
    int n, target;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    print_array(arr, n);
    qsort((void*)arr, n, sizeof(int), comparer);
    print_array(arr, n);

    printf("Target: ");
    scanf("%d", &target);
    int result = interpolation_search(arr, n, target);
    if (result == -1) printf("%d is not exist in the array.\n", target);
    else printf("%d is exist at index %d in the array.\n", target, result);

    free(arr);
    return 0;
}

/*
Input:
5
5 4 3 2 1
3

Output:
5 4 3 2 1
1 2 3 4 5
3 is exist at index 2 in the array.
*/
#include <stdio.h>
#include <stdlib.h>

int binary_search_recur(int* arr, int left, int right, const int target)
{
    if (left >= right) return -1;

    int mid = (left + right) / 2;
    if (arr[mid] == target) return mid;
    else if (target < arr[mid]) return binary_search_recur(arr, left, mid - 1, target);
    else return binary_search_recur(arr, mid + 1, right, target);
}

int binary_search(int* arr, const int size, const int target)
{
    int left = 0, right = size - 1;
    int idx = -1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
        {
            idx = mid;
            break;
        }
        else if (target < arr[mid]) right = mid - 1;
        else left = mid + 1;
    }
    return idx;
}

int compare(const void* a, const void* b) // comparer for qsort function in C
{
    return *((int*)a) - *((int*)b);
}

int main(void)
{
    int n, target;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    qsort((void*)arr, (size_t)n, sizeof(int), compare); // It must be sorted before using binary search.
    scanf("%d", &target);
    printf("%d\n", binary_search(arr, n, target));
    printf("%d\n", binary_search_recur(arr, 0, n - 1, target));

    free(arr);
    return 0;
}

/*
Input:
5
5 4 3 2 1
-123

Output:
-1
-1
*/
#include <stdio.h>
#include <stdlib.h>

// It returns the smallest if there are numbers bigger than the target.
// Otherwise, it returns -1.

int upper_bound(int* arr, const int len, const int target)
{
    if (!arr) return -1;

    int left = 0, right = len - 1;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) left = mid + 1;
        else right = mid;
    }

    return arr[left] > target ? left : -1;
}

int compare(const void* t1, const void* t2)
{
    return *(int*)t1 - *(int*)t2;
}

int main(void)
{
    int n, target;

    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    qsort((int*)arr, n, sizeof(int), compare);
    printf("Type a target number: ");
    scanf("%d", &target);
    int min_idx = upper_bound(arr, n, target);
    if (min_idx == -1) printf("All elements in array are smaller than %d\n", target);
    else printf("%d is the smallest number which is bigger than %d\n", arr[min_idx], target);

    free(arr);
    return 0;
}
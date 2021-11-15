def partition(arr, left, right):
    pivot = arr[left]
    low = left + 1
    high = right

    while low <= high:
        while low <= right and pivot > arr[low]:
            low += 1
        while high > left and pivot < arr[high]:
            high -= 1
        if (low <= high):
            arr[low], arr[high] = arr[high], arr[low]
    arr[left], arr[high] = arr[high], arr[left]
    return high


def quick_sort(arr, left, right):
    if left > right:
        return
    pivot_idx = partition(arr, left, right)
    quick_sort(arr, left, pivot_idx - 1)
    quick_sort(arr, pivot_idx + 1, right)


def print_array(arr, n):
    for i in range(n):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)
print_array(arr, size)
quick_sort(arr, 0, size - 1)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
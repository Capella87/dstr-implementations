def selection_sort(arr, n):
    for i in range(0, n - 1):
        min_idx = i
        for j in range(i, n):
            if (arr[min_idx] > arr[j]):
                min_idx = j
        if min_idx != i:
            arr[min_idx], arr[i] = arr[i], arr[min_idx]


def print_array(arr, n):
    for i in range(0, n):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)
print_array(arr, size)
selection_sort(arr, size)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
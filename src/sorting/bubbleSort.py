def bubble_sort(arr: list, size: int) -> None:
    for i in range(0, size - 1):
        for j in range(0, size - 1 - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


def print_array(arr: list, size: int) -> None:
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

print_array(arr, size)
bubble_sort(arr, size)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
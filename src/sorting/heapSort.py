def heapify(arr: list, n: int, t_idx: int) -> None:
    largest = t_idx
    child_idx = t_idx * 2 + 1

    if child_idx < n and arr[largest] < arr[child_idx]:
        largest = child_idx
    child_idx += 1
    if child_idx < n and arr[largest] < arr[child_idx]:
        largest = child_idx
    if largest != t_idx:
        arr[largest], arr[t_idx] = arr[t_idx], arr[largest]
        heapify(arr, n, largest)


def heap_sort(arr: list, n: int) -> None:
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, -1, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)


def print_array(arr: list, size: int) -> None:
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

print_array(arr, size)
heap_sort(arr, size)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
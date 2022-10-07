import secrets
from sys import stdin

rand_generator = secrets.SystemRandom()


def get_pivot_idx(begin: int, end: int) -> int:
    return rand_generator.randint(begin, end)


def partition(arr: list, left: int, right: int, pivot_idx: int) -> int:
    pivot = arr[pivot_idx]
    arr[pivot_idx], arr[right] = arr[right], arr[pivot_idx]
    i = left
    j = right - 1

    while i <= j:
        while i <= j and arr[i] <= pivot:
            i += 1
        while i <= j and pivot <= arr[j]:
            j -= 1
        if i < j:
            arr[i], arr[j] = arr[j], arr[i]
    arr[i], arr[right] = arr[right], arr[i]

    return i


def quick_sort(arr: list, left: int, right: int) -> None:
    if left >= right:
        return
    pivot_idx = get_pivot_idx(left, right)

    pivot_idx = partition(arr, left, right, pivot_idx)
    quick_sort(arr, left, pivot_idx - 1)
    quick_sort(arr, pivot_idx + 1, right)


def print_array(arr: list) -> None:
    for i in arr:
        print(' %d' % i, end='')
    print()


def get_list() -> list:
    return list(map(int, stdin.readline().split(' ')))


lst = get_list()
print_array(lst)
quick_sort(lst, 0, len(lst) - 1)
print_array(lst)


'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
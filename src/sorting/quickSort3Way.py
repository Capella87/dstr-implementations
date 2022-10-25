# 3-Way Quick Sort to consider duplicates

import secrets

rgen = secrets.SystemRandom()


def get_random(left: int, right: int) -> int:
    return rgen.randint(left, right)


def partition(arr: list, left: int, right: int, p: int) -> tuple:
    lb = left
    ub = right

    arr[left], arr[p] = arr[p], arr[left]
    pivot = arr[left]

    i = left
    while i <= ub:
        if arr[i] == pivot:
            i += 1
        elif arr[i] < pivot:
            arr[lb], arr[i] = arr[i], arr[lb]
            lb += 1
            i += 1
        else:
            arr[i], arr[ub] = arr[ub], arr[i]
            ub -= 1

    return lb, ub


def quick_sort(arr: list, left: int, right: int) -> None:
    if left >= right:
        return

    pivot_idx = get_random(left, right) # Get random pivot index using pseudorandom generator
    n_pivots = partition(arr, left, right, pivot_idx)

    quick_sort(arr, left, n_pivots[0] - 1)
    quick_sort(arr, n_pivots[1] + 1, right)


def print_array(arr: list) -> None:
    for elem in arr:
        print(elem, end=' ')
    print()


arr = list(map(int, input().split()))
print_array(arr)
quick_sort(arr, 0, len(arr) - 1)
print_array(arr)

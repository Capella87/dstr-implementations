def shell_sort(arr: list, n: int) -> None:
    interval = n // 2
    while interval > 0:
        for i in range(interval, n):
            temp = arr[i] # save data
            j = i
            while j >= interval and arr[j - interval] > temp:
                arr[j] = arr[j - interval]
                j -= interval
            arr[j] = temp
        interval //= 2


def print_array(arr: list, n: int) -> None:
    for i in range(0, n):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)
print_array(arr, size)
shell_sort(arr, size)
print_array(arr, size)

'''
Input:
5
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
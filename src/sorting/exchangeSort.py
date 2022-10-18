def exchange_sort(arr: list, n: int) -> None:
    for i in range(0, n - 1):
        for j in range(i + 1, n):
            if (arr[i] > arr[j]):
                arr[i], arr[j] = arr[j], arr[i]


def print_array(arr: list, n: int) -> None:
    for i in range(0, n):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

print_array(arr, size)
exchange_sort(arr, size)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
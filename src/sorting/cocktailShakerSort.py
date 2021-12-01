def cocktail_sort(arr, size):
    r = size // 2
    is_swapped = False

    for i in range(r):
        for j in range(i, size - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                is_swapped = True
        for j in range(size - i - 2, i, -1):
            if arr[j - 1] > arr[j]:
                arr[j - 1], arr[j] = arr[j], arr[j - 1]
                is_swapped = True
        if is_swapped == False:
            break


def print_array(arr, size):
    for i in range(size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

print_array(arr, size)
cocktail_sort(arr, size)
print_array(arr, size)

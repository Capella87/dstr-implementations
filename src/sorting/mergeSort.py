def merge_sort(arr):
    if len(arr) <= 1:
        return

    mid = len(arr) // 2
    left = arr[:mid] # Split arr array into left and right.
    right = arr[mid:]

    # Divide
    merge_sort(left)
    merge_sort(right)

    # Conquer
    i = j = k = 0
    l_len = len(left)
    r_len = len(right)
    while i < l_len and j < r_len:
        if left[i] < right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1
    while i < l_len:
        arr[k] = left[i]
        i += 1
        k += 1
    while j < r_len:
        arr[k] = right[j]
        j += 1
        k += 1
    return


def print_array(arr, size):
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)
print("Before : ", end=' ')
print_array(arr, size)
merge_sort(arr)
print("After  : ", end=' ')
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
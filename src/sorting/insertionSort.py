def insertion_sort(arr, size):
    for i in range(1, size):
        temp = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > temp:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = temp


def print_array(arr, size):
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

print_array(arr, size)
insertion_sort(arr, size)
print_array(arr, size)

'''
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
'''
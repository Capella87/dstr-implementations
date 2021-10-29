def insertionSort(arr, size):
    for i in range(1, size):
        temp = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > temp:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = temp


def printArray(arr, size):
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

printArray(arr, size)
insertionSort(arr, size)
printArray(arr, size)
def bubbleSort(arr, size):
    for i in range(0, size - 1):
        for j in range(0, size - 1 - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]


def printArray(arr, size):
    for i in range(0, size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split()))
size = len(arr)

printArray(arr, size)
bubbleSort(arr, size)
printArray(arr, size)
def binary_search(arr, size, target):
    left = 0
    right = size - 1
    idx = -1
    
    while left <= right:
        mid = (left + right) // 2
        if target < arr[mid]:
            right = mid - 1
        elif arr[mid] < target:
            left = mid + 1
        else:
            idx = mid
            break
    return idx


def print_array(arr, size):
    for i in range(size):
        print(arr[i], end=' ')
    print()


arr = list(map(int, input().split(' ')))
size = len(arr)
print_array(arr, size)
arr.sort()
print_array(arr, size)

target = int(input("Target: "))
rt = binary_search(arr, size, target)

print("The target", end=' ')
if rt == -1:
    print(target, "is NOT exist.")
else:
    print(target, "is exist at index", rt, "in the array.")

'''
Input:
5 4 3 2 1
Target: 3

Output:
5 4 3 2 1
1 2 3 4 5
3 is exist at index 2 in the array.
'''
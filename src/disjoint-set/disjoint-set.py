def union_set(arr, a, b):
    a_root = find(arr, a)
    b_root = find(arr, b)

    if a_root == b_root or a_root == -1 or b_root == -1:
        return False
    
    if arr[b_root] < arr[a_root]:
        arr[a_root] = b_root
    else:
        if arr[a_root] == arr[b_root]:
            arr[a_root] -= 1
        arr[b_root] = a_root
    return True

def find(arr, target):
    if len(arr) <= target: return -1
    elif arr[target] < 0:
        return target
    else:
        arr[target] = find(arr, arr[target])
        return arr[target]

def get_root(arr, target):
    rt = find(arr, target)
    print('The root of', target, 'is', rt)


arr = []

size = int(input())
for i in range(0, size):
    arr.append(-1)

while True:
    inp = list(map(int, input().split(' ')))
    if inp[0] == 0: break
    elif inp[0] == 1: # Union
        union_set(arr, int(inp[1]), int(inp[2]))
    elif inp[0] == 2: # Get_root
        get_root(arr, int(inp[1]))

'''
Input:
100
2 1
1 1 2
1 1 3
2 2
2 3
2 1
1 1 4
1 5 6 
2 5
2 6
1 1 5
2 1
2 5
0

Output:
The root of 1 is 1
The root of 2 is 1
The root of 3 is 1
The root of 1 is 1
The root of 5 is 5
The root of 6 is 5
The root of 1 is 1
The root of 5 is 1
'''

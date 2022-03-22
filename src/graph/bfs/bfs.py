from collections import deque

arr = [[] for _ in range(10)]

def add_edge(src, target):
    global arr
    arr[src].append(target)
    arr[target].append(src)


def bfs(start):
    global arr
    is_visited = [False] * 10
    q = deque()

    print('BFS:', end=' ')

    is_visited[start] = True
    q.append(start)
    while len(q) > 0:
        v = q.popleft()
        print(v, end=' ')
        size = len(arr[v])
        for i in range(size):
            if is_visited[arr[v][i]] == False:
                is_visited[arr[v][i]] = True
                q.append(arr[v][i])


add_edge(1, 2);
add_edge(1, 5);
add_edge(2, 3);
add_edge(3, 4);
add_edge(3, 5);
add_edge(3, 7);
add_edge(4, 5);
add_edge(5, 7);
add_edge(6, 7);
add_edge(7, 9);

bfs(1)

'''
Output:
BFS: 1 2 5 3 4 7 6 9
'''
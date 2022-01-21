#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> vertices;

void add_edge(int from, int to)
{
    vertices[from].push_back(to);
    vertices[to].push_back(from);
}

void dfs_recursive(int v, bool* is_visited, const int n)
{
    if (is_visited[v]) return;

    is_visited[v] = true;
    cout << v << ' ';
    int size = (int)vertices[v].size();
    for (int i = size - 1; i >= 0; i--)
        if (!is_visited[vertices[v][i]])
            dfs_recursive(vertices[v][i], is_visited, n);
}

void dfs(int v, const int n)
{
    stack<int> stk;
    bool* is_visited = new bool[n]();

    cout << "DFS (Stack):     ";

    stk.push(v);
    while (!stk.empty())
    {
        v = stk.top();
        stk.pop();
        if (is_visited[v]) continue;

        is_visited[v] = true;
        cout << v << ' ';
        int size = (int)vertices[v].size();
        for (int i = 0; i < size; i++)
            if (!is_visited[vertices[v][i]])
                stk.push(vertices[v][i]);
    }
    cout << '\n';
    
    delete[] is_visited;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    vertices.resize(10);

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

    bool* is_visited = new bool[10]();
    cout << "DFS (Recursive): ";
    dfs_recursive(1, is_visited, 10);
    cout << '\n';
    dfs(1, 10);

    delete[] is_visited;
    return 0;
}

/*
Output:
DFS (Recursive): 1 5 7 9 6 3 4 2
DFS (Stack):     1 5 7 9 6 3 4 2
*/
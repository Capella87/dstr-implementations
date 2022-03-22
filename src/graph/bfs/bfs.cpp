#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> vertices;

void add_edge(int from, int to)
{
    vertices[from].push_back(to);
    vertices[to].push_back(from);
}

void bfs(int v, const int n)
{
    bool* is_visited = new bool[n]();
    queue<int> q;

    cout << "BFS: ";

    is_visited[v] = true;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        cout << v << ' ';
        q.pop();
        int size = (int)vertices[v].size();
        for (int i = 0; i < size; i++)
        {
            if (!is_visited[vertices[v][i]])
            {
                is_visited[vertices[v][i]] = true;
                q.push(vertices[v][i]);
            }
        }
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

    bfs(1, 10);

    return 0;
}

/*
Output:
BFS: 1 2 5 3 4 7 6 9
*/
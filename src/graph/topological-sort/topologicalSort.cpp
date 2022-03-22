#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void add_edge(vector<vector<int>>& arr, vector<int>& incoming, const int src, const int dest)
{
    arr[src].push_back(dest);
    incoming[dest]++;
}

bool topological_sort(vector<vector<int>>& arr, vector<int>& incoming)
{
    queue<int> task_q;
    vector<int> result;
    int size = (int)arr.size();

    for (int i = 0; i < size; i++) // Enqueue vertex if it does not have any incoming edges.
        if (!incoming[i]) task_q.push(i);

    while (!task_q.empty()) // Do until the queue is empty.
    {
        int v = task_q.front();
        task_q.pop();
        result.push_back(v);

        int dest_size = (int)arr[v].size();
        for (int i = 0; i < dest_size; i++)
        {
            if (--incoming[arr[v][i]] == 0) // Enqueue vertex under the same condition.
                task_q.push(arr[v][i]);
        }
    }
    if (result.size() != size) // Returns false if the graph has a cycle.
        return false;
    for (int i = 0; i < size; i++)
        cout << result[i] << ' ';
    cout << '\n';

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, src, dest;

    cin >> n; // Input the number of vertices.
    vector<vector<int>> arr(n);
    vector<int> incoming(n);

    while (1)
    {
        cin >> src;
        if (src == -1) break;
        cin >> dest;

        add_edge(arr, incoming, src, dest);
    }
    topological_sort(arr, incoming);

    return 0;
}

/*
Input:
5
0 1
0 2
0 3
1 2
2 3
4 3
4 2
-1

Output:
0 4 1 2 3
*/
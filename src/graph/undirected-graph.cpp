#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

typedef struct edge
{
    int src;
    int dest;
    int weight;
} edge;

typedef struct vertex
{
    int weight;
    vector<edge> adj;
} vertex;

class Undigraph
{
private:
    int e;
    int v;
    int size;
    vector<vertex> adj_list;

public:
    Undigraph()
    {
        e = v = size = 0;
        adj_list.resize(0);;
    }

    Undigraph(int n)
    {
        v = n;
        e = 0;
        size = n;
        adj_list.resize(n);
        for (int i = 0; i < n; i++)
            adj_list[i].weight = 0;
    }

    bool add_graph(int from, int to)
    {
        adj_list[from].adj.push_back({from, to, 0});
        adj_list[to].adj.push_back({ to, from, 0 });

        return true;
    }

    
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    Undigraph gr(100);
    vector<bool> is_visit(100);

    gr.add_graph(1, 2);
    gr.add_graph(2, 3);
    gr.add_graph(3, 5);
    gr.add_graph(4, 8);
    gr.add_graph(2, 4);
    gr.add_graph(2, 5);
    gr.add_graph(1, 4);
    gr.add_graph(8, 9);
    gr.add_graph(5, 9);

    gr.dfs_recursive(1, is_visit);
    cout << '\n';
    vector<bool> is_visit2(100);
    gr.dfs_stk(1, is_visit2);
    vector<bool> is_visit3(100);
    gr.bfs(1, is_visit3);

    return 0;
}
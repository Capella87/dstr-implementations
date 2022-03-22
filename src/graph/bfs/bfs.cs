using System;
using System.Collections.Generic;

namespace Search
{
    public static class MainApp
    {
        private static List<List<int>> _arr;
        private static bool[] _isVisited;

        public static void AddEdge(int src, int dest)
        {
            _arr[src].Add(dest);
            _arr[dest].Add(src);
        }

        public static void BFS(int start)
        {
            var q = new Queue<int>();

            Console.Write("BFS: ");

            _isVisited[start] = true;
            q.Enqueue(start);

            while (q.Count > 0)
            {
                int v = q.Dequeue();
                Console.Write(v + " ");

                for (int i = 0; i < _arr[v].Count; i++)
                {
                    if (!_isVisited[_arr[v][i]])
                    {
                        _isVisited[_arr[v][i]] = true;
                        q.Enqueue(_arr[v][i]);
                    }
                }
            }
            Console.WriteLine();
        }

        public static void Main()
        {
            _arr = new List<List<int>>();
            for (int i = 0; i < 10; i++)
                _arr.Add(new List<int>());
            _isVisited = new bool[10];

            AddEdge(1, 2);
            AddEdge(1, 5);
            AddEdge(2, 3);
            AddEdge(3, 4);
            AddEdge(3, 5);
            AddEdge(3, 7);
            AddEdge(4, 5);
            AddEdge(5, 7);
            AddEdge(6, 7);
            AddEdge(7, 9);

            BFS(1);
        }
    }
}

/*
Output:
BFS: 1 2 5 3 4 7 6 9
*/
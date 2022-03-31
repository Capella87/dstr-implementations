using System;
using System.Collections.Generic;

namespace TSort
{
    public class CycleGraphException : Exception
    {
        public CycleGraphException()
        {
            Console.Write("Exception - CycleGraphException : ");
        }
    }

    public static class MainApp
    {
        private static List<List<int>> _digraph;
        private static List<int> _incoming;
        private static int _n;

        public static bool AddEdge(int src, int dest)
        {
            try
            {
                _digraph[src].Add(dest);
                _incoming[dest]++;
            }
            catch (ArgumentOutOfRangeException)
            {
                Console.WriteLine("One or more vertex number are out of range.");
                return false;
            }

            return true;
        }

        public static void TopologicalSort(out List<int> rt)
        {
            rt = new List<int>();
            var vert = new Queue<int>();

            for (int i = 0; i < _n; i++) // Enqueue nodes that does not have any incoming edges.
                if (_incoming[i] == 0)
                    vert.Enqueue(i);

            while (vert.Count > 0)
            {
                int v = vert.Dequeue();
                rt.Add(v);
                
                for (int i = 0; i < _digraph[v].Count; i++)
                    if (--_incoming[_digraph[v][i]] == 0) // Remove incoming edge and Add nodes which have no incoming edges.
                        vert.Enqueue(_digraph[v][i]);
            }
            if (rt.Count != _digraph.Count) throw new CycleGraphException(); // Throws an exception that the digraph has at least one cycle.
        }

        public static void Main()
        {
            _n = int.Parse(Console.ReadLine());
            _digraph = new List<List<int>>(new List<int>[_n]);
            for (int i = 0; i < _n; i++)
                _digraph[i] = new List<int>();
            _incoming = new List<int>(new int[_n]);

            while (true)
            {
                string[] input = Console.ReadLine().Split(' ');
                int src = int.Parse(input[0]);
                if (src == -1) break;

                int dest = int.Parse(input[1]);
                AddEdge(src, dest);
            }
            
            try
            {
                TopologicalSort(out List<int> result);
                Console.Write("Sorted vertices: ");
                foreach (var elements in result)
                    Console.Write($"{elements} ");
                Console.WriteLine();
            }
            catch (CycleGraphException)
            {
                Console.WriteLine("This digraph has at least one cycle.");
            }
        }
    }
}
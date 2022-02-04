using System;
using System.Collections.Generic;

namespace DisjointSet
{
    public class DisjointSet
    {
        private int _size;
        private List<int> _arr;


        public int Size { get {return _size;}}
        public DisjointSet()
        {
            _size = 0;
            _arr = new List<int>();
        }

        public DisjointSet(int size) : this()
        {
            _size = size;
            for (int i = 0; i < _size; i++)
                _arr.Add(-1);
        }

        public void Add(int count)
        {
            _size += count;
            for (int i = 0; i < count; i++)
                _arr.Add(-1);
        }

        public int Find(int target)
        {
            if (target >= _size) return -1;
            else if (_arr[target] < 0) return target;
            else return _arr[target] = Find(_arr[target]);
        }

        public bool UnionSet(int a, int b)
        {
            int aRoot = Find(a);
            int bRoot = Find(b);
            
            if (aRoot == -1 || bRoot == -1) return false;
            if (aRoot == bRoot) return false;
            
            if (_arr[bRoot] < _arr[aRoot])
                _arr[aRoot] = bRoot;
            else
            {
                if (_arr[aRoot] == _arr[bRoot]) _arr[aRoot]--;
                _arr[bRoot] = aRoot;
            }

            return true;
        }

        public void GetRoot(int num)
        {
            int result = Find(num);

            if (result == -1)
                Console.WriteLine($"Set {num}'s root is {result}");
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            int initSize = Convert.ToInt32(Console.ReadLine());

            DisjointSet djs = new DisjointSet(initSize);
            string[] input;
            while (true)
            {
                input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
                if (input[0].ToLower() == "exit") break;
                else if (input[0] == "union")
                    djs.UnionSet(Convert.ToInt32(input[1]), Convert.ToInt32(input[2]));
                else if (input[0] == "get")
                    djs.GetRoot(Convert.ToInt32(input[1]));
            }
            /*
            djs.UnionSet(1, 2);
            djs.UnionSet(1, 3);
            djs.UnionSet(1, 4);
            
            djs.GetRoot(4);
            djs.GetRoot(1);

            djs.UnionSet(5, 6);
            
            djs.GetRoot(6);
            
            djs.UnionSet(1, 5);

            djs.GetRoot(5);
            djs.GetRoot(1);
            */
        }
    }
}

/*
Input:
union 1 2
union 1 3
union 1 4
get 4
get 1
union 5 6
get 6
union 1 5
get 5
get 1
exit

Output:
Set 4's root is 1
Set 1's root is 1
Set 6's root is 5
Set 5's root is 1
Set 1's root is 1
*/
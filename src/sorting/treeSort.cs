using System;
using Sorting;

namespace TreeSort
{
    public class TreeSort<T> : Sorting<T> where T : IComparable<T>
    {
        public TreeSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public TreeSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
        }

        internal class Node
        {
            private T _data;

            public T Data { get { return _data; } }
            public Node? Left { get; set; }
            public Node? Right { get; set; }
            public int Count { get; set; }

            public Node(T val)
            {
                _data = val;
                Left = Right = null;
                Count = 0;
            }
        }

        private Node? InsertNode(Node? root, T val)
        {
            if (root == null)
            {
                root = new Node(val);
                return root;
            }

            if (val.CompareTo(root.Data) < 0)
                root.Left = InsertNode(root.Left, val);
            else if (val.CompareTo(root.Data) > 0)
                root.Right = InsertNode(root.Right, val);
            else root.Count++;

            return root;
        }

        private int Inorder(Node? root, int idx)
        {
            if (root == null) return idx;

            if (root.Left != null) idx = Inorder(root.Left, idx);
            _arr[idx++] = root.Data;
            if (root.Right != null) idx = Inorder(root.Right, idx);

            return idx;
        }

        public override void Sort()
        {
            Node? rt = null;
            foreach (var item in _arr)
                rt = InsertNode(rt, item);
            Inorder(rt, 0);
        }
    }

    public static class Program
    {
        public static void Main()
        {
            var a = new TreeSort<int>();
            a.PrintArray();
            a.Sort();
            a.PrintArray();
        }
    }
}
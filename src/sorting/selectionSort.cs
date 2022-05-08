using System;
using Sorting;

namespace SelectionSort
{
    public class SelectionSort<T> : Sorting<T> where T : IComparable<T>
    {
        public SelectionSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public SelectionSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
        }

        public override void Sort()
        {
            // Refresh minIdx when _arr[j] < _arr[minIdx]
            for (int i = 0; i < _count - 1; i++)
            {
                int minIdx = i;
                for (int j = i + 1; j < _count; j++)
                    if (_arr[j].CompareTo(_arr[minIdx]) < 0)
                        minIdx = j;
                if (minIdx != i) Swap(minIdx, i);
            }
        }
    }

    public static class Program
    {
        public static void Main()
        {
            var a = new SelectionSort<int>();
            a.PrintArray();
            a.Sort();
            a.PrintArray();
        }
    }
}

/*
Input:
5 4 3 2 1

Output:
5 4 3 2 1
1 2 3 4 5
*/
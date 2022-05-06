using System;
using Sorting;

namespace BubbleSort
{
    public class BubbleSort<T> : Sorting<T> where T : IComparable<T>
    {
        public BubbleSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public BubbleSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
        }

        public override void Sort()
        {
            for (int i = 0; i < _count - 1; i++)
            {
                for (int j = 0; j < _count - 1 - i; j++)
                    if (_arr[j].CompareTo(_arr[j + 1]) > 0) // _arr[j] is bigger than _arr[j + 1];
                        Swap(j, j + 1);
            }
        }
    }
    public static class Program
    {
        public static void Main()
        {
            var a = new BubbleSort<int>();
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
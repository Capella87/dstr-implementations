using System;
using Sorting;

namespace InsertionSort
{
    public class InsertionSort<T> : Sorting<T> where T : IComparable<T>
    {
        public InsertionSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public InsertionSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
        }

        public override void Sort()
        {
            for (int i = 1; i < _count; i++)
            {
                int idx = i - 1;
                T temp = _arr[i];
                // Move elements in array until the element is smaller than the temp.
                while (idx >= 0 && temp.CompareTo(_arr[idx]) < 0)
                {
                    _arr[idx + 1] = _arr[idx];
                    idx--;
                }
                _arr[idx + 1] = temp;
            }
        }
    }

    public static class Program
    {
        public static void Main()
        {
            var a = new InsertionSort<int>();
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
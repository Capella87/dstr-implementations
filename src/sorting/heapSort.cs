using System;
using Sorting;

namespace HeapSort
{
    public class HeapSort<T> : Sorting<T> where T : IComparable<T>
    {
        public HeapSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ', 
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public HeapSort(T[] input)
        {
            _arr = input;
            _count = input.Length;
        }

        private void Heapify(int size, int tIdx)
        {
            int largest = tIdx;
            int left = tIdx * 2 + 1;
            int right = tIdx * 2 + 2;

            if (left < size && _arr[left].CompareTo(_arr[largest]) > 0)
                largest = left;
            if (right < size && _arr[right].CompareTo(_arr[largest]) > 0)
                largest = right;

            if (largest != tIdx)
            {
                Swap(largest, tIdx);
                Heapify(size, largest);
            }
            return;
        }

        public override void Sort()
        {
            for (int i = _count / 2 - 1; i >= 0; i--)
                Heapify(_count, i);
            for (int i = _count - 1; i >= 0; i--)
            {
                Swap(0, i);
                Heapify(i, 0);
            }
        }
    }

    public static class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            var n = new HeapSort<int>();
            n.PrintArray();
            n.Sort();
            n.PrintArray();
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
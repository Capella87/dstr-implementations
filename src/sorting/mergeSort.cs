using System;
using Sorting;

namespace MergeSort
{
    public class MergeSort<T> : Sorting<T> where T : IComparable<T>
    {
        private T[] _buffer;

        public MergeSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
            _buffer = new T[_count];
        }

        public MergeSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
            _buffer = new T[_count];
        }

        private void MSort(int left, int right)
        {
            if (left >= right) return;

            int mid = (left + right) / 2;

            MSort(left, mid);
            MSort(mid + 1, right);

            int leftIdx = left, rightIdx = mid + 1;
            int bufIdx = left;

            while (leftIdx <= mid && rightIdx <= right)
            {
                if (_arr[leftIdx].CompareTo(_arr[rightIdx]) < 0) // _arr[rightIdx] is bigger than _arr[leftIdx]
                    _buffer[bufIdx++] = _arr[leftIdx++];
                else _buffer[bufIdx++] = _arr[rightIdx++];
            }
            while (leftIdx <= mid)
                _buffer[bufIdx++] = _arr[leftIdx++];
            while (rightIdx <= right)
                _buffer[bufIdx++] = _arr[rightIdx++];
            for (int i = left; i <= right; i++)
                _arr[i] = _buffer[i];

            return;
        }

        public override void Sort()
        {
            MSort(0, _count - 1);
        }
    }

    public class MainApp
    {
        public static void Main()
        {
            var a = new MergeSort<int>();
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
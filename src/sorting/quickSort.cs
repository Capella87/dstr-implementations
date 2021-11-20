using System;

namespace QuSort
{
    public class QuSort
    {
        private int[] _numArr;
        private int _arrSize;

        private void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        private int Partition(int left, int right)
        {
            int pivot = _numArr[left];
            int low = left + 1;
            int high = right;

            while (low <= high)
            {
                while (low <= right && pivot > _numArr[low])
                    low++;
                while (high > left && pivot < _numArr[high])
                    high--;
                if (low <= high) Swap(ref _numArr[low], ref _numArr[high]);
            }
            Swap(ref _numArr[left], ref _numArr[high]);
            return high;
        }

        public void QuickSort(int left, int right)
        {
            if (left > right) return;
            int pivotIdx = Partition(left, right);
            QuickSort(left, pivotIdx - 1);
            QuickSort(pivotIdx + 1, right);
        }

        public int GetSize()
        {
            return _arrSize;
        }

        public void PrintArray()
        {
            for (int i = 0; i < _arrSize; i++)
                Console.Write($"{_numArr[i]} ");
            Console.WriteLine();
        }

        public QuSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;
            _numArr = new int[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = int.Parse(input[i]);
        }
    }

    public class MainApp
    {
        public static void Main()
        {
            QuSort q = new();
            q.PrintArray();
            q.QuickSort(0, q.GetSize() - 1);
            q.PrintArray();
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
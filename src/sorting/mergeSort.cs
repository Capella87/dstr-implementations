using System;

namespace MSort
{
    public class MSort
    {
        private int[] _targetArr;
        private int[] _targetBuffer;
        private int _arrSize;

        public void MergeSort(int left, int right)
        {
            if (left >= right) return;
            int mid = (left + right) / 2;

            // Divide
            MergeSort(left, mid);
            MergeSort(mid + 1, right);

            // Conquer
            int i = left, j = mid + 1;
            var k = left;

            while (i <= mid && j <= right)
            {
                if (_targetArr[i] < _targetArr[j])
                    _targetBuffer[k++] = _targetArr[i++];
                else _targetBuffer[k++] = _targetArr[j++];
            }
            while (i <= mid)
                _targetBuffer[k++] = _targetArr[i++];
            while (j <= right)
                _targetBuffer[k++] = _targetArr[j++];
            for (var l = left; l <= right; l++)
                _targetArr[l] = _targetBuffer[l];
            return;
        }

        public void PrintArray()
        {
            for (var i = 0; i < this._arrSize; i++)
                Console.Write($"{_targetArr[i]} ");
            Console.WriteLine();
        }

        public int GetSize()
        {
            return _arrSize;
        }

        public MSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            this._arrSize = input.Length; // input count
            this._targetArr = new int[this._arrSize];
            this._targetBuffer = new int[this._arrSize];
            for (var i = 0; i < this._arrSize; i++)
                _targetArr[i] = Convert.ToInt32(input[i]);
        }
    }

    public class MainApp
    {
        public static void Main()
        {
            MSort m = new();
            m.PrintArray();
            m.MergeSort(0, m.GetSize() - 1);
            m.PrintArray();
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
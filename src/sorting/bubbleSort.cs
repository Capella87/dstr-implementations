using System;

namespace BSort
{
    public class BSort
    {
        private int[] _numArr;
        private int _arrSize;

        public BSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;

            _numArr = new int[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = Convert.ToInt32(input[i]);
        }

        private void Swap(int idx1, int idx2)
        {
            int temp = _numArr[idx1];
            _numArr[idx1] = _numArr[idx2];
            _numArr[idx2] = temp;
        }

        public void bubbleSort()
        {
            for (int i = 0; i < _arrSize - 1; i++)
                for (int j = 0; j < _arrSize - 1 - i; j++)
                    if (_numArr[j] > _numArr[j + 1])
                        Swap(j, j + 1);
        }

        public void PrintArray()
        {
            foreach (int i in _numArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            BSort b = new();
            b.PrintArray();
            b.bubbleSort();
            b.PrintArray();
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
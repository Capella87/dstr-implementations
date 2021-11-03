using System;

namespace ISort
{
    public class ISort
    {
        private int[] _numArr;
        private int _arrSize;

        public ISort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;
            _numArr = new int[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = int.Parse(input[i]);
        }

        public void InsertionSort()
        {
            for (int i = 1; i < _arrSize; i++)
            {
                int temp = _numArr[i];
                int j = i - 1;
                for (; j >= 0 && _numArr[j] > temp; j--)
                    _numArr[j + 1] = _numArr[j];
                _numArr[j + 1] = temp;
            }
        }

        public void PrintArr()
        {
            foreach (int t in _numArr)
                Console.Write($"{t} ");
            Console.WriteLine();
        }

    }

    public class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            ISort n = new();
            n.PrintArr();
            n.InsertionSort();
            n.PrintArr();
        }
    }
}
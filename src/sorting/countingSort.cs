using System;

namespace CSort
{
    public class CSort
    {
        private int[] _numBoard;
        private int[] _numArr;
        private int _arrSize;

        public CSort()
        {
            _numBoard = new int[1000001];
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;
            _numArr = new int[_arrSize];

            for (int i = 0; i < _arrSize; i++)
            {
                _numArr[i] = int.Parse(input[i]);
                _numBoard[Math.Abs(_numArr[i])]++;
            }
        }

        public void PrintArray()
        {
            foreach (int i in _numArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }

        public void CountingSort()
        {
            for (int i = 0; i < 1000001; i++)
                for (int j = 0; j < _numBoard[i]; j++)
                    Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            CSort c = new();
            c.PrintArray();
            c.CountingSort();
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
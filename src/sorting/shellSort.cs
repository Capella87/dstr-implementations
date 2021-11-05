using System;

namespace Shell
{
    public class Shell
    {
        private int[] _numArr;
        private int _arrSize;

        public Shell()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;
            _numArr = new int[_arrSize];
            for (int i = 0; i < _numArr.Length; i++)
                _numArr[i] = int.Parse(input[i]);
        }

        public void ShellSort()
        {
            for (int interval = _arrSize / 2; interval > 0; interval /= 2)
            {
                for (int i = interval; i < _arrSize; i++)
                {
                    int temp = _numArr[i];
                    int j;
                    for (j = i; j >= interval && _numArr[j - interval] > temp; j -= interval)
                        _numArr[j] = _numArr[j - interval];
                    _numArr[j] = temp;
                }
            }
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
            Shell n = new();
            n.PrintArray();
            n.ShellSort();
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
using System;

namespace shell
{
    public class Sort
    {
        private int[] numArr;
        private int arrSize;

        public Sort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            arrSize = input.Length;
            numArr = new int[arrSize];
            for (int i = 0; i < numArr.Length; i++)
                numArr[i] = int.Parse(input[i]);
        }

        public void ShellSort()
        {
            for (int interval = arrSize / 2; interval > 0; interval /= 2)
            {
                for (int i = interval; i < arrSize; i++)
                {
                    int temp = numArr[i];
                    int j;
                    for (j = i; j >= interval && numArr[j - interval] > temp; j -= interval)
                        numArr[j] = numArr[j - interval];
                    numArr[j] = temp;
                }
            }
        }

        public void PrintArray()
        {
            foreach (int i in numArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Sort n = new();
            n.PrintArray();
            n.ShellSort();
            n.PrintArray();
        }
    }
}
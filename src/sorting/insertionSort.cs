using System;

namespace insertion
{
    public class ISort
    {
        private int[] numArr;
        private int numSize;

        public ISort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            numSize = input.Length;
            numArr = new int[numSize];
            for (int i = 0; i < numSize; i++)
                numArr[i] = int.Parse(input[i]);
        }

        public void InsertionSort()
        {
            for (int i = 1; i < numSize; i++)
            {
                int temp = numArr[i];
                int j = i - 1;
                for (; j >= 0 && numArr[j] > temp; j--)
                    numArr[j + 1] = numArr[j];
                numArr[j + 1] = temp;
            }
        }

        public void PrintArr()
        {
            foreach (int t in numArr)
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
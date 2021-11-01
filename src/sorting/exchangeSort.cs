using System;

namespace exchange
{
    public class ESort
    {
        private int[] NumArr;
        private int ArrSize;

        private void Swap(int idx1, int idx2)
        {
            int temp = NumArr[idx1];
            NumArr[idx1] = NumArr[idx2];
            NumArr[idx2] = temp;
        }

        public ESort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            ArrSize = input.Length;
            NumArr = new int[ArrSize];
            for (int i = 0; i < ArrSize; i++)
                NumArr[i] = int.Parse(input[i]);
        }

        public void ExchangeSort()
        {
            for (int i = 0; i < ArrSize - 1; i++)
                for (int j = i + 1; j < ArrSize; j++)
                    if (NumArr[i] > NumArr[j]) Swap(i, j);
        }

        public void PrintArray()
        {
            foreach (int i in NumArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public class Program
    {
        public static void Main()
        {
            ESort e = new();
            e.PrintArray();
            e.ExchangeSort();
            e.PrintArray();
        }
    }
}
using System;

namespace bubble
{
    public class BSort
    {
        private int[] numArr;
        private int arrSize;

        public BSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            arrSize = input.Length;

            numArr = new int[arrSize];
            for (int i = 0; i < arrSize; i++)
                numArr[i] = Convert.ToInt32(input[i]);
        }

        private void Swap(int idx1, int idx2)
        {
            int temp = numArr[idx1];
            numArr[idx1] = numArr[idx2];
            numArr[idx2] = temp;
        }

        public void bubbleSort()
        {
            for (int i = 0; i < arrSize - 1; i++)
                for (int j = 0; j < arrSize - 1 - i; j++)
                    if (numArr[j] > numArr[j + 1])
                        Swap(j, j + 1);
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
            BSort b = new();
            b.PrintArray();
            b.bubbleSort();
            b.PrintArray();
        }
    }
}
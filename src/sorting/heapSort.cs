using System;

namespace heap
{
    public class HSort
    {
        private int[] numArr;
        private int arrSize;
        
        public HSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);

            arrSize = input.Length;
            numArr = new int[arrSize];
            for (int i = 0; i < arrSize; i++)
                numArr[i] = Convert.ToInt32(input[i]);
        }

        private void Swap(int dest, int src)
        {
            int temp = numArr[dest];
            numArr[dest] = numArr[src];
            numArr[src] = temp;
        }

        private void Heapify(int size, int t_idx)
        {
            int largest = t_idx;
            int left = t_idx * 2 + 1;
            int right = t_idx * 2 + 2;

            if (left < size && numArr[left] > numArr[largest])
                largest = left;
            if (right < size && numArr[right] > numArr[largest])
                largest = right;
            if (t_idx != largest)
            {
                Swap(t_idx, largest);
                Heapify(size, largest);
            }
            return;
        }

        public void HeapSort()
        {
            for (int i = arrSize / 2 - 1; i >= 0; i--)
                Heapify(arrSize, i);
            for (int i = arrSize - 1; i >= 0; i--)
            {
                Swap(0, i);
                Heapify(i, 0);
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
            HSort n = new();
            n.PrintArray();
            n.HeapSort();
            n.PrintArray();
        }
    }
}
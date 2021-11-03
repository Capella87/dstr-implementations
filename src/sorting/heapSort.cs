using System;

namespace HSort
{
    public class HSort
    {
        private int[] _numArr;
        private int _arrSize;
        
        public HSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);

            _arrSize = input.Length;
            _numArr = new int[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = Convert.ToInt32(input[i]);
        }

        private void Swap(int dest, int src)
        {
            int temp = _numArr[dest];
            _numArr[dest] = _numArr[src];
            _numArr[src] = temp;
        }

        private void Heapify(int size, int tIdx)
        {
            int largest = tIdx;
            int left = tIdx * 2 + 1;
            int right = tIdx * 2 + 2;

            if (left < size && _numArr[left] > _numArr[largest])
                largest = left;
            if (right < size && _numArr[right] > _numArr[largest])
                largest = right;
            if (tIdx != largest)
            {
                Swap(tIdx, largest);
                Heapify(size, largest);
            }
            return;
        }

        public void HeapSort()
        {
            for (int i = _arrSize / 2 - 1; i >= 0; i--)
                Heapify(_arrSize, i);
            for (int i = _arrSize - 1; i >= 0; i--)
            {
                Swap(0, i);
                Heapify(i, 0);
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
            HSort n = new();
            n.PrintArray();
            n.HeapSort();
            n.PrintArray();
        }
    }
}
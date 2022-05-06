using System;

namespace HSort
{
    public class HSort<T> where T : IComparable<T>
    {
        private T[] _numArr;
        private int _arrSize;

        public HSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);

            _arrSize = input.Length;
            _numArr = new T[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = ParseType(input[i]);
        }

        private static T ParseType(object target)
        {
            return (T)Convert.ChangeType(target, typeof(T));
        }

        private void Swap(int dest, int src)
        {
            T temp = _numArr[dest];
            _numArr[dest] = _numArr[src];
            _numArr[src] = temp;
        }

        private void Heapify(int size, int tIdx)
        {
            int largest = tIdx;
            int left = tIdx * 2 + 1;
            int right = tIdx * 2 + 2;

            if (left < size && _numArr[left].CompareTo(_numArr[largest]) > 0)
                largest = left;
            if (right < size && _numArr[right].CompareTo(_numArr[largest]) > 0)
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
            foreach (var i in _numArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public static class Program
    {
        static void Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            var n = new HSort<int>();
            n.PrintArray();
            n.HeapSort();
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
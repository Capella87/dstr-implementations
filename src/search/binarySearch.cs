using System;

namespace BSearch
{
    public class BSearch
    {
        private int[] _numArr;
        private int _arrSize;

        public int BinarySearch(int target) // Non-recursive binary search
        {
            int left = 0, right = this._arrSize - 1;
            int idx = -1;
            
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (_numArr[mid] == target)
                {
                    idx = mid;
                    break;
                }
                else if (target < _numArr[mid])
                    right = mid - 1;
                else left = mid + 1;
            }
            return idx;
        }

        public BSearch()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            this._numArr = new int[input.Length];
            this._arrSize = input.Length;
            for (var i = 0; i < this._arrSize; i++)
                _numArr[i] = Convert.ToInt32(input[i]);
            Array.Sort(this._numArr);
        }
    }

    public class Program
    {
        static void Main()
        {
            BSearch a = new();
            Console.WriteLine(a.BinarySearch(Convert.ToInt32(Console.ReadLine())));
        }
    }
}
    /*
        BinarySearch method returns -1 if the target is not exist in the array.
        Otherwise, it returns the index of target in array.
    */

    /*
        Input:
        5 4 3 2 1
        123
        Output:
        -1
    */
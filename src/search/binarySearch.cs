using System;

namespace bsearch
{
    public class BSearch
    {
        private int[] numArr;
        private int arrSize;

        public int BinarySearch(int target) // Non-recursive
        {
            int left = 0, right = this.arrSize - 1;
            int idx = -1;
            
            while (left <= right)
            {
                int mid = (left + right) / 2;
                if (numArr[mid] == target)
                {
                    idx = mid;
                    break;
                }
                else if (target < numArr[mid])
                    right = mid - 1;
                else left = mid + 1;
            }
            return idx;
        }

        public BSearch()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            this.numArr = new int[input.Length];
            this.arrSize = input.Length;
            for (var i = 0; i < this.arrSize; i++)
                numArr[i] = Convert.ToInt32(input[i]);
            Array.Sort(this.numArr);
        }
    }

    public class Program
    {
        static void Main()
        {
            BSearch a = new BSearch();
            Console.WriteLine(a.BinarySearch(Convert.ToInt32(Console.ReadLine())));
        }
    }

    /*
        BinarySearch method returns -1 if the target is not exist in the array.
        Otherwise, it returns the index of target in array.
    */

    /*
        input:
        5 4 3 2 1
        123
        output:
        -1
    */
}
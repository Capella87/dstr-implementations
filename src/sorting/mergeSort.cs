using System;

namespace sort
{
    public class MSort
    {
        private int[] targetArr;
        private int[] targetBuffer;
        public int arrSize;

        public void MergeSort(int left, int right)
        {
            if (left >= right) return;
            int mid = (left + right) / 2;

            // Divide
            MergeSort(left, mid);
            MergeSort(mid + 1, right);

            // Conquer
            int i = left, j = mid + 1;
            var k = left;

            while (i <= mid && j <= right)
            {
                if (targetArr[i] < targetArr[j])
                    targetBuffer[k++] = targetArr[i++];
                else targetBuffer[k++] = targetArr[j++];
            }
            while (i <= mid)
                targetBuffer[k++] = targetArr[i++];
            while (j <= right)
                targetBuffer[k++] = targetArr[j++];
            for (var l = left; l <= right; l++)
                targetArr[l] = targetBuffer[l];
            return;
        }

        public void PrintArr()
        {
            for (var i = 0; i < this.arrSize; i++)
                Console.Write($"{targetArr[i]} ");
            Console.WriteLine();
        }

        public MSort()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            this.arrSize = input.Length; // input count
            this.targetArr = new int[this.arrSize];
            this.targetBuffer = new int[this.arrSize];
            for (var i = 0; i < this.arrSize; i++)
                targetArr[i] = Convert.ToInt32(input[i]);
        }
        
        public static void Main() // Driver code
        {
            MSort t = new MSort();
            Console.Write("Before: ");
            t.PrintArr();
            t.MergeSort(0, t.arrSize - 1);
            Console.Write("After:  ");
            t.PrintArr();
        }
    }
}

/*
input:
5 4 3 2 1

output:
Before : 5 4 3 2 1
After  : 1 2 3 4 5
*/
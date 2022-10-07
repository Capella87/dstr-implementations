using Sorting;

namespace QuSort
{
    public class QuickSort<T> : Sorting<T> where T : IComparable<T>
    {
        public QuickSort()
        {
            _arr = Array.ConvertAll<string, T>(Console.ReadLine().Split(' ',
            StringSplitOptions.RemoveEmptyEntries), ParseType);
            _count = _arr.Length;
        }

        public QuickSort(T[] input)
        {
            _arr = input;
            _count = _arr.Length;
        }

        private int GetPivot(int left, int right)
        {
            var rand = new Random();

            return rand.Next(left, right + 1);
        }

        private int Partition(int left, int right, int pivotIdx)
        {
            if (pivotIdx != right) Swap(pivotIdx, right);

            ref T pivot = ref _arr[right];
            int i = left, j = right - 1;

            while (i <= j)
            {
                while (i <= j && pivot.CompareTo(_arr[i]) >= 0)
                    i++;
                while (i <= j && pivot.CompareTo(_arr[j]) <= 0)
                    j--;
                if (i < j) Swap(i, j);
            }
            Swap(right, i);

            return i;
        }

        private void QuSort(int left, int right)
        {
            if (left >= right) return;

            int pivotIdx = GetPivot(left, right);

            pivotIdx = Partition(left, right, pivotIdx);
            QuSort(left, pivotIdx - 1);
            QuSort(pivotIdx + 1, right);
        }

        public override void Sort()
        {
            QuSort(0, _count - 1);
        }
    }

    public static class Program
    {
        public static void Main()
        {
            var a = new QuickSort<int>();
            a.PrintArray();
            a.Sort();
            a.PrintArray();
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
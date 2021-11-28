using System;

namespace Cocktail
{
    public class CocktailShaker
    {
        private int[] _numArr;
        private int _arrSize;

        public CocktailShaker()
        {
            string[] input = Console.ReadLine().Split(' ', StringSplitOptions.RemoveEmptyEntries);
            _arrSize = input.Length;
            _numArr = new int[_arrSize];
            for (int i = 0; i < _arrSize; i++)
                _numArr[i] = Convert.ToInt32(input[i]);
        }

        private void Swap(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        public void CocktailShakerSort()
        {
            bool isSwapped = false;
            int size = _arrSize / 2;
            
            for (int i = 0; i < size; i++)
            {
                for (int j = i; j < _arrSize - i - 1; j++)
                {
                    if (_numArr[j] > _numArr[j + 1])
                    {
                        Swap(ref _numArr[j], ref _numArr[j + 1]);
                        isSwapped = true;
                    }
                }
                for (int j = _arrSize - i - 2; j > i; j--)
                {
                    if (_numArr[j - 1] > _numArr[j])
                    {
                        Swap(ref _numArr[j - 1], ref _numArr[j]);
                        isSwapped = true;
                    }
                }
                if (!isSwapped) break;
            }

        }

        public void PrintArray()
        {
            foreach(int i in _numArr)
                Console.Write($"{i} ");
            Console.WriteLine();
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            CocktailShaker s = new();
            s.PrintArray();
            s.CocktailShakerSort();
            s.PrintArray();
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
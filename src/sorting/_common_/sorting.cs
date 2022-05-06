using System;

namespace Sorting
{
    public abstract class Sorting<T> where T : IComparable<T>
    {
        protected T[] _arr;
        protected int _count;

        protected static T ParseType(object target)
        {
            return (T)Convert.ChangeType(target, typeof(T));
        }

        protected void Swap(int idx1, int idx2)
        {
            T temp = _arr[idx1];
            _arr[idx1] = _arr[idx2];
            _arr[idx2] = temp;
        }

        public T this[long idx]
        {
            get
            {
                try
                {
                    return _arr[idx];
                }
                catch (IndexOutOfRangeException e)
                {
                    Console.WriteLine("Index error : Out of range!");
                    Console.Write(e.StackTrace);
                    return default(T);
                }
            }
        }

        public void PrintArray()
        {
            foreach (var e in _arr)
                Console.Write($"{e} ");
            Console.WriteLine();
        }

        public abstract void Sort();
    }
}
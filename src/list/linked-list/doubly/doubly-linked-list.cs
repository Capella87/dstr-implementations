using System;

namespace Doubly
{
    public class DoublyList<T> where T : IComparable<T>
    {
        internal class Node
        {
            internal T? _data;
            internal Node? _prev;
            internal Node? _next;

            /// <summary>
            /// Constructor
            /// </summary>
            public Node()
            {
                _data = default;
                _prev = null;
                _next = null;
            }

            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="data">A value to be inserted in the node.</param>
            public Node(T data) : this()
            {
                this._data = data;
            }
        }

        private Node _head;
        private Node _tail;
        private int _size;

        public int Size { get => _size; }

        /// <summary>
        /// Constructor
        /// </summary>
        public DoublyList()
        {
            _head = new Node();
            _tail = new Node();
            _head._next = _tail;
            _tail._prev = _head;
            _size = 0;
        }

        /// <summary>
        /// Insert an element behind _head.
        /// </summary>
        /// <param name="d">A value to be inserted.</param>
        /// <returns>Returns true if d is inserted successfully.</returns>
        public bool InsertFront(T d)
        {
            var newNode = new Node(d);

            newNode._next = _head._next;
            newNode._prev = _head;
            _head._next._prev = newNode;
            _head._next = newNode;
            _size++;

            return true;
        }

        /// <summary>
        /// Insert an element in front of _tail.
        /// </summary>
        /// <param name="d">A value to be appended.</param>
        /// <returns>Returns true if d is appended successfully.</returns>
        public bool Append(T d)
        {
            var newNode = new Node(d);

            newNode._next = _tail;
            newNode._prev = _tail._prev;
            _tail._prev._next = newNode;
            _tail._prev = newNode;
            _size++;

            return true;
        }

        /// <summary>
        /// Insert an element before the target. Find the target first and insert.
        /// </summary>
        /// <param name="d">A value to be inserted.</param>
        /// <param name="n">A target value.</param>
        /// <returns>Returns true if d is inserted successfully.</returns>
        public bool Insert(T d, T n)
        {
            Node? t = SearchNode(n);
            if (t == null) return false;

            var newNode = new Node(d);
            newNode._next = t;
            newNode._prev = t._prev;
            t._prev._next = newNode;
            t._prev = newNode;
            _size++;

            return true;
        }

        /// <summary>
        /// Traverse from _head to _tail.
        /// </summary>
        /// <returns>Returns false if the list is empty.</returns>
        public bool FrontTraverse()
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return false;
            }
            Node? cur = _head._next;
            while (cur != null && cur != _tail)
            {
                Console.Write($"{cur._data} ");
                cur = cur._next;
            }
            Console.WriteLine();

            return true;
        }

        /// <summary>
        /// Traverse from _head to _tail.
        /// </summary>
        /// <returns>Returns false if the list is empty.</returns>
        public bool BackTraverse()
        {
            if (_size == 0)
            {
                Console.WriteLine("No Entries");
                return false;
            }
            Node? cur = _tail._prev;
            while (cur != null && cur != _head)
            {
                Console.Write($"{cur._data} ");
                cur = cur._prev;
            }
            Console.WriteLine();

            return true;
        }

        /// <summary>
        /// Remove the first element from the list.
        /// </summary>
        /// <returns>Returns false if the list is empty.</returns>
        public bool RemoveFront()
        {
            if (_size == 0)
            {
                Console.WriteLine("No Entries");
                return false;
            }

            Node? cur = _head._next;
            if (cur != null)
            {
                _head._next = cur._next;
                cur._next._prev = _head;
                _size--;

                return true;
            }

            return false;
        }

        /// <summary>
        /// Remove the last element from the list.
        /// </summary>
        /// <returns>Returns false if the list is empty.</returns>
        public bool RemoveLast()
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return false;
            }

            Node? cur = _tail._prev;
            if (cur != null)
            {
                _tail._prev = cur._prev;
                cur._prev._next = _tail;
                _size--;

                return true;
            }

            return false;
        }

        /// <summary>
        /// Find the first element of target and get rid of it from the list. O(n) time complexity.
        /// </summary>
        /// <param name="target">A target value to be removed.</param>
        /// <returns>Returns false if the target is not in the list or the list is empty.</returns>
        public bool Remove(T target)
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return false;
            }

            Node? cur = SearchNode(target);
            if (cur != null)
            {
                cur._next._prev = cur._prev;
                cur._prev._next = cur._next;
                _size--;
                return true;
            }

            return false;
        }

        /// <summary>
        /// Search a target from the first to the last. O(n) time complexity.
        /// </summary>
        /// <param name="target"></param>
        /// <returns>Returns null if the list is empty or the target is not in the list.</returns>
        private Node? SearchNode(T target)
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return null;
            }

            Node? cur = _head._next;
            while (cur != null && cur != _tail)
            {
                if (cur._data != null && cur._data.Equals(target))
                    return cur;
                cur = cur._next;
            }

            return null;
        }

        /// <summary>
        /// Search a target from the last to the first. O(n) time complexity.
        /// </summary>
        /// <param name="target">A target value to be found.</param>
        /// <returns>Returns false if the list is empty or the target is not in the list.</returns>
        private Node? SearchNodeLast(T target)
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return null;
            }

            Node? cur = _tail._prev;
            while (cur != null && cur != _head)
            {
                if (cur._data != null && cur._data.Equals(target))
                    return cur;
                cur = cur._prev;
            }

            return null;
        }

        /// <summary>
        /// Find a target and show a result.
        /// </summary>
        /// <param name="target">A target value to be found.</param>
        /// <returns>Returns true if the target is in the list.</returns>
        public bool Find(T target)
        {
            Node? hasQuery = SearchNode(target);
            if (hasQuery != null)
            {
                Console.WriteLine($"{target} is exist in the list.");
                return true;
            }
            else
            {
                Console.WriteLine($"{target} is NOT exist in the list.");
                return false;
            }
        }

        /// <summary>
        /// Find the target and show a result. Traverse from the last element.
        /// </summary>
        /// <param name="target">A target value to be found.</param>
        /// <returns>Returns true if the target is in the list.</returns>
        public bool FindLast(T target)
        {
            Node? hasQuery = SearchNodeLast(target);
            if (hasQuery != null)
            {
                Console.WriteLine($"{target} is exist in the list.");
                return true;
            }
            else
            {
                Console.WriteLine($"{target} is NOT exist in the list.");
                return false;
            }
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            var dl = new DoublyList<int>();

            dl.InsertFront(1);
            dl.InsertFront(2);
            dl.InsertFront(3);
            dl.InsertFront(4);
            dl.Insert(123, 3);
            dl.Append(5);
            dl.Append(6);
            dl.Append(7);
            dl.Append(8);
            dl.Append(1);

            Console.Write("Front: ");
            dl.FrontTraverse();

            Console.Write("Back: ");
            dl.BackTraverse();

            // Remove some elements from the list and traverse elements.
            dl.RemoveFront();
            dl.RemoveFront();
            dl.FrontTraverse();
            dl.RemoveLast();
            dl.RemoveLast();
            dl.FrontTraverse();

            Console.WriteLine($"There are {dl.Size} entries in the list.");

            // Search 1 and 4.
            dl.Find(1);
            dl.Find(4);
            dl.FindLast(1);

            // Remove 1 from the list.
            dl.Remove(1);
            dl.FrontTraverse();
        }
    }
}

/*
Output:
Front: 4 123 3 2 1 5 6 7 8 1 
Back: 1 8 7 6 5 1 2 3 123 4 
3 2 1 5 6 7 8 1 
3 2 1 5 6 7 
There are 6 entries in the list.
1 is exist in the list.
4 is NOT exist in the list.
1 is exist in the list.
3 2 5 6 7
*/
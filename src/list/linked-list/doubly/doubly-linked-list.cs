using System;

namespace Doubly
{
    public class DoublyList
    {
        internal class Node
        {
            internal int? _data;
            internal Node? _prev;
            internal Node? _next;

            public Node()
            {
                _data = null;
                _prev = null;
                _next = null;
            }

            public Node(int data) : this()
            {
                this._data = data;
            }
        }

        private Node _head;
        private Node _tail;
        private int _size;

        public int size { get => _size; }

        public DoublyList()
        {
            _head = new Node();
            _tail = new Node();
            _head._next = _tail;
            _tail._prev = _head;
            _size = 0;
        }

        // Insert an element behind _head.
        public bool InsertFront(int d)
        {
            var newNode = new Node(d);

            newNode._next = _head._next;
            newNode._prev = _head;
            _head._next._prev = newNode;
            _head._next = newNode;
            _size++;

            return true;
        }

        // Insert an element in front of _tail.
        public bool Append(int d)
        {
            var newNode = new Node(d);

            newNode._next = _tail;
            newNode._prev = _tail._prev;
            _tail._prev._next = newNode;
            _tail._prev = newNode;
            _size++;

            return true;
        }

        // Insert an element before the target. Find the target first and insert.
        public bool Insert(int d, int n)
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

        // Traverse from _head to _tail. Returns false if the list is empty.
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

        // Traverse from _head to _tail. Returns false if the list is vacant.
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

        // Remove the first element from the list.
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

        // Remove the last element from the list.
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

        // Find the first element of target and get rid of it from the list. Takes O(n)
        public bool Remove(int target)
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

        // Search a query from the first to the last. O(n)
        private Node? SearchNode(int query)
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return null;
            }

            Node? cur = _head._next;
            while (cur != null && cur != _tail)
            {
                if (cur != null && cur._data == query)
                    return cur;
                cur = cur._next;
            }

            return null;
        }

        // Search a query from the last to the first. O(n)
        private Node? SearchNodeLast(int query)
        {
            if (_size == 0)
            {
                Console.WriteLine("No entries");
                return null;
            }

            Node? cur = _tail._prev;
            while (cur != null && cur != _head)
            {
                if (cur != null && cur._data == query)
                    return cur;
                cur = cur._prev;
            }

            return null;
        }

        // Find the query and show a result.
        public bool Find(int query)
        {
            Node? hasQuery = SearchNode(query);
            if (hasQuery != null)
            {
                Console.WriteLine($"{query} is exist in the list.");
                return true;
            }
            else
            {
                Console.WriteLine($"{query} is NOT exist in the list.");
                return false;
            }
        }

        // Find the query and show a result. Traverse from the last.
        public bool FindLast(int query)
        {
            Node? hasQuery = SearchNodeLast(query);
            if (hasQuery != null)
            {
                Console.WriteLine($"{query} is exist in the list.");
                return true;
            }
            else
            {
                Console.WriteLine($"{query} is NOT exist in the list.");
                return false;
            }
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            DoublyList dl = new DoublyList();

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

            Console.WriteLine($"There are {dl.size} entries in the list.");

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
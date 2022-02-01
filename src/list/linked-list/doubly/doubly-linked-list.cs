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

        public bool InsertFront(int d) // Insert an element behind _head.
        {
            var newNode = new Node(d);

            newNode._next = _head._next;
            newNode._prev = _head;
            _head._next._prev = newNode;
            _head._next = newNode;
            _size++;

            return true;
        }

        public bool Append(int d) // Insert an element in front of _tail.
        {
            var newNode = new Node(d);

            newNode._next = _tail;
            newNode._prev = _tail._prev;
            _tail._prev._next = newNode;
            _tail._prev = newNode;
            _size++;

            return true;
        }

        public bool Insert(int d, int n) // Insert an element before the target. Find the target first and insert.
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

        public bool FrontTraverse() // Traverse from _head to _tail. Returns false if the list is empty.
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

        public bool BackTraverse() // Traverse from _head to _tail. Returns false if the list is vacant.
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
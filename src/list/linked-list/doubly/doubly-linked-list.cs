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

            public Node(in int data) : this()
            {
                this._data = data;
            }
        }

        private Node _head;
        private Node _tail;
        private int _size;

        public int size
        {
            get { return _size; }
        }

        public DoublyList()
        {
            _head = new Node();
            _tail = new Node();
            _head._next = _tail;
            _tail._prev = _head;
            _size = 0;
        }

        public bool InsertFirst(in int d) // Insert an element behind _head.
        {
            var newNode = new Node(d);

            newNode._next = _head._next;
            newNode._prev = _head;
            _head._next._prev = newNode;
            _head._next = newNode;
            _size++;

            return true;
        }

        public bool InsertLast(in int d) // Insert an element in front of _tail.
        {
            var newNode = new Node(d);

            newNode._next = _tail;
            newNode._prev = _tail._prev;
            _tail._prev._next = newNode;
            _tail._prev = newNode;
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

        public bool RemoveFirst()
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

        private Node? SearchNode(in int query)
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

        public bool RemoveQuery(in int query)
        {
            Node? hasQuery = SearchNode(in query);
            if (hasQuery != null)
            {
                // Remove
                hasQuery._next._prev = hasQuery._prev;
                hasQuery._prev._next = hasQuery._next;
                _size--;

                Console.WriteLine($"Remove element {query} from the list successfully.");
                return true;
            }
            else
            {
                Console.WriteLine($"{query} is NOT exist in the list.");
                return false;
            }
        }

        public bool SearchQuery(in int query)
        {
            Node? hasQuery = SearchNode(in query);
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

            dl.InsertFirst(1);
            dl.InsertFirst(2);
            dl.InsertFirst(3);
            dl.InsertFirst(4);
            dl.InsertLast(5);
            dl.InsertLast(6);
            dl.InsertLast(7);
            dl.InsertLast(8);

            Console.Write("Front: ");
            dl.FrontTraverse();

            Console.Write("Back: ");
            dl.BackTraverse();

            // Remove some elements from the list and traverse elements.
            dl.RemoveFirst();
            dl.RemoveFirst();
            dl.FrontTraverse();
            dl.RemoveLast();
            dl.RemoveLast();
            dl.FrontTraverse();

            Console.WriteLine($"There are {dl.size} entries in the list.");

            // Search 1 and 4.
            dl.SearchQuery(1);
            dl.SearchQuery(4);

            // Remove 1 from the list.
            dl.RemoveQuery(1);
            dl.FrontTraverse();
        }
    }
}
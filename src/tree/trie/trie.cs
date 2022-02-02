using System;
using System.Collections.Generic;

namespace Trie
{
    public class Trie
    {
        internal class Node
        {
            internal bool _isLeaf;
            internal Dictionary<char, Node?> _children; // Saves children


            internal Node()
            {
                _isLeaf = false;
                _children = new Dictionary<char, Node?>();
            }
        }

        private Node? _root;

        public Trie()
        {
            _root = new Node();
        }

        // Returns true if str is added or discovered successfully.
        public bool Add(string str)
        {
            int idx = 0;
            Node? cur = _root;

            while (idx < str.Length && cur != null)
            {
                if (!cur._children.ContainsKey(str[idx])) // No targeted character in the dictionary, Add it.
                    cur._children.Add(str[idx], new Node());
                cur = cur._children[str[idx]]; // Go to the child.
                idx++;
            }

            if (cur != null) // Prevent NULL dereferencing.
            {
                cur._isLeaf = true;
                return true;
            }

            return false;
        }

        // Returns true if str is discovered.
        public bool Search(string str)
        {
            int idx = 0;
            Node? cur = _root;

            while (idx < str.Length && cur != null)
            {
                if (!cur._children.ContainsKey(str[idx]))
                    return false;
                cur = cur._children[str[idx]];
                idx++;
            }

            return cur == null ? false : cur._isLeaf;
        }

        //Delete str from the trie.
        private Node? Deletion(ref Node? cur, string str, int idx)
        {
            if (cur == null) return null;

            // Reached at the end of string str.
            if (idx == str.Length)
            {
                if (cur._isLeaf) cur._isLeaf = false;
                if (cur._children.Count == 0)
                    cur = null;

                return cur;
            }

            // Get child node to be targeted, if the child node is NOT in the list, return raw cur and exit the recursion;
            if (!cur._children.TryGetValue(str[idx], out Node? cur2)) return cur;

            cur._children[str[idx]] = Deletion(ref cur2, str, idx + 1);
            if (cur._children.Count > 0 && cur._children[str[idx]] == null) // Regarded to be deleted node, Pop out it from the dictionary.
                cur._children.Remove(str[idx]);

            if (cur._children.Count == 0 && !cur._isLeaf) // If there's no child, It will be deleted. (In C#, We do NOT use any deallocation code);
                cur = null;

            return cur;
        }


        // Deletion function for public scope.
        public void Detrie(string str)
        {
            _root = Deletion(ref _root, str, 0);
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            var tri = new Trie();
            tri.Add("qwerjklfjelwk");
            tri.Add("python");
            tri.Add("pypy");

            Console.WriteLine("pypy is " + (tri.Search("pypy") ? "exist." : "NOT exist."));
            Console.WriteLine("pyqt is " + (tri.Search("pyqt") ? "exist." : "NOT exist."));
            tri.Detrie("python");
            Console.WriteLine("python is " + (tri.Search("python") ? "exist." : "NOT exist."));
            tri.Detrie("pypypy"); // Wrong input;
            Console.WriteLine("pypy is " + (tri.Search("pypy") ? "exist." : "NOT exist."));
        }
    }
}

/*
Input:
Output:
pypy is exist.
pyqt is NOT exist.
python is NOT exist.
pypy is NOT exist.
*/
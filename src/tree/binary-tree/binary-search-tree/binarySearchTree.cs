using System;
using System.Collections.Generic;

namespace BinarySearchTree
{
    public class BinarySearchTree
    {
        public enum Mode { preorder, inorder, postorder, levelorder };

        internal class Node
        {
            internal int _data;
            internal Node? _parent;
            internal Node? _left;
            internal Node? _right;

            internal Node(in int d)
            {
                _data = d;
                _parent = _left = _right = null;
            }
        }

        private Node? _root;

        public BinarySearchTree()
        {
            _root = null;
        }

        // Insert
        public bool Insert(in int d)
        {
            if (_root == null)
            {
                _root = new Node(d);
                return true;
            }

            // Find place and insert.
            Node cur = _root;
            while (true)
            {
                if (d < cur._data)
                {
                    if (cur._left == null)
                    {
                        cur._left = new Node(d);
                        cur._left._parent = cur;

                        return true;
                    }
                    else cur = cur._left;
                }
                else if (cur._data < d)
                {
                    if (cur._right == null)
                    {
                        cur._right = new Node(d);
                        cur._right._parent = cur;

                        return true;
                    }
                    else cur = cur._right;
                }
                else return false;
            }
        }

        // Remove elements from tree
        private Node? _findMin(Node? t)
        {
            Node? cur = t;
            while (cur != null && cur._left != null)
                cur = cur._left;

            return cur;
        }

        private bool isRoot(in Node? n)
        {
            return n._parent == null ? true : false;
        }

        public bool Detree(in int d)
        {
            if (_root == null) return false;

            Node cur = _root;

            while (cur != null)
            {
                if (d < cur._data)
                    cur = cur._left;
                else if (cur._data < d)
                    cur = cur._right;
                else break;
            }
            if (cur == null) return false;

            if (cur._left != null && cur._right != null) // two children
            {
                Node temp = _findMin(cur._right);
                int value = temp._data;

                Detree(value);
                cur._data = value;
            }
            else if (cur._left == null && cur._right == null) // No child
            {
                if (!isRoot(cur))
                {
                    if (cur == cur._parent._left) cur._parent._left = null;
                    else cur._parent._right = null;
                }
                else _root = null;
            }
            else // One child;
            {
                Node? whichChild = cur._left == null ? cur._right : cur._left;

                if (!isRoot(cur))
                {
                    if (cur._parent._left == cur) cur._parent._left = whichChild;
                    else cur._parent._right = whichChild;
                }
                else _root = whichChild;
            }

            return true;
        }

        private void PreorderTraverse(Node? t)
        {
            if (t == null) return;
            Console.Write($"{t._data} ");
            PreorderTraverse(t._left);
            PreorderTraverse(t._right);
        }

        private void InorderTraverse(Node? t)
        {
            if (t == null) return;
            InorderTraverse(t._left);
            Console.Write($"{t._data} ");
            InorderTraverse(t._right);
        }

        private void PostorderTraverse(Node? t)
        {
            if (t == null) return;
            PostorderTraverse(t._left);
            PostorderTraverse(t._right);
            Console.Write($"{t._data} ");
        }

        private void LevelorderTraverse(Node? t)
        {
            Queue<Node?> q = new Queue<Node?>();

            q.Enqueue(t);
            while (q.Count > 0)
            {
                Node? n = q.Dequeue();
                Console.Write($"{n._data} ");

                if (n._left != null) q.Enqueue(n._left);
                if (n._right != null) q.Enqueue(n._right);
            }
        }

        public void Traverse(Mode m)
        {
            switch (m)
            {
                case Mode.preorder:
                    PreorderTraverse(_root);
                    break;

                case Mode.inorder:
                    InorderTraverse(_root);
                    break;

                case Mode.postorder:
                    PostorderTraverse(_root);
                    break;

                case Mode.levelorder:
                    LevelorderTraverse(_root);
                    break;
            }
            Console.WriteLine();
        }
    }

    public static class MainApp
    {
        public static void Main()
        {
            var tree = new BinarySearchTree();

            tree.Insert(491);
            tree.Insert(198);
            tree.Insert(566);
            tree.Insert(814);
            tree.Insert(802);
            tree.Insert(423);
            tree.Insert(826);
            tree.Insert(555);
            tree.Insert(818);
            tree.Insert(802);

            tree.Traverse(BinarySearchTree.Mode.preorder);

            tree.Detree(555);
            tree.Traverse(BinarySearchTree.Mode.preorder);
            tree.Detree(814);
            Console.WriteLine();
            Console.Write("Preorder: ");
            tree.Traverse(BinarySearchTree.Mode.preorder);
            Console.Write("Inorder: ");
            tree.Traverse(BinarySearchTree.Mode.inorder);
            Console.Write("Postorder: ");
            tree.Traverse(BinarySearchTree.Mode.postorder);
            Console.Write("Levelorder: ");
            tree.Traverse(BinarySearchTree.Mode.levelorder);
        }
    }
}
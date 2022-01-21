namespace AVLTree
{
    public class AVLTree
    {
        public enum Mode { preorder, inorder, postorder, levelorder };

        internal class Node
        {
            internal int _data;
            internal Node? _parent;
            internal Node? _left;
            internal Node? _right;
            internal int _height;

            internal Node(in int d)
            {
                _data = d;
                _parent = _left = _right = null;
                _height = 0;
            }
        }

        private Node? _root;

        public AVLTree()
        {
            _root = null;
        }

        private int GetHeight(Node? n)
        {
            return n == null ? -1 : n._height;
        }

        private Node? LeftRotation(Node? n)
        {
            Node? target = n._right;
            Node? temp = target._left;

            target._left = n;
            n._right = temp;

            target._parent = n._parent;
            n._parent = target;
            if (n._right != null) n._right._parent = n;

            n._height = Math.Max(GetHeight(n._left), GetHeight(n._right)) + 1;
            target._height = Math.Max(GetHeight(target._right), n._height) + 1;

            return target;
        }

        private Node? RightRotation(Node? n)
        {
            Node? target = n._left;
            Node? temp = target._right;

            target._right = n;
            n._left = temp;

            target._parent = n._parent;
            n._parent = target;
            if (n._left != null) n._left._parent = n;

            n._height = Math.Max(GetHeight(n._left), GetHeight(n._right)) + 1;
            target._height = Math.Max(GetHeight(target._left), n._height) + 1;

            return target;
        }

        // Insertion

        private Node? Balance(Node? n)
        {
            if (n == null) return n;

            if (GetHeight(n._left) - GetHeight(n._right) > 1)
            {
                if (GetHeight(n._left._left) >= GetHeight(n._left._right))
                    n = RightRotation(n);
                else
                {
                    n._left = LeftRotation(n._left);
                    n = RightRotation(n);
                }
            }
            else if (GetHeight(n._left) - GetHeight(n._right) < -1)
            {
                if (GetHeight(n._right._left) <= GetHeight(n._right._right))
                    n = LeftRotation(n);
                else
                {
                    n._right = RightRotation(n._right);
                    n = LeftRotation(n);
                }
            }
            n._height = Math.Max(GetHeight(n._left), GetHeight(n._right)) + 1;

            return n;
        }

        private Node? Insert(Node? n, Node? nParent, in int data)
        {
            if (n == null)
            {
                n = new(data);
                n._parent = nParent;
                return n;
            }

            if (data < n._data)
                n._left = Insert(n._left, n._parent, in data);
            else if (n._data < data)
                n._right = Insert(n._right, n._parent, in data);
            else return n;

            return Balance(n);
        }

        public void Insert(in int data)
        {
            _root = Insert(_root, null, in data);
        }

        // Remove

        private Node? FindMin(Node? n)
        {
            if (n == null) return n;
            else if (n._left == null) return n;

            return FindMin(n._left);
        }

        private Node? Detree(Node? n, in int data)
        {
            if (n == null) return n;

            if (data < n._data)
                n._left = Detree(n._left, data);
            else if (n._data < data)
                n._right = Detree(n._right, data);
            else if (n._left != null && n._right != null) // Found the target and it has two children.
            {
                n._data = FindMin(n._right)._data; // Replace to the minimum node's value
                n._right = Detree(n._right, n._data); // Remove the minimum node
            }
            else // Found the target and it has no child or one child.
            {
                Node? p = n._parent;
                n = (n._left != null) ? n._left : n._right;
                if (n != null) n._parent = p;
            }

            return Balance(n);
        }
        
        public void Detree(in int data)
        {
            _root = Detree(_root, in data);
        }

        // Search

        public bool Search(in int data)
        {
            Node? cur = _root;

            while (cur != null)
            {
                if (data < cur._data)
                    cur = cur._left;
                else if (cur._data < data)
                    cur = cur._right;
                else
                {
                    Console.WriteLine($"{data} is exist in the tree.");
                    goto exit_success;
                }
            }

            Console.WriteLine($"{data} is NOT found in the tree.");
            return false;
        exit_success:
            return true;
        }

        // Traversal

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
            var tree = new AVLTree();

            tree.Insert(491);
            tree.Insert(198);
            tree.Insert(566);
            tree.Insert(814);
            tree.Insert(802);
            tree.Insert(423);
            tree.Insert(826);
            tree.Insert(555);
            tree.Insert(818);

            tree.Traverse(AVLTree.Mode.preorder);

            tree.Detree(555);
            tree.Traverse(AVLTree.Mode.preorder);
            tree.Detree(814);

            Console.WriteLine();
            Console.Write("Preorder: ");
            tree.Traverse(AVLTree.Mode.preorder);
            Console.Write("Inorder: ");
            tree.Traverse(AVLTree.Mode.inorder);
            Console.Write("Postorder: ");
            tree.Traverse(AVLTree.Mode.postorder);
            Console.Write("Levelorder: ");
            tree.Traverse(AVLTree.Mode.levelorder);
            Console.WriteLine();

            tree.Search(814); // NOT found
            tree.Search(423); // Found
        }
    }
}
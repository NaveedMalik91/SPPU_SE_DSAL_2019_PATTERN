#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class node
{
private:
    node *lchild;
    node *rchild;
    int data;

public:
    node()
    {
        this->data = 0;
        this->lchild = NULL;
        this->rchild = NULL;
    }
    node(int x)
    {
        this->data = x;
        this->lchild = NULL;
        this->rchild = NULL;
    }
    friend class Binarytree;
};
class Binarytree
{
public:
    node *root;
    Binarytree()
    {
        root = NULL;
    }
    void insert(int a)
    {
        while (true)
        {
            node *node1 = new node(a);
            if (root == NULL)
            {
                root = node1;
            }
            else
            {
                queue<node *> q;
                q.push(root);
                while (!q.empty())
                {
                    node *temp = q.front();
                    q.pop();
                    if (temp->lchild == NULL)
                    {
                        temp->lchild = node1;
                        cout << "Node Added";
                        break;
                    }
                    else if (temp->rchild == NULL)
                    {
                        temp->rchild = node1;
                        break;
                    }
                    else
                    {
                        q.push(temp->lchild);
                        q.push(temp->rchild);
                    }
                }
            }
            cout << "Do you want to add more nodes:(y/n): ";
            char ch;
            cin >> ch;
            if (ch != 'y' && ch != 'Y')
            {
                break;
            }
            else
            {
                cin >> a;
            }
        }
    }
    void preorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        cout << root->data << " ";
        preorder(root->lchild);
        preorder(root->rchild);
    }
    void postorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        postorder(root->lchild);
        postorder(root->rchild);
        cout << root->data << " ";
    }
    void inorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        inorder(root->lchild);
        cout << root->data << " ";
        inorder(root->rchild);
    }

    void non_inorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        stack<node *> st;
        node *curr = root;
        while (curr != NULL || !st.empty())
        {
            while (curr != NULL)
            {
                st.push(curr);
                curr = curr->lchild;
            }
            curr = st.top();
            st.pop();
            cout << curr->data;
            curr = curr->rchild;
        }
    }

    void non_postorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        stack<node *> st;
        node *curr = root;
        node *last = NULL;
        while (curr != NULL || !st.empty())
        {

            while (curr != NULL)
            {
                st.push(curr);
                curr = curr->lchild;
            }
            curr = st.top();
            if (curr->rchild == last || curr->rchild == NULL)
            {
                cout << curr->data << " ";
                st.pop();
                last = curr;
                curr = NULL;
            }
            else
            {
                curr = curr->rchild;
            }
        }
    }

    void non_preorder(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            stack<node *> st;
            st.push(root);
            while (!st.empty())
            {
                root = st.top();
                st.pop();
                cout << root->data << " ";
                if (root->lchild)
                {
                    st.push(root->lchild);
                }
                if (root->rchild)
                {
                    st.push(root->rchild);
                }
            }
        }
    }

    int height(node *root)
    {
        if (root == NULL)
        {
            return -1;
        }
        int left = height(root->lchild);
        int right = height(root->rchild);
        return max(left, right) + 1;
    }

    int leaf_nodes(node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->lchild == NULL && root->rchild == NULL)
        {
            cout << "Leaf node = :";
            cout << root->data << " ";
            return 1;
        }
        return leaf_nodes(root->lchild) + leaf_nodes(root->rchild);
    }

    int intermediate_nodes(node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->lchild == NULL && root->rchild == NULL)
        {
            return 0;
        }
        int intermediate = 0;
        if (root->lchild != NULL)
        {
            if (root->lchild->lchild != NULL || root->lchild->rchild != NULL)
            {
                cout << "Intermediate node:";
                cout << root->lchild->data << " ";
                intermediate++;
            }
            intermediate += intermediate_nodes(root->lchild);
        }
        if (root->rchild != NULL)
        {
            if (root->rchild->lchild != NULL || root->rchild->rchild != NULL)
            {
                cout << "Intermediate node:";
                cout << root->rchild->data << " ";
                intermediate++;
            }
            intermediate += intermediate_nodes(root->rchild);
        }
        return intermediate;
    }
    void swap(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        swap(root->lchild);
        swap(root->rchild);
        node *temp = root->lchild;
        root->lchild = root->rchild;
        root->rchild = temp;
    }

    void deletet(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        deletet(root->lchild);
        deletet(root->rchild);
        delete root;
        root = NULL;
    }
    void level_order(node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        queue<node *> q;
        q.push(root);
        while (!q.empty())
        {
            node *curr = q.front();
            q.pop();
            cout << curr->data << " ";

            if (curr->lchild != nullptr)
            {
                q.push(curr->lchild);
            }
            if (curr->rchild != nullptr)
            {
                q.push(curr->rchild);
            }
        }
    }
};
int main()
{
    Binarytree t, t1, t2, t3;
    int x;
    while (true)
    {
        cout << endl;
        cout << "=---------MENU---------" << endl;
        cout << "1. Enter the nodes of tree" << endl;
        cout << "2. Recursive Traversal of tree" << endl;
        cout << "3. Non - Recursive Traversal of tree" << endl;
        cout << "4. Height of tree" << endl;
        cout << "5. Get leaf and Intermediate nodes of Tree" << endl;
        cout << "6. Swap the Binary Tree" << endl;
        cout << "7. Delete the Binary Tree" << endl;
        cout << "8. Level order printing" << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "Enter Your choice: " << endl;
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the number to add: " << endl;
            cin >> x;
            t.insert(x);
            break;

        case 2:
            cout << "Recursive Traversal:" << endl;
            cout << "Inorder traversal: " << endl;
            t.inorder(t.root);
            cout << endl;

            cout << "Preorder traversal: " << endl;
            t.preorder(t.root);
            cout << endl;

            cout << "Postorder traversal: " << endl;
            t.postorder(t.root);
            cout << endl;
            break;

        case 3:
            cout << "Non-Recursive Tree Traversal:" << endl;
            cout << "Inorder Traversal:" << endl;
            t.non_inorder(t.root);
            cout << endl;

            cout << "Pre-order Traversal:" << endl;
            t.non_preorder(t.root);
            cout << endl;

            cout << "Post-order Traversal:" << endl;
            t.non_postorder(t.root);
            cout << endl;
            break;

        case 4:
            cout << "Height of tree is: " << t.height(t.root) << endl;
            break;

        case 5:
            cout << "Number of leaf nodes : " << t.leaf_nodes(t.root) << endl;
            cout << "Number of intermediate nodes : " << t.intermediate_nodes(t.root) << endl;
            break;

        case 6:
            t2 = Binarytree(t);
            t2.swap(t2.root);
            cout << "Tree traversal of swapped tree(inorder)"
                 << " ";
            t2.inorder(t2.root);
            cout << endl;
            break;

        case 7:
            t.deletet(t.root);
            cout << "Tree deleted" << endl;
            t.root = NULL;
            break;
        case 8:
            cout << "Level order printing:" << endl;
            t.level_order(t.root);
            break;

        case 9:
            cout << "Exiting program." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}
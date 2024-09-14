//Heap sort
#include <iostream>
#include <queue>
using namespace std;

class Node
{
    int data;
    Node *left, *right;

public:
    Node()
    {
        this->data = 0;
        this->left = nullptr;
        this->right = nullptr;
    }

    Node(int i)
    {
        this->data = i;
        this->left = nullptr;
        this->right = nullptr;
    }

    friend class BT;
};

class BT
{
private:
    Node *root;
public:
    BT()
    {
        this->root = NULL;
    }
    queue<Node*> q;
    int numNodes = 0;
    //max-heap->>decreasing order of values
    Node *maxHeapTree(Node *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        //each root node is checked recursively to maintain Bst structure 
        node->left = maxHeapTree(node->left);
        node->right = maxHeapTree(node->right);

        if (node->left != nullptr && node->left->data > node->data)
        {
            int temp = node->data;
            node->data = node->left->data;
            node->left->data = temp;
        }
        if (node->right != nullptr && node->right->data > node->data)
        {
            int temp = node->data;
            node->data = node->right->data;
            node->right->data = temp;
        }

        return node;
    }

    Node *lastNode()
    {
        queue<Node *> q;
        q.push(this->root);
        Node *current = nullptr;

        while (!q.empty())
        {
            current = q.front();
            q.pop();

            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }

        return current;
    }

    Node *deleteNode(Node *node, int key)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->data == key)
        {
            delete node;
            return nullptr;
        }

        node->left = deleteNode(node->left, key);
        node->right = deleteNode(node->right, key);
        return node;
    }

    void insert(int value)
    {
        
        if (this->root == nullptr)
        {
            this->root = new Node(value);
            q.push(this->root);
        }

        else
        {
            Node *newNode = new Node(value);
            Node *current = q.front();

            while (true)
            {
                if (current->left != nullptr && current->right != nullptr)
                {
                    q.push(current->left);
                    q.push(current->right);
                    q.pop();
                    current = q.front();
                }

                else if (current->left == nullptr)
                {
                    current->left = newNode;
                    break;
                }

                else
                {
                    current->right = newNode;
                    break;
                }
            }
        }
        numNodes++;
    }

    void BFStraversal()
    {
        queue<Node *> q;
        q.push(this->root);
        Node *current = nullptr;

        while (!q.empty())
        {
            current = q.front();
            cout << current->data << " ";
            q.pop();

            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    void heapSort()
    {
        for (int i = 0; i < numNodes; i++)
        {
            maxHeapTree(this->root);
            Node *last = lastNode();

            int temp = this->root->data;
            this->root->data = last->data;
            last->data = temp;

            cout << last->data << " ";
            deleteNode(this->root, last->data); //atlast value of root is stored sot it will get deleted
        }
    }
   
};

int main()
{
    BT b;
    int num, ch, marks;
    while (true)
    {
        cout << "\n---------CHOICE----------" << endl;
        cout << "1.Create a heap" << endl;
        cout << "2.Display unsorted heap" << endl;
        cout << "3.Sort data using heap-sort" << endl;
        cout << "4.Exit" << endl;
        cout << endl;
        cout << "Enter your choice: " << endl;
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter the total number of values: ";
            cin >> num;
            for (int i = 0; i < num; i++)
            {
                cout << "Enter the marks of student " << i + 1 << ":";
                cin >> marks;
                b.insert(marks);
            }
            break;
        case 2:
            cout << "Unsorted Heap: ";
            b.BFStraversal();
            break;
        case 3:
            cout << "Sorted heap using heap-sort: ";
            b.heapSort();
            break;
        case 4:
            cout << "Exiting program" << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
    return 0;
}
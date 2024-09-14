#include <iostream>
using namespace std;
class node
{
private:
    node *lchild;
    node *rchild;
    int data;
    bool lthread;
    bool rthread;

public:
    node()
    {
        this->lchild = NULL;
        this->rchild = NULL;
        this->lthread = true;
        this->rthread = true;
    }
    node(int val)
    {
        this->data = val;
    }
    friend class TBST;
};
class TBST
{
private:
    node *root;

public:
    TBST()
    {
        this->root = NULL;
    }
    TBST(node *root)
    {
        this->root = root;
    }
    void insert(int val)
    {
        node *curr = root;
        node *par = NULL;
        while (curr != NULL)
        {
            par = curr;
            if (val < curr->data)
            {
                if (curr->lthread == false)
                {
                    curr = curr->lchild;
                }
                else
                {
                    break;
                }
            }
            else if (val > curr->data)
            {
                if (curr->rthread == false)
                {
                    curr = curr->rchild;
                }
                else
                {
                    break;
                }
            }
        }
        node *node1 = new node(val);
        node1->lthread = true;
        node1->rthread = true;

        if (par == NULL)
        {
            root = node1;
            node1->lchild = NULL;
            node1->rchild = NULL;
        }
        else if (val < curr->data)
        {
            node1->lchild = par->lchild;
            node1->rchild = par;
            par->lthread = false;
            par->lchild = node1;
        }
        else
        {
            node1->lchild = par;
            node1->rchild = par->rchild;
            par->rthread = false;
            par->rchild = node1;
        }
    }

    node *in_succ(node *ptr)
    {
        if (ptr->rthread == true)
        {
            return ptr->rchild;
        }
        ptr = ptr->rchild;
        while (ptr->lthread == false)
        {
            ptr = ptr->lchild;
        }
        return ptr;
    }

    node *pre_succ(node *ptr)
    {
        if (ptr->lthread == true)
        {
            return ptr->lchild;
        }
        ptr = ptr->lchild;
        while (ptr->rthread == false)
        {
            ptr = ptr->rchild;
        }
        return ptr;
    }
    void inorder()
    {
        if (root == NULL)
        {
            cout << "Empty tree" << endl;
            return;
        }
        node *curr = root;
        while (curr->lthread == false)
        {
            curr = curr->lchild;
        }
        while (curr != NULL)
        {
            cout << "Node" << curr->data << endl;
            cout << "Lbit:";
            if (curr->lchild != NULL)
            {
                cout << curr->lchild->data;
            }
            else
            {
                cout << "NULL";
            }

            if (curr->rchild != NULL)
            {
                cout << " ,Rbit:" << curr->rchild->data;
            }
            else
            {
                cout << "NULL";
            }
            cout << endl;
            curr = in_succ(curr);
        }
    }

    void preorder()
    {
        if (root == NULL)
        {
            cout << "Tree Empty" << endl;
            return;
        }
        node *ptr = root;

        while (ptr)
        {
            cout << ptr->data << " ";
            if (!ptr->lthread)
                ptr = ptr->lchild;
            else if (!ptr->rthread)
                ptr = ptr->rchild;
            else
            {
                while (ptr and ptr->rthread)
                {
                    ptr = ptr->rchild;
                }
                if (ptr)
                {
                    ptr = ptr->rchild;
                }
            }
        }
    }
    
    // Deletion
    //No child
    //1.If left node of parent is deleted then its parent left
    //thread will point to its predecessor..
    //2. If right node of parent is deleted then the right
    //thread of parent will point to its succesor
    node* caseA(node* par, node* curr)
    {
        if (par == NULL)
        {
            root = NULL;
        }
        else if(curr == par->lchild)
        {
            par->lthread = false;
            par->lchild = curr->lchild;//lthread point to predecessor of parent
        }
        else
        {
            par->rthread = false;
            par->rchild = curr->rchild;// rthread point to successor of parent
        }
        delete curr;
        return root;
        
    }
    //One child
    //Incase of deleted node is left child then its rthread will point to its successor
    //Incase of node has right subtree leftthread will point to its predecessor
    node* caseB(node* par, node* curr)
    {
        node* child;
        if (!curr->lthread)
        {
            child = curr->lchild;
        }
        if(!curr->rthread)
        {
            child = curr->rchild;
        }
        //root of a node is deleted
        if (par == NULL)
        {
            root = child;
        }
        // left to root node
        else if(curr == par->lchild)
        {
            par->lchild = child; //node to be deleted replaced with its child node
        }
        //right to root node
        else
        {
            par->rchild = child;
        }

        //Adusting threads
        node* s = in_succ(curr);
        node* p = pre_succ(curr);

        if (!curr->lthread)
        {
            p->rchild = s; 
        }
        if (!curr->rthread)
        {
            s->lchild = p;
        }
        delete curr;
        return root;
        
    }
    //Two nodes
    //Node to be deleted is replaced with its inorder successor and delete in_succ.
    node* caseC(node* curr)
    {
        node* parsucc = curr; 
        node* succ = in_succ(curr);
        curr->data = succ->data;
        if (succ->lthread and succ->rthread) // inorder succesor is a leaf node
        {
            root = caseA(parsucc,succ);
        }
        else //inorder succesor is not a leaf node
        {
            root = caseB(parsucc,succ);
        }
        return root;
        
    }

    node* delete_node(int val)
    {
        node* par = NULL;
        node* curr = root;
        bool found = false;
        while (curr)
        {
            if (val == curr->data)
            {
                found = true;
                break;
            }
            par = curr;
            if(val < curr->data)
            {
                if (curr->lthread == false)
                {
                    curr = curr->lchild;
                }
                else
                {
                    break;
                }
                
            }
            else
            {
                if (curr->rthread == false)
                {
                    curr = curr->rchild;
                }
                else
                {
                    break;
                }
                
            }
        }
        if (!found)
        {
            cout<<"Key not found"<<endl;
        }
        else if(curr->lthread and curr->rthread) // leaf node
        {
            root = caseA(par,curr);

        }
        else if(curr->lthread) //left child of node exists
        {
            root = caseB(par,curr);
        }
        else if(curr->rthread) //rchild of node exists
        {
            root = caseB(par,curr);
        }
        else if(!curr->lthread and !curr->rthread) //Two node exists
        {
            root = caseC(curr);
        }
        return root;
    }

};

int main()
{
    TBST t1;
    int del;
    int choice = 0;
    while (choice < 5)
    {
        cout << "Operations" << endl;
        cout << "1. Insertion" << endl;
        cout << "2. Inorder" << endl;
        cout << "3. Preorder" << endl;
        cout << "4. Deletion" << endl;
        cout << "Enter the choice number: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the no. of nodes: ";
            int n;
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter data: ";
                int d;
                cin >> d;
                t1.insert(d);
            }
            break;

        case 2:
            cout<<"--------------------"<<endl;
            cout << "Inorder" << endl;
            t1.inorder();
            cout<<"--------------------"<<endl;
            break;

        case 3:
            cout<<"--------------------"<<endl;
            cout << "Preorder" << endl;
            t1.preorder();
            cout<<endl;
            cout<<"--------------------"<<endl;
            break;
        case 4:
            cout<<"Enter the node to delete"<<endl;
            cin>>del;
            t1.delete_node(del);
            cout<<"Node has been deleted successfully"<<endl;
            t1.inorder();
            break;

        default:
            cout << "Invalid Choice";
            break;
        }
    }
}

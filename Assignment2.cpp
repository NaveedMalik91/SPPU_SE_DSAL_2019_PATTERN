#include <iostream>
#include <stack>
using namespace std;
class Node
{
private:
    Node *lchild;
    Node *rchild;
    string keyword;
    string meaning;

public:
    Node()
    {
        this->keyword = "";
        this->meaning = "";
        this->lchild = NULL;
        this->rchild = NULL;
    }
    Node(string keyword, string meaning)
    {
        this->keyword = keyword;
        this->meaning = meaning;
        this->lchild = NULL;
        this->rchild = NULL;
    }
    friend class Dictionary;
};
class Dictionary
{
private:
    Node *root;

public:
    Dictionary()
    {
        this->root = NULL;
    }
    Dictionary(Node *val)
    {
        this->root = val;
    }
    Node *getroot() const
    {
        return root;
    }
    void setroot(Node *newroot)
    {
        root = newroot;
    }

    Node *createnode(string keyword, string meaning)
    {
        Node *node1 = new Node(keyword, meaning);
        return node1;
    }

    Node *insert(Node *root, string keyword, string meaning)
    {
        if (root == NULL)
        {
            return createnode(keyword, meaning);
        }
        if (keyword < root->keyword)
        {
            root->lchild = insert(root->lchild, keyword, meaning);
        }
        if (keyword > root->keyword)
        {
            root->rchild = insert(root->rchild, keyword, meaning);
        }
        return root;
    }
    Node *inc_succ(Node *node)
    {
        while (node->lchild != NULL)
        {
            node = node->lchild;
        }
        return node;
    }

    Node *remove(Node *root, string keyword)
    {
        if (root == NULL)
        {
            cout << "Tree is empty";
        }
        if (keyword > root->keyword)
        {
            root->rchild = remove(root->rchild, keyword);
        }
        if (keyword < root->keyword)
        {
            root->lchild = remove(root->lchild, keyword);
        }
        else
        {
            if (root->lchild == NULL)
            {
                Node *temp = root->rchild;
                delete root;
                return temp;
            }
            if (root->rchild == NULL)
            {
                Node *temp = root->lchild;
                delete root;
                return temp;
            }
            Node *temp = inc_succ(root->rchild);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->rchild = remove(root->rchild, keyword);
        }
        return root;
    }

    int search(Node *root, string key)
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
        }
        int count = 0;
        Node* curr = root;
        while (curr != NULL)
        {
            count++;
            if (curr->keyword==key)
            {
                cout << "Keyword found in the tree" << endl;
                cout << "Keyword: " << curr->keyword <<" "<<"Meaning: " << curr->meaning << endl;
                cout << "Comparisons made are: " << count;
                return count;
            }

            if (key > curr->keyword)
            {
                curr = curr->rchild;
            }
            if (key < curr->keyword)
            {
                curr = curr->lchild;
            }
        }
        cout << "Keyword not Found" << endl;
        cout << "Maximum comparisond made are:" << count << endl;
        
    }

    void update(string keyword, string NewMean)
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
        }
        Node *curr = root;
        while (curr != NULL)
        {
            if (keyword == curr->keyword)
            {
                curr->meaning = NewMean;
                return;
            }
            else if (keyword > curr->keyword)
            {
                curr = curr->rchild;
            }
            else if (keyword < curr->keyword)
            {
                curr = curr->lchild;
            }
        }
        cout << "Keyword not found, Update Failed!!" << endl;
    }

    void ascending()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }

        stack<Node *> s;
        Node *current = root;

        while (current != NULL || !s.empty())
        {
            while (current != NULL)
            {
                s.push(current);
                current = current->lchild;
            }
            current = s.top();
            s.pop();
            cout << current->keyword << ": " << current->meaning << endl;
            current = current->rchild;
        }
    }

    void descending()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        stack<Node *> s;
        Node *current = root;
        while (current != NULL || !s.empty())
        {
            while (current != NULL)
            {
                s.push(current);
                current = current->rchild;
            }
            current = s.top();
            s.pop();
            cout << current->keyword << ": " << current->meaning << endl;
            current = current->lchild;
        }
    }

    void min_max()
    {
        if (root == NULL)
        {
            return;
        }
        while (root->lchild != NULL)
        {
            root = root->lchild;
        }
        Node *min_node = root;
        while (root->rchild != NULL)
        {
            root = root->rchild;
        }
        Node *max_node = root;
        cout << "Maximum value in BST is:" << max_node->keyword << endl;
        cout << "Minimum node in BST is: " << min_node->keyword << endl;
    }
    bool addmorekeys()
    {
        char ch;
        cout << "Do you want to add more keys(y/n)" << endl;
        cin >> ch;
        return (ch == 'y' || ch == 'Y');
    }
};
int main(int argc, char const *argv[])
{
    Dictionary obj ,dict;
    int choice;
    string key;
    string mean;
    do
    {
        cout << "\n------------CHOICE---------\n";
        cout << "1. Add new keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update keyword meaning\n";
        cout << "4. Display in ascending order\n";
        cout << "5. Display in Descending order\n";
        cout << "6. Search a keyword in Tree\n";
        cout << "7. Minimum and Maximum value in bst\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
            do
            {
            case 1:
                cout << "Enter the keyword:" << endl;
                cin >> key;
                cin.ignore();
                cout << "Enter the meaning:" << endl;
                cin >> mean;
                cin.ignore();
                obj.setroot(obj.insert(obj.getroot(), key, mean));
                cout << "Keyword added successfully" << endl;
            } while (obj.addmorekeys());
            break;
        case 2:
            cout << "Enter the keyword to delete" << endl;
            cin >> key;
            cin.ignore();
            obj.setroot(obj.remove(obj.getroot(), key));
            cout << "Keyword has been deleted" << endl;
            break;
        case 3:
            cout << "Enter the keyword to update its meaning" << endl;
            cin >> key;
            cin.ignore();
            cout << "Enter the new meaning" << endl;
            cin >> mean;
            cin.ignore();
            obj.update(key, mean);
            cout << "Keyword updated successfully" << endl;
            break;
        case 4:
            cout << "The ascending order of keywords:meaning is:" << endl;
            obj.ascending();
            break;
        case 5:
            cout << "The descending order of keywords:meaning is:" << endl;
            obj.descending();
            break;
        case 6:
        {
            string k;
            cout << "Enter the keyword to search" << endl;
            cin >> k;
            cin.ignore();
            obj.search(obj.getroot(), k);
            break;
        }
        case 7:
            obj.min_max();
            break;
        default:
            cout << "Exiting program....." << endl;
            break;

        }
    }while(choice!=8);
    return 0;
}

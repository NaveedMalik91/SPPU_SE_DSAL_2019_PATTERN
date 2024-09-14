#include <iostream>
#include <string>
using namespace std;
class entry
{
private:
    int index;
    string key;
    string meaning;
    entry *next;

public:
    entry()
    {
        
        this->index = -1;
        this->key = "";
        this->meaning = "";
        this->next = NULL;
    }
    entry(int ind)
    {
        this->index = ind;
        this->next = NULL;
    }
    entry(string x, string y)
    {
        this->key = x;
        this->meaning = y;
        this->next = NULL;
    }
    friend class Dictionary;
};

class Dictionary
{
private:
    entry table[10];

public:
    Dictionary(){
       
    }

    int hash_func(const string &str)
    {
        int sum = 0;
        for (char c : str)
        {
            if (isalnum(c))
            {
                sum += c;
            }
        }
        return (3 * sum + 5) % 10;
    }

    void insert(string key, string mean)
    {
        int hash_key = hash_func(key);
        entry *newEntry = new entry(key, mean);
        // Adjusting pointers and insert value
        newEntry->index = hash_key;            // points to index where stored
        newEntry->next = table[hash_key].next; // points to next of index where stored
        table[hash_key].next = newEntry;
    }

    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            cout << i;

            entry *ptr = table[i].next;

            while (ptr)
            {
                cout << "-> [ " << ptr->key << " : " << ptr->meaning << " ] ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    }

    void search(string k)
    {
        int hash_key = hash_func(k);
        entry *ptr = table[hash_key].next; // ptr will hold the index where value stored
        bool flag = 0;
        int count = 1;
        while (ptr)
        {
            if (ptr->key == k)
            {
                cout << "Key = " << k << " found at index = " << hash_key << endl;
                cout << "Position = " << count<<endl;
                flag = 1;
                break;
            }
            count++;
            ptr = ptr->next; // move to the next node in linked list untill value found
        }
        if (!flag)
        {
            cout << "Key not added yet in the Dictionary" << endl;
        }
    }

    void delete_key(string k)
    {
        int hash_key = hash_func(k);
        // Element to be deleted is first in chain
        while (table[hash_key].next->key == k)
        {
            entry *todelete = table[hash_key].next;            // storing the value to be deleted
            table[hash_key].next = table[hash_key].next->next; // move pointer to second value in chain
            delete todelete;
            cout << "Key contaning " << k << " has been deleted" << endl;
            cout << endl;
            return;
        }
        // Element to be deleted is not first in chain
        entry *ptr = table[hash_key].next;
        while (ptr->next)
        {
            if (ptr->next->key == k)
            {
                entry *tobedelete = ptr->next;
                ptr->next = ptr->next->next;
                delete tobedelete;
                cout << "Key = " << k << " has been deleted" << endl;
                cout << endl;
                return; // if found then return
            }
            ptr = ptr->next; // otherwise move to next value
        }
        cout << "Element not found" << endl;
        return;
    }
};

int main()
{
    Dictionary obj;
    int choice, num;
    string key, mean;
    while (true)
    {
        cout << "--------Choice---------" << endl;
        cout << "1.Insert the keys" << endl;
        cout << "2.Display the keys" << endl;
        cout << "3.Search the keys" << endl;
        cout << "4.Delete the keys" << endl;
        cout << "5.Exit" << endl;
        cout << endl;
        cout << "Enter the choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the total values" << endl;
            cin >> num;
            for (int i = 0; i < num; i++)
            {
                cout << "Enter the Key:";
                cin >> key;
                cout << "Enter the mean:";
                cin >> mean;
                obj.insert(key, mean);
            }
            break;
        case 2:
            cout << "----------Dictionary Content----------" << endl;
            obj.display();
            cout << "-------------------------------" << endl;
            break;
        case 3:
            cout << "Enter the key to Search" << endl;
            cin >> key;
            obj.search(key);
            break;
        case 4:
            cout << "Enter the key to delete" << endl;
            cin >> key;
            obj.delete_key(key);
            break;
        case 5:
            cout << "Exitiqng program" << endl;
            return 0;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

    return 0;
}

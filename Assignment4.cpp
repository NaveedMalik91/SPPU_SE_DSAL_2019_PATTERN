#include <iostream>
using namespace std;
class entry
{
private:
    int index;
    string data;

public:
    entry()
    {
        this->data = -1;
    }
    entry(int x, string s)
    {
        this->data = s;
        this->index = x;
    }
    friend class tele_direc;
};
class tele_direc
{
private:
    entry table[10];

public:
    tele_direc()
    {
        for (int i = 0; i < 10; i++)
        {
            table[i] = entry(i, "-1");
        }
    }

    int hash_func(string value)
    {
        int sum = 0;
        for (char c : value)
        {
            sum += c - '0';
        }
        return (3 * sum + 5) % 10;
    }
    void display()
    {
        for (int i = 0; i < 10; i++)
        {
            cout << table[i].index << ":" << table[i].data<<endl;;
        }
    }

    void with_replacement(string val)
    {
        int hash_key = hash_func(val);
        // if not collision
        if (table[hash_key].data == "-1")
        {
            table[hash_key].data = val;
        }
        // If collision
        else
        {
            int replaced = hash_func(table[hash_key].data);
            table[hash_key].data = val;
            while (table[hash_key].data != "-1")
            {
                if (hash_key > 9)
                {
                    hash_key = 0;
                }
                hash_key++;
            }
            table[hash_key].data = replaced;
        }
    }
    void without_replacement(string val)
    {
        int hash_key = hash_func(val);
        while (table[hash_key].data != "-1")
        {
            if (hash_key > 9)
            {
                hash_key = 0;
            }
            hash_key++;
        }
        table[hash_key].data = val;
    }

    void delete_entry(string val)
    {
        int hash_key = hash_func(val);
        while (table[hash_key].data != val)
        {
            if (hash_key > 9)
            {
                hash_key = 0;
            }
            hash_key++;
        }
        table[hash_key].data = "-1";
    }

    void search(string val, int comp)
    {
        int hash_key = hash_func(val);
        comp = 1;
        if (table[hash_key].data == val)
        {
            cout << "Element found = " << val << " found at position =" << table[hash_key].index << endl;
        }
        else
        {
            while (1)
            {
                hash_key++;
                if (hash_key > 9)
                {
                    hash_key = 0;
                }
                comp++;
                if (comp > 10)
                {
                    cout << "Element not found" << endl;
                }
            }
        }
    }
};
int main(int argc, char const *argv[])
{
    tele_direc obj1,obj2;
    int choice ,comp;
    string ph_no;
    do
    {
        cout << endl;
        cout << "1. Insert phone numbers" << endl;
        cout << "2. Display hash table contents" << endl;
        cout << "3. Search for a number in table" << endl;
        cout << "4. Delete an entry" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter the choice:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            int num;
            cout<<"Enter how many numbers you want to add"<<endl;
            cin>>num;
            for (int i = 0; i < num; i++)
            {
                cout<<"Enter 10-digit mobile number"<<endl;
                cin>>ph_no;
                if (ph_no.length() != 10)
                {
                    cout<<"Invalid number"<<endl;
                    continue;
                }
                obj1.with_replacement(ph_no);
                obj2.without_replacement(ph_no);
            }
            break;
        case 2:
            cout<<"Hash table with replacement:"<<endl;
            obj1.display();
            cout<<endl;
            cout<<"Hash table without replacement:"<<endl;
            obj2.display();
            break;
        case 3:
            cout<<"Enter the phone_number to search:";
            cin>>ph_no;
            if (ph_no.length() != 10)
            {
                cout<<" Invalid number"<<endl;
                break;
            }
            comp = 0;
            obj1.search(ph_no , comp);
            cout<<"The comparisons with replacement =  "<<comp<<endl;
            cout<<endl;
            comp = 0;
            obj2.search(ph_no , comp);
            cout<<"The comparisons without replacement = "<<comp;
            cout<<endl;
            break;
        case 4:
            cout<<"Enter the ph_num to delete"<<endl;
            cin>>ph_no;
            obj1.delete_entry(ph_no);
            obj2.delete_entry(ph_no);
            cout<<"The phone number enterred has been deleted"<<endl;
        case 5:
            cout<<"Exiting program........"<<endl;
        default:
            cout<<"Invalid choice"<<endl;
            break;
        }
    } while (choice != 6);
    
    
    return 0;
}

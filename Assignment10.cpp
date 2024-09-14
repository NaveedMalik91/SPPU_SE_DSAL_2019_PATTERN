// Direct file access
#include <iostream>
#include<vector>
#include <fstream>
#include <string>
using namespace std;
class Hashtable
{
private:
    int addr;

public:
    Hashtable()
    {
        for (int i = 0; i < 10; i++)
        {
            this->addr = -1;
        }
    }
    friend class Employee;
};
Hashtable HT[10];

class Employee
{
private:
    int id;
    char name[10];
    char salary[10];
    char exp[10];

public:
    // Add a record
    void add_record()
    {
        int count;
        cout << "How many records you want to enter..? ";
        cin >> count;
        ofstream fout;
        fout.open("Employee.txt", ios::out); // opening a file
        for (int i = 0; i < count; i++)
        {
            cout << "Enter the Name: ";
            cin>>name;
            cout << "Enter the ID: ";
            cin >> id;
            cout << "Enter the Salary: ";
            cin >> salary;
            cout << "Enter the Experience in years: ";
            cin >> exp;
            int location = fout.tellp();
            int index = id % 10; // tablesize = 10
            HT[index].addr = location;
            fout << name << " " << id << " " << salary << " " << exp << endl;
        }
        fout.close();
    }
    // Display a record
    void display()
    {
        int cnt = 1;
        char buffer[40]; // Read in put from files and clears the input buffer created during input
        ifstream fin;
        fin.open("Employee.txt", ios::in);
        while (!fin.eof())
        {
            fin.getline(buffer, 40);
            cout << "Record " << cnt << ": " << buffer << endl;
            cnt++;
        }
        fin.close();
    }
    // Search a record
    void search()
    {
        int id;
        cout << "Enter the id:";
        cin >> id;
        // Getting index in hashtable where id is stored
        int index = id % 10;
        // Getting location
        int location = HT[index].addr;
        ifstream fin;
        fin.open("Employee.txt", ios::in);
        // Go to location
        fin.seekg(location, ios::beg);
        char buffer[40];
        // Read the data from location
        fin.getline(buffer, 40);
        cout << "Record Found: " << buffer << endl;
    }
    // Delete a record
    void delete_record()
    {
        int id;
        cout << "Enter the id: ";
        cin >> id;

        int index = id % 10;
        int location = HT[index].addr;
        ifstream fin;
        fin.open("Employee.txt", ios::in);
        fin.seekg(location, ios::beg);
        char buffer[40];
        fin.getline(buffer, 40);
        cout << "Deleted Record: " << buffer << endl;
        fin.close();
        cout << "Remaining Records:- " << endl;
        // reopen file
        fin.open("Employee.txt", ios::in);
        for (int i = 0; i < 10; i++)
        {
            if (HT[i].addr != -1 && HT[i].addr != location)
            {
                fin.seekg(HT[i].addr, ios::beg);
                fin.getline(buffer, 40);
                cout << "Record: " << buffer<<endl;
            }
        }
        fin.close();
    }
};
int main()
{
    Employee E;
    while (true)
    {
        cout << "1.Write Records in Direct Access File" << endl;
        cout << "2.Read Records from Direct Access File" << endl;
        cout << "3.Search Record in Direct Access File" << endl;
        cout << "4.Delete Record from Direct Access File" << endl;
        cout << "5.Delete the Direct Access File" << endl;
        cout << "6.Exit" << endl;
        cout << endl;
        cout << "Enter your choice : ";
        int res;
        cin >> res;
        if (res == 1)
            E.add_record();
        else if (res == 2)
            E.display();
        else if (res == 3)
            E.search();
        else if (res == 4)
            E.delete_record();
        else if (res == 5)
            remove("Employee.txt");
        else if (res == 6)
            break;
        else
            continue;
    }
    return 0;
}

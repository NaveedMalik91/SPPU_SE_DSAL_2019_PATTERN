//Sequential file access
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Student
{
private:
    int roll_no;
    string name;
    string division;
    string address;

public:
    Student()
    {
        this->roll_no = 0;
        this->name = "";
        this->division = "";
        this->address = "";
    }
    Student(int x, string a, string b, string c)
    {
        this->roll_no = x;
        this->name = a;
        this->division = b;
        this->address = c;
    }
    void add_student()
    {
        cout << "Enter the name: ";
        getline(cin, name);
        cin.ignore();
        cout << "Enter the roll_no: ";
        cin >> roll_no;
        cin.ignore();
        cout << "Enter the Division: ";
        getline(cin, division);
        cin.ignore();
        cout << "Enter the address: ";
        getline(cin, address);
        cin.ignore();

        ofstream obj("student.txt", ios::app);
        obj << roll_no << endl;
        obj << name << endl;
        obj << division << endl;
        obj << address << endl;
        cout << "Data has been added successfully" << endl;
        obj.close();
    }
    void delete_entry()
    {
        cout << "Enter the Roll_no of student :";
        cin >> roll_no;
        cin.ignore();

        ifstream file("student.txt");
        ofstream temp("temp.txt");

        int current_roll;
        bool found = false;
        while (file >> current_roll)
        {
            cin.ignore();
            getline(file, name);
            cin.ignore();
            getline(file, division);
            cin.ignore();
            getline(file, address);
            cin.ignore();

            if (current_roll != roll_no)
            {
                temp << current_roll << endl;
                temp << name << endl;
                temp << division << endl;
                temp << address << endl;
            }
            else
            {
                found = true;
            }
        }
        file.close();
        temp.close();
        remove("student.txt");
        rename("temp.txt", "student.txt");
        if (found)
        {
            cout << "Student data has been deleted successfully" << endl;
        }
        else
        {
            cout << "Student not found" << endl;
        }
    }

    void display()
    {
        cout << "Enter the Roll_no of student: ";
        cin >> roll_no;
        cin.ignore();

        ifstream file("student.txt");
        int current_roll;
        bool found = false;
        while (file >> current_roll)
        {
            cin.ignore();
            getline(file, name);
            cin.ignore();
            getline(file, division);
            cin.ignore();
            getline(file, address);
            cin.ignore();

            if (current_roll == roll_no)
            {
                cout << "Roll_no = " << roll_no << endl;
                cout << "Address = " << address << endl;
                cout << "Name = " << name << endl;
                cout << "Division = " << division << endl;
                found = true;
                break;
            }
        }
        file.close();
        if (!found)
        {
            cout << "Data with roll no enterred doesn't exixts" << endl;
        }
    }
};

int main()
{
    int choice;
    Student s;
    do
    {
        cout << "\n***** Student Information System *****" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student Information" << endl;
        cout << "5. Delete File" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            s.add_student();
            break;
        case 2:
            s.delete_entry();
            break;
        case 3:
            s.display();
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        case 5:
            remove("student.txt");
            cout << "file removed";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <cstring>
#include <string>
using namespace std;
struct student
{
    char name[30];
    char grade[4];
    char gpa[4];
    char id[5];
};
int len = 0,z=0, pos = 0, nof = 0;
int search()
{
    int found = 0, x = 0, z = 0, i = 0, c = 0;
    ifstream file;
    file.open("st1.txt", ios::in | ios::app);
    student s;
    char ID[20];
    cout << "Enter id to Search : ";
    cin.getline(ID, 16);
    if (strlen(ID) != 4 )
    {
        cout << "\nSorry, Student Not Found.........!\n";
        c++;
        return 0;
    }
    if (file.is_open())
    {
        while (file.good())
        {
            char del;
            re:
            file.read((char*)&del, 1);
            if (file.eof())
                break;
            if (del == '$')
            {
                file.seekg(1, ios::cur);
                goto re;
            }
            else
                file.seekg(-1, ios::cur);

            search:
            file.getline(s.name, 30, '|');
            file.getline(s.id, 5, '|');
            file.getline(s.grade, 4, '|');
            file.getline(s.gpa, 4, '|');

            file.seekg(1, ios::cur);
            int result = strcmp(ID, s.id);
            if (result == 0)
            {
                cout << "\n\t*----------------Student Information-----------------------*\n";
                cout << "Student Name : " << s.name << endl;
                cout << "Student id : " << s.id << endl;
                cout << "Student Grade : " << s.grade << endl;
                cout << "Student GPA : " << s.gpa << endl;
                return 1;
                found++;
            }

            if (file.eof())
                break;
        }
        if (found == 0 && x == 0)
        {
            file.close();
            file.open("st2.txt", ios::in | ios::app);
            x++;
            goto search;
        }
        if (found == 0 && x != 0 && z == 0)
        {
            file.close();
            file.open("st3.txt", ios::in | ios::app);
            z++;
            goto search;
        }
        if (found == 0 && i == 0 && x != 0 && z != 0)
        {
            file.close();
            file.open("st4.txt", ios::in | ios::app);
            i++;
            goto search;
        }
        if (found == 0 && x != 0 && z != 0 && i != 0 && c == 0)
            cout << "\nSorry, Student Not Found.........!\n";

    }
    else
        cout << "Error Can't open the file.......!\n";

    file.close();
}

int checkexist(char ID[20])
{
    int found = 0, x = 0, z = 0, i = 0, c = 0;
    ifstream file;
    file.open("st1.txt", ios::in | ios::app);
    student s;
    if (file.is_open())
    {
        while (file.good())
        {
            char del;
            re:
            file.read((char*)&del, 1);
            if (file.eof())
                break;
            if (del == '$')
            {
                file.seekg(1, ios::cur);
                goto re;
            }
            else
                file.seekg(-1, ios::cur);

            search:
            file.getline(s.name, 30, '|');
            file.getline(s.id, 5, '|');
            file.getline(s.grade, 4, '|');
            file.getline(s.gpa, 4, '|');

            file.seekg(1, ios::cur);
            int result = strcmp(ID, s.id);
            if (result == 0)
            {
                ::len = strlen(s.name) + strlen(s.id) + strlen(s.grade) + strlen(s.gpa);
                ::pos = file.tellg();
                found++;
                ::nof = 1;
                if (x > 0)
                    ::nof = 2;
                if (z > 0)
                    ::nof = 3;
                if (i > 0)
                    ::nof = 4;

                return 1;
            }

            if (file.eof())
                break;
        }
        if (found == 0 && x == 0)
        {
            file.close();
            file.open("st2.txt", ios::in | ios::app);
            x++;
            goto search;
            ::nof = 2;
        }
        if (found == 0 && x != 0 && z == 0)
        {
            file.close();
            file.open("st3.txt", ios::in | ios::app);
            z++;
            goto search;
            ::nof = 3;
        }
        if (found == 0 && i == 0 && x != 0 && z != 0)
        {
            file.close();
            file.open("st4.txt", ios::in | ios::app);
            i++;
            goto search;
            ::nof = 4;
        }
        if (found == 0 && x != 0 && z != 0 && i != 0 && c == 0)
        {
            return 0;
        }
    }
    else
    {
        cout << "Error Can't open the file.......!\n";
        return 0;
    }

    file.close();
}


void insert()
{
    ofstream file;
    student s;

    cout << "\n\t*----------------insert New Student-----------------------*\n";

    cout << "student name : "; cin.getline(s.name, 30);
    id:
    cout << "student id :";
    cin.getline(s.id, 20);
    if (strlen(s.id) != 4 || s.id[0] =='-')
    {
        cout << "\ninValid id should be 4 digits only!\n";
        goto id;
    }
    else if (checkexist(s.id) == 1 )
    {
        cout << "\nsorry, id is already existed\n";
        goto id;
    }
    grade:
    cout << "student grade :"; cin.getline(s.grade, 12);
    if (stoi(s.grade) == 1)
        file.open("st1.txt", ios::app | ios::binary);

    else if (stoi(s.grade) == 2)
        file.open("st2.txt", ios::app | ios::binary);

    else if (stoi(s.grade) == 3)
        file.open("st3.txt", ios::app | ios::binary);

    else if (stoi(s.grade) == 4)
        file.open("st4.txt", ios::app | ios::binary);
    else {
        cout << "inValid Grade (1 -> 4)\n" << endl;
        goto grade;
    }

    gpa:
    cout << "student GPA :"; cin.getline(s.gpa,16);
    if (stoi(s.gpa) < 0 || stoi(s.gpa) >4)
    {
        cout << "\ninValid Grade outof(4)\n" << endl;
        goto gpa;
    }

    file.write(s.name, strlen(s.name)); file.put('|');
    file.write(s.id, strlen(s.id)); file.put('|');
    file.write(s.grade, strlen(s.grade)); file.put('|');
    file.write(s.gpa, strlen(s.gpa)); file.put('|');
    file.put('*');

    if (!file.is_open())
        cout << "Error Can't open the file.......!\n";

    file.close();
}

void display()
{
    ifstream file;
    student s;
    int no = 1;
    string n;
    cout << "Enter Number of Student Grade to Display : ";
    grade:
    cin >> n;
    if (stoi(n) == 1)
        file.open("st1.txt", ios::in | ios::app);
    else if (stoi(n) == 2)
        file.open("st2.txt", ios::in | ios::app);
    else if (stoi(n) == 3)
        file.open("st3.txt", ios::in | ios::app);
    else if (stoi(n) == 4)
        file.open("st4.txt", ios::in | ios::app);
    else
    {
        cout << "\ninValid Grade ,Please insert valid grade (1 -> 4):  ";
        goto grade;
    }
    cout << "\n";
    cout << "\t*==================Student Information of Grade " << n << " =================================*\n\n";
    if (file.is_open())
    {
        while (file.good())
        {
            char del;
            re:
            file.read((char*)&del, 1);
            if (file.eof())
                break;
            if (del == '$')
            {
                file.seekg(1, ios::cur);
                goto re;
            }
            else
                file.seekg(-1, ios::cur);

            if(del=='$')
                file.seekg(-1, ios::cur);

            file.getline(s.name, 30, '|');
            file.getline(s.id, 5, '|');
            file.getline(s.grade, 4, '|');
            file.getline(s.gpa, 4, '|');

            file.seekg(1, ios::cur);
            char n;
            file >> n;
            if (n == ' ')
                break;
            file.seekg(-1, ios::cur);

            cout << "\n*----------------Student no " << no << " Information-------------------------*\n\n";
            cout << "Student Name.: " << s.name << endl;
            cout << "Student id.: " << s.id << endl;
            cout << "Student Grade.: " << s.grade << endl;
            cout << "Student GPA.: " << s.gpa << endl;
            no++;

            if (file.eof())
                break;
        }
    }
    else
        cout << "Error Can't open the file.......!\n";
    file.close();
}
void Delete()
{
    ofstream file;
    student s;
    re:
    if (z == 0)
    {
        cout << "Enter id of student to delete : ";
    }
    char ID[20];
    cin.getline(ID, 20);

    if (strlen(ID) != 4){
        cout << "invalid id should be (4 digits)\n";
        goto re;
    }

    if (!checkexist(ID)) {
            cout << "\nSorry, Student Not Found.........!\n";
            return;
    }
        if (nof == 1)
            file.open("st1.txt", ios::in);
        else if (nof == 2)
            file.open("st2.txt", ios::in);
        else if (nof == 3)
            file.open("st3.txt", ios::in);
        else if (nof == 4)
            file.open("st4.txt", ios::in);


    if (file.is_open())
    {
        int first = pos - (5 + len);
        file.seekp(first, ios::beg);
        int end = pos - first;
        while (end != 0)
        {
            file.put('$');
            end--;
        }
        cout << "student with id ("<<ID<<") deleted successfully\n";
    }
    else
        cout << "Error Can't open the file.......!\n";

    file.close();
}

void update()
{
    ifstream ifile;
    ofstream ofile;
    student s;
    int a = 0;
    z++;
    cout << "Enter id of student to update : ";
    char ID[20];
    //cin.ignore();
    cin.getline(ID, 20);
    if (strlen(ID) != 4)
        cout << "invalid id should be (4 digits)\n";

    if (checkexist(ID))
    {
        if (nof == 1)
        {
            ifile.open("st1.txt", ios::in);
            ofile.open("st1.txt", ios::in | ios::app);
        }
        else if (nof == 2)
        {
            ifile.open("st2.txt", ios::in);
            ofile.open("st1.txt", ios::in | ios::app);

        }
        else if (nof == 3)
        {
            ifile.open("st3.txt", ios::in);
            ofile.open("st3.txt", ios::in | ios::app);
        }
        else if (nof == 4)
        {
            ifile.open("st4.txt", ios::in);
            ofile.open("st4.txt", ios::in | ios::app);
        }
    }
    else
    {
        cout << "\nSorry, Student Not Found.........!\n";
        a++;
        ifile.close();
        ofile.close();
        return;
    }

    int first = pos - (5 + len);
    ifile.seekg(first, ios::beg);
    ifile.getline(s.name, 30, '|');
    ifile.getline(s.id, 5, '|');
    ifile.getline(s.grade, 4, '|');
    ifile.getline(s.gpa, 4, '|');
    if (a == 0)
    {
        cout << "\nInformation of Student you want to Update\n";
        cout << "Student Name.: " << s.name << endl;
        cout << "Student id.: " << s.id << endl;
        cout << "Student Grade.: " << s.grade << endl;
        cout << "Student GPA.: " << s.gpa << endl;
        cout << "\nSubmit id to Update: ";
        Delete();
        insert();
    }
    z = 0;

    ifile.close();
    ofile.close();
}

int main() {
    int choice;
    while (1) {
        cout<<"\n\n";
        cout << "1. Add Student Record\n";
        cout << "2. Modify Student Record\n";
        cout << "3. Search Student Record\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Display Students Record\n";
        cout << "6. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                update();
                break;
            case 3:
                search();
                break;
            case 4:
                Delete();
                break;
            case 5:
                display();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}


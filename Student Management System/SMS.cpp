#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

const int size = 500;

class Student
{
public:
    string name;
    string program;
    int rollno;
    float cgpa;
    string cnic;
    string phone;

    void show_all_students(Student s[], int currentSize);
    void search_by_rollno(Student s[], int rollno, int currentSize);
    void find_max_cgpa(Student s[], int currentSize);
    void sortby_name(Student s[], int currentSize);
    void sortby_cgpa(Student s[], int currentSize);
    void add_new_student(Student s[], int &currentSize);
    void save_students_to_file(Student s[], int currentSize, const string &filename);
};

void Student::show_all_students(Student s[], int currentSize)
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name of the student: " << s[i].name << '\t'
             << "Cnic of the Student: " << s[i].cnic << '\t'
             << "Roll no of the student: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Degree Program: " << s[i].program << '\t'
             << "Phone Number of the student: " << s[i].phone << endl;
    }
}

void Student::search_by_rollno(Student s[], int rollno, int currentSize)
{
    bool found = false;
    for (int i = 0; i < currentSize; i++)
    {
        if (s[i].rollno == rollno)
        {
            found = true;
            cout << "Name of the student: " << s[i].name << '\t'
                 << "Cnic of the Student: " << s[i].cnic << '\t'
                 << "Roll no of the student: " << s[i].rollno << '\t'
                 << "CGPA: " << s[i].cgpa << '\t'
                 << "Degree Program: " << s[i].program << '\t'
                 << "Phone Number of the student: " << s[i].phone << endl;
        }
    }
    if (!found)
    {
        cout << "Student with the following roll no is not found!" << endl;
    }
}

void Student::find_max_cgpa(Student s[], int currentSize)
{
    float max_cgpa = s[0].cgpa;
    int index = 0;
    for (int i = 1; i < currentSize; i++)
    {
        if (s[i].cgpa > max_cgpa)
        {
            max_cgpa = s[i].cgpa;
            index = i;
        }
    }
    cout << "Student with the maximum CGPA is: " << endl;
    cout << "Name of the student: " << s[index].name << '\t'
         << "Cnic of the Student: " << s[index].cnic << '\t'
         << "Roll no of the student: " << s[index].rollno << '\t'
         << "CGPA: " << s[index].cgpa << '\t'
         << "Degree Program: " << s[index].program << '\t'
         << "Phone Number of the student: " << s[index].phone << endl;
}

void Student::sortby_name(Student s[], int currentSize)
{
    // Bubble Sort
    for (int i = 0; i < currentSize - 1; i++)
    {
        for (int j = 0; j < currentSize - i - 1; j++)
        {
            if (s[j].name > s[j + 1].name)
            {
                // swap the elements
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
    cout << "Students sorted by name are: " << endl;
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name of the student: " << s[i].name << '\t'
             << "Cnic of the Student: " << s[i].cnic << '\t'
             << "Roll no of the student: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Degree Program: " << s[i].program << '\t'
             << "Phone Number of the student: " << s[i].phone << endl;
    }
}

void Student::sortby_cgpa(Student s[], int currentSize)
{
    // selection sort
    for (int i = 0; i < currentSize - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < currentSize; j++)
        {
            if (s[j].cgpa > s[min_index].cgpa)
            {
                min_index = j;
            }
        }
        // swap elements
        Student temp = s[min_index];
        s[min_index] = s[i];
        s[i] = temp;
    }
    cout << "Students with sorted CGPA's are: " << endl;
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name of the student: " << s[i].name << '\t'
             << "Cnic of the Student: " << s[i].cnic << '\t'
             << "Roll no of the student: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Degree Program: " << s[i].program << '\t'
             << "Phone Number of the student: " << s[i].phone << endl;
    }
}

void Student::add_new_student(Student s[], int &currentSize)
{
    if (currentSize >= size)
    {
        cout << "Can not add students!" << endl;
        return;
    }
    Student newStudent;
    cout << "Enter the name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter the Cnic: ";
    getline(cin, newStudent.cnic);
    cout << "Enter the roll no: ";
    cin >> newStudent.rollno;
    cout << "Enter the Cgpa: ";
    cin >> newStudent.cgpa;
    cout << "Enter the degree program(Bs/Ms): ";
    cin.ignore();
    getline(cin, newStudent.program);
    cout << "Enter the phone number: ";
    getline(cin, newStudent.phone);
    s[currentSize] = newStudent;
    currentSize++;
    cout << "Student has been added successfully!" << endl;
}

void Student::save_students_to_file(Student s[], int currentSize, const string &filename)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cout << "Unable to open the file for writing!" << endl;
        return;
    }
    outfile << "Name\tCNIC\tRollNo\tCGPA\tProgram\tPhone" << endl;
    for (int i = 0; i < currentSize; i++)
    {
        outfile << s[i].name << '\t'
                << s[i].cnic << '\t'
                << s[i].rollno << '\t'
                << s[i].cgpa << '\t'
                << s[i].program << '\t'
                << s[i].phone << endl;
    }
    outfile.close();
    cout << "Students have been saved successfully!" << endl;
}

int main()
{
    Student s[size];
    ifstream infile("Student.txt");
    string line;
    int currentSize = 0;
    while (getline(infile, line) && currentSize < size)
    {
        stringstream ss(line);
        string name, cnic, program, phone;
        int rollno;
        float cgpa;
        ss >> name >> cnic >> rollno >> cgpa >> program >> phone;
        s[currentSize].name = name;
        s[currentSize].cnic = cnic;
        s[currentSize].rollno = rollno;
        s[currentSize].cgpa = cgpa;
        s[currentSize].program = program;
        s[currentSize].phone = phone;
        currentSize++;
    }
    infile.close();
    int choice;
    do
    {
        cout << "--------MENU--------" << endl;
        cout << "1. Show All Students" << endl;
        cout << "2. Search a student by roll no" << endl;
        cout << "3. Find the student with max CGPA" << endl;
        cout << "4. Sort the students by name" << endl;
        cout << "5. Sort the students by CGPA" << endl;
        cout << "6. Add a new student" << endl;
        cout << "7. Save the students to the file" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            s[0].show_all_students(s, currentSize);
            break;
        case 2:
        {
            int rollno;
            cout << "Enter the roll no to be searched: " << endl;
            cin >> rollno;
            s[0].search_by_rollno(s, rollno, currentSize);
            break;
        }
        case 3:
            s[0].find_max_cgpa(s, currentSize);
            break;
        case 4:
            s[0].sortby_name(s, currentSize);
            break;
        case 5:
            s[0].sortby_cgpa(s, currentSize);
            break;
        case 6:
            s[0].add_new_student(s, currentSize);
            break;
        case 7:
            s[0].save_students_to_file(s, currentSize, "Student.txt");
            break;
        case 8:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (choice != 8);
    return 0;
}

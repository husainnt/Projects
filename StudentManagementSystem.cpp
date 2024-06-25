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
    void find_max_cgpa_stud(Student s[], int currentSize);
    void sortby_name(Student s[], int currentSize);
    void sortby_cgpa(Student s[], int currentSize);
    void add_new_student(Student s[], int &currentSize);
    void save_students_to_file(Student s[], int currentSize, const string &filename);
};

void Student::show_all_students(Student s[], int currentSize)
{
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name of student: " << s[i].name << '\t'
             << "Cnic of student: " << s[i].cnic << '\t'
             << "Rollno of student: " << s[i].rollno << '\t'
             << "CGPA of student: " << s[i].cgpa << '\t'
             << "Degree program of student: " << s[i].program << '\t'
             << "Phone number of student: " << s[i].phone << endl;
    }
}

void Student::search_by_rollno(Student s[], int rollno, int currentSize)
{
    bool found = false;
    for (int i = 0; i < currentSize; i++)
    {
        if (s[i].rollno == rollno)
        {
            cout << "Name of student: " << s[i].name << '\t'
                 << "Cnic of student: " << s[i].cnic << '\t'
                 << "Rollno of student: " << s[i].rollno << '\t'
                 << "CGPA of student: " << s[i].cgpa << '\t'
                 << "Degree program of student: " << s[i].program << '\t'
                 << "Phone number of student: " << s[i].phone << endl;
            found = true;
            break; // Exit the loop once found
        }
    }

    if (!found)
    {
        cout << "Student not found with roll number: " << rollno << endl;
    }
}

void Student::find_max_cgpa_stud(Student s[], int currentSize)
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

    cout << "Student with maximum CGPA:" << endl;
    cout << "Name: " << s[index].name << '\t'
         << "Cnic: " << s[index].cnic << '\t'
         << "Roll No: " << s[index].rollno << '\t'
         << "CGPA: " << s[index].cgpa << '\t'
         << "Program: " << s[index].program << '\t'
         << "Phone: " << s[index].phone << endl;
}

void Student::sortby_name(Student s[], int currentSize)
{
    // Bubble sort by name
    for (int i = 0; i < currentSize - 1; i++)
    {
        for (int j = 0; j < currentSize - i - 1; j++)
        {
            if (s[j].name > s[j + 1].name)
            {
               swap(s[j],s[j+1]);
            }
        }
    }

    cout << "Students sorted by name:" << endl;
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name: " << s[i].name << '\t'
             << "Cnic: " << s[i].cnic << '\t'
             << "Roll No: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Program: " << s[i].program << '\t'
             << "Phone: " << s[i].phone << endl;
    }
}

void Student::sortby_cgpa(Student s[], int currentSize)
{
    // Selection sort by CGPA
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
        // Swap elements
       swap(s[i],s[min_index]);
    }

    cout << "Students sorted by CGPA:" << endl;
    for (int i = 0; i < currentSize; i++)
    {
        cout << "Name: " << s[i].name << '\t'
             << "Cnic: " << s[i].cnic << '\t'
             << "Roll No: " << s[i].rollno << '\t'
             << "CGPA: " << s[i].cgpa << '\t'
             << "Program: " << s[i].program << '\t'
             << "Phone: " << s[i].phone << endl;
    }
}

void Student::add_new_student(Student s[], int &currentSize)
{
    if (currentSize >= size)
    {
        cout << "Cannot add more students, array is full." << endl;
        return;
    }

    Student newStudent;
    cout << "Enter name: ";
    cin >> newStudent.name;
    cout << "Enter CNIC: ";
    cin >> newStudent.cnic;
    cout << "Enter roll number: ";
    cin >> newStudent.rollno;
    cout << "Enter CGPA: ";
    cin >> newStudent.cgpa;
    cout << "Enter degree program: ";
    cin >> newStudent.program;
    cout << "Enter phone number: ";
    cin >> newStudent.phone;

    s[currentSize] = newStudent;
    currentSize++;

    cout << "Student added successfully." << endl;
}

void Student::save_students_to_file(Student s[], int currentSize, const string &filename)
{
    ofstream outfile(filename);
    if (!outfile)
    {
        cout << "Unable to open file for writing!" << endl;
        return;
    }

    outfile << "Name\tCNIC\tRoll No\tCGPA\tProgram\tPhone" << endl; // Header

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
    cout << "Students saved to file successfully." << endl;
}

int main()
{
    Student s[size];                // Array of Student objects
    ifstream infile("Student.txt"); // Open the input file

    if (!infile)
    {
        cout << "Unable to open file!" << endl;
        return 1; // Exit if file opening fails
    }

    string line;
    getline(infile, line); // Read the header line and discard it

    int currentSize = 0;
    while (getline(infile, line) && currentSize < size)
    {
        stringstream ss(line);
        string name, cnic, program, phone;
        int rollno;
        float cgpa;

        ss >> name >> cnic >> rollno >> cgpa >> program >> phone;

        // Store the data in the array of Student objects
        s[currentSize].name = name;
        s[currentSize].cnic = cnic;
        s[currentSize].rollno = rollno;
        s[currentSize].cgpa = cgpa;
        s[currentSize].program = program;
        s[currentSize].phone = phone;

        currentSize++; // Increment index to move to the next student
    }

    infile.close(); // Close the file

    // Menu-driven program
    int choice;
    do
    {
        cout << "===== MENU =====" << endl;
        cout << "1. Show all students" << endl;
        cout << "2. Search by roll number" << endl;
        cout << "3. Find student with maximum CGPA" << endl;
        cout << "4. Sort students by name" << endl;
        cout << "5. Sort students by CGPA" << endl;
        cout << "6. Add new student" << endl;
        cout << "7. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s[0].show_all_students(s, currentSize);
            break;
        case 2:
        {
            int rollno;
            cout << "Enter roll number: ";
            cin >> rollno;
            s[0].search_by_rollno(s, rollno, currentSize);
            break;
        }
        case 3:
            s[0].find_max_cgpa_stud(s, currentSize);
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
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

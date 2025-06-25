#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class student
{
public:
    int rollno;
    char name[50];
    float mark[5];
    float average;
    float total;
    char grade;

    void input();
    void calculate();
    void display();
};

void student::input()
{
    cout << "Enter roll number: ";
    cin >> rollno;
    cin.ignore();

    cout << "Enter name: ";
    cin.getline(name, 50);

    cout << "Enter 5 subject marks: " << endl;
    for (int i = 0; i < 5; i++)
    {

        cout << "Subject " << (i + 1) << ": ";
        cin >> mark[i];
        if (mark[i] > 100 || mark[i] < 0)
        {
            i--;
        }
    }
}

void student::calculate()
{
    total = 0;
    for (int i = 0; i < 5; i++)
        total += mark[i];

    average = total / 5;

    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 60)
        grade = 'C';
    else if (average >= 40)
        grade = 'D';
    else
        grade = 'F'; // Capital F for consistency
}

void student::display()
{

    char arr[5] = {};
    cout << "\n--- Report Card ---\n";
    cout << "Roll Number: " << rollno << endl;
    cout << "Name: " << name << endl;
    cout << "Marks:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "Subject " << (i + 1) << ": " << mark[i];
        if (mark[i] >= 33)
        {
            arr[i] = 'P';
            cout << "  " << arr[i] << endl;
        }
        else
        {
            arr[i] = 'F';
            cout << "  " << arr[i] << endl;
        }
    }

    cout << "Total: " << total << endl;
    cout << "Average: " << average << endl;
    cout << "Grade: " << grade << endl;
}

int fileRead(student s[], int count)
{
    ifstream infile("report.txt");
    if (infile.is_open())
    {
        while (infile >> s[count].rollno)
        {
            infile.ignore();

            infile.getline(s[count].name, 50);

            for (int i = 0; i < 5; i++)
                infile >> s[count].mark[i];

            infile >> s[count].average >> s[count].grade;
            s[count].total = s[count].average * 5;
            count++;
        }
        infile.close();
    }
    return count;
}

int main()
{
    student s[100];
    int count = 0;
    int choice;

    // File Read
    count = fileRead(s, count);

    do
    {
        cout << "\n--- Student Report Card Menu ---\n";
        cout << "1. Add new student\n";
        cout << "2. Display all students\n";
        cout << "3. search by rollNumber " << endl;
        cout << "4  Total number of record " << endl;
        cout << "5. Delete Student Record " << endl;
        cout << "6. update Student Record " << endl;
        cout << "7. Sort Student Record " << endl;
        cout << "8. Export csv file " << endl;
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s[count].input();
            s[count].calculate();

            // Save to file in correct format
            {
                ofstream file("report.txt", ios::app); // writing
                if (file.is_open())
                {
                    file << s[count].rollno << endl;
                    file << s[count].name << endl;
                    for (int i = 0; i < 5; i++)
                        file << s[count].mark[i] << " ";
                    file << endl;
                    file << s[count].average << " " << s[count].grade << endl;
                    file.close();
                    cout << "Student Added Successfully" << endl;
                }
                else
                {
                    cout << "Error opening file for writing." << endl;
                }
            }
            count++;
            break;

        case 2:
            if (count == 0)
                cout << "No student records found.\n";
            else
            {
                for (int i = 0; i < count; i++)
                    s[i].display();
            }
            break;

            // searching record by roll number
        case 3:
        {

            int searchrollno;
            cout << "Enter Roll Number for search: ";
            cin >> searchrollno;
            bool found = false;

            int c = 0;

            ifstream roll("report.txt");

            if (roll.is_open())
            {

                while (roll >> s[c].rollno)
                {
                    roll.ignore();
                    roll.getline(s[c].name, 50);

                    for (int i = 0; i < 5; i++)
                    {
                        roll >> s[c].mark[i];
                    }

                    roll >> s[c].average >> s[c].grade;
                    s[c].total = s[c].average * 5;

                    if (searchrollno == s[c].rollno)
                    {
                        s[c].display();
                        found = true;
                        break;
                    }
                    c++;
                }
                if (found != true)
                {
                    cout << "student not found for " << searchrollno << " roll number" << endl;
                }
                roll.close();
            }
            else
            {
                cout << "unable to open a file " << endl;
            }
            break;
        }

        case 4:
        {
            int tempcount = 0;
            tempcount = fileRead(s, tempcount);
            cout << " total number of student record: " << tempcount << endl;
            break;
        }

        case 5:
        {
            int delroll;
            cout << " Enter Roll Number to delete record ";
            cin >> delroll;
            int counter = 0;
            bool deleted = false;
            ofstream temp("temp.txt", ios::out);

            counter = fileRead(s, counter);

            for (int i = 0; i < counter; i++)
            {

                if (delroll == s[i].rollno)
                {
                    deleted = true;
                    continue;
                }

                else
                {

                    temp << s[i].rollno << endl;
                    temp << s[i].name << endl;
                    for (int j = 0; j < 5; j++)
                        temp << s[i].mark[j] << " ";
                    temp << endl;
                    temp << s[i].average << " " << s[i].grade << endl;
                }
            }
            temp.close();

            if (deleted)
            {
                remove("report.txt");
                rename("temp.txt", "report.txt");
                cout << "Record deleted successfully.\n";
            }
            else
                cout << "Roll number not found.\n";

            break;
        }

        case 6:
        {
            int updateroll;
            cout << "enter the roll  number : ";
            cin >> updateroll;
            bool updated = false;
            int counter = 0;
            counter = fileRead(s, counter);

            ofstream temp("temp.txt", ios::out);

            for (int i = 0; i < counter; i++)
            {

                if (s[i].rollno == updateroll)
                {
                    updated = true;
                    s[i].input();
                    s[i].calculate();

                    temp << s[i].rollno << endl;
                    temp << s[i].name << endl;
                    for (int j = 0; j < 5; j++)
                        temp << s[i].mark[j] << " ";
                    temp << endl;
                    temp << s[i].average << " " << s[i].grade << endl;
                }

                else
                {

                    temp << s[i].rollno << endl;
                    temp << s[i].name << endl;
                    for (int j = 0; j < 5; j++)
                        temp << s[i].mark[j] << " ";
                    temp << endl;
                    temp << s[i].average << " " << s[i].grade << endl;
                }
            }
            temp.close();

            if (updated)
            {
                remove("report.txt");
                rename("temp.txt", "report.txt");
                cout << " record update successfully " << endl;
            }
            else
            {
                cout << " record not found " << endl;
            }
            break;
        }

        case 7:
        {

            int record = 0;
            record = fileRead(s, record);
            int option;
            cout << "1. sorting by roll number" << endl;
            cout << "2. sorting by average" << endl;
            cout << "3. sorting by name" << endl;
            cout << "enter : ";

            cin >> option;

            switch (option)
            {
            case 1:
            {

                for (int i = 0; i < record - 1; i++)
                {
                    for (int j = i + 1; j < record; j++)
                    {
                        if (s[i].rollno > s[j].rollno)
                        {
                            swap(s[i], s[j]);
                        }
                    }
                }

                for (int i = 0; i < record; i++)
                {
                    s[i].display();
                }
                break;
            }

            case 2:
            {

                for (int i = 0; i < record - 1; i++)
                {
                    for (int j = i + 1; j < record; j++)
                    {
                        if (s[i].average < s[j].average)
                        {
                            swap(s[i], s[j]);
                        }
                    }
                }

                for (int i = 0; i < record; i++)
                {
                    s[i].display();
                }
                break;
            }

            case 3:
            {

                for (int i = 0; i < record - 1; i++)
                {
                    for (int j = i + 1; j < record; j++)
                    {
                        if (strcmp(s[i].name, s[j].name) > 0)
                        {
                            swap(s[i], s[j]);
                        }
                    }
                }

                for (int i = 0; i < record; i++)
                {
                    s[i].display();
                }
                break;
            }
            }
            break;
        }
        case 8:
        {

            int totalrecord = 0;
            totalrecord = fileRead(s, totalrecord);

            ofstream csvfile("report.csv");

            if (csvfile.is_open())
            {
                csvfile << "RollNo,Name,Subject1,Subject2,Subject3,Subject4,Subject5,Total,Average,Grade\n";

                for (int i = 0; i < totalrecord; i++)
                {

                    csvfile << s[i].rollno << ",";
                    csvfile << s[i].name << ",";

                    for (int j = 0; j < 5; j++)
                    {
                        csvfile << s[i].mark[j] << ",";
                    }

                    csvfile << s[i].total << ",";
                    csvfile << s[i].average << ",";
                    csvfile << s[i].grade << "\n";
                }

                csvfile.close();

                cout << "Data exported successfully to report.csv\n";
            }
            else
            {
                cout << "Error: Could not open CSV file for writing.\n";
            }
            break;
        }

        case 9:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <random>

#include "person.h"
#include "studentprocessor.h"

using namespace std;



Person generateRandomStudent(int numberOfHomework) {
    static random_device rd;
    static mt19937 generator(rd());
    uniform_int_distribution<int> gradeDistribution(1, 10);
    vector<string> names = {
        "John", "Anna", "Mark", "Laura", "David",
        "Emma", "Michael", "Sofia", "Daniel", "Olivia"
    };
    vector<string> surnames = {
        "Smith", "Johnson", "Brown", "Taylor", "Wilson",
        "Anderson", "Thomas", "Moore", "Martin", "Clark"
    };
    uniform_int_distribution<int> nameDistribution(
        0, static_cast<int>(names.size()) - 1
    );
    string name = names[nameDistribution(generator)];
    string surname = surnames[nameDistribution(generator)];
    vector<int> homework;
    for (int i = 0; i < numberOfHomework; i++) {
        homework.push_back(gradeDistribution(generator));
    }
    int exam = gradeDistribution(generator);
    return Person(name, surname, homework, exam);
}
void displayResults(const vector<Person>& students) {
    cout << "\n";
    cout << left
         << setw(15) << "Name"
         << setw(15) << "Surname"
         << setw(15) << "Final (Avg.)"
         << setw(15) << "Final (Med.)"
         << "\n";
    cout << string(60, '-') << "\n";
    for (const Person& student : students) {
        cout << left
             << setw(15) << student.getName()
             << setw(15) << student.getSurname()
             << fixed << setprecision(2)
             << setw(15) << student.calculateAverage()
             << setw(15) << student.calculateMedian()
             << "\n";
    }
    cout << "\n";
}
void enterStudents(vector<Person>& students) {
    int numberOfStudents;
    cout << "\nHow many students do you want to enter? ";
    cin >> numberOfStudents;
    for (int i = 0; i < numberOfStudents; i++) {
        string name;
        string surname;
        cout << "\nStudent " << i + 1 << "\n";
        cout << "Name: ";
        cin >> name;
        cout << "Surname: ";
        cin >> surname;
        vector<int> homework;
        cout << "Enter homework grades one by one.\n";
        cout << "Enter -1 when finished.\n";
        while (true) {
            int grade;
            cout << "Homework grade: ";
            cin >> grade;
            if (grade == -1)
                break;
            if (grade >= 0 && grade <= 10) {
                homework.push_back(grade);
            }
            else {
                cout << "Grade must be between 0 and 10.\n";
            }
        }
        int exam;
        do {
            cout << "Exam grade: ";
            cin >> exam;
            if (exam < 0 || exam > 10)
                cout << "Grade must be between 0 and 10.\n";
        } while (exam < 0 || exam > 10);
        students.emplace_back(
            name, surname, homework, exam
        );
    }
}
void generateStudents(vector<Person>& students) {
    int numberOfStudents;
    int numberOfHomework;
    cout << "\nHow many students? ";
    cin >> numberOfStudents;
    cout << "How many homework assignments? ";
    cin >> numberOfHomework;
    if (numberOfStudents <= 0 || numberOfHomework <= 0) {
        cout << "Invalid number.\n";
        return;
    }
    students.clear();
    for (int i = 0; i < numberOfStudents; i++) {
        students.push_back(
            generateRandomStudent(numberOfHomework)
        );
    }
    cout << "\nRandom data generated successfully.\n";
}
bool readFromFile(vector<Person>& students) {
    try {
        StudentProcessor::readFromFile(students, "students.txt");
        cout << "\nStudents loaded successfully.\n";
        return true;
    }
    catch (const exception& e) {
        cout << "\nError: " << e.what() << "\n";
        return false;
    }
}
int main() {
    vector<Person> students;
    int choice;
    cout << "Student Final Grade Calculator\n";
    cout << "==============================\n";
    cout << "\n1. Enter students manually\n";
    cout << "2. Generate random students\n";
    cout << "3. Read students from Students.txt\n";
    cout << "\nChoose an option: ";
    cin >> choice;
    if (choice == 1) {
        enterStudents(students);
    }
    else if (choice == 2) {
        generateStudents(students);
    }
    else if (choice == 3) {
        if (!readFromFile(students))
            return 1;
    }
    else {
        cout << "Invalid choice.\n";
        return 1;
    }
   StudentProcessor::sortStudents(students);
    if (!students.empty())
        displayResults(students);
    else
        cout << "\nNo students to display.\n";
    return 0;
}
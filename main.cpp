#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <random>
using namespace std;
class Person {
private:
    string name;
    string surname;
    vector<int> homework;
    int exam;
    double finalGrade;
public:
    Person() : name(""), surname(""), exam(0), finalGrade(0.0) {}
    Person(const string& n, const string& s,
           const vector<int>& hw, int e)
        : name(n), surname(s), homework(hw),
          exam(e), finalGrade(0.0) {}
    // Rule of Three
    Person(const Person& other)
        : name(other.name),
          surname(other.surname),
          homework(other.homework),
          exam(other.exam),
          finalGrade(other.finalGrade) {}
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            surname = other.surname;
            homework = other.homework;
            exam = other.exam;
            finalGrade = other.finalGrade;
        }
        return *this;
    }
    ~Person() {}
    double calculateAverage() const {
        if (homework.empty())
            return exam;
        double sum = accumulate(
            homework.begin(),
            homework.end(),
            0.0
        );
        double average = sum / homework.size();
        return 0.4 * average + 0.6 * exam;
    }
    double calculateMedian() const {
        if (homework.empty())
            return exam;
        vector<int> sortedHomework = homework;
        sort(sortedHomework.begin(), sortedHomework.end());
        double median;
        if (sortedHomework.size() % 2 == 0) {
            int middle1 =
                sortedHomework[sortedHomework.size() / 2 - 1];
            int middle2 =
                sortedHomework[sortedHomework.size() / 2];
            median = (middle1 + middle2) / 2.0;
        }
        else {
            median = sortedHomework[sortedHomework.size() / 2];
        }
        return 0.4 * median + 0.6 * exam;
    }
    string getName() const {
        return name;
    }
    string getSurname() const {
        return surname;
    }
    friend istream& operator>>(istream& in, Person& student) {
        in >> student.name >> student.surname;
        int numberOfHomework;
        in >> numberOfHomework;
        student.homework.clear();
        for (int i = 0; i < numberOfHomework; i++) {
            int grade;
            in >> grade;
            student.homework.push_back(grade);
        }
        in >> student.exam;
        return in;
    }
    friend ostream& operator<<(ostream& out,
                               const Person& student) {
        out << left
            << setw(15) << student.name
            << setw(15) << student.surname
            << fixed << setprecision(2)
            << student.calculateAverage();
        return out;
    }
};
bool compareStudents(const Person& a, const Person& b) {
    if (a.getSurname() == b.getSurname())
        return a.getName() < b.getName();
    return a.getSurname() < b.getSurname();
}
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
    ifstream file("Students.txt");
    if (!file.is_open()) {
        cout << "\nCould not open Students.txt.\n";
        return false;
    }
    students.clear();
    Person student;
    while (file >> student) {
        students.push_back(student);
    }
    file.close();
    cout << "\nStudents loaded successfully.\n";
    return true;
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
    sort(
        students.begin(),
        students.end(),
        compareStudents
    );
    if (!students.empty())
        displayResults(students);
    else
        cout << "\nNo students to display.\n";
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm> 

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    double grade;

    Student(int id, const string& name, int age, double grade)
        : id(id), name(name), age(age), grade(grade) {
    }

    void display() const {
        cout << id << ", " << name << ", " << age << ", " << grade << endl;
    }
};

vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return students;
    }

    string line;
    getline(file, line);  // Skip the header line

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string item;

        int id, age;
        string name;
        double grade;

        getline(ss, item, ',');
        id = stoi(item);

        getline(ss, item, ',');
        name = item;

        getline(ss, item, ',');
        age = stoi(item);

        getline(ss, item, ',');
        grade = stod(item);

        students.emplace_back(id, name, age, grade);
    }

    file.close();
    return students;
}
void searchStudentByName(const vector<Student>& students, const string& searchName) {
    bool found = false;

    for (const auto& student : students) {
        if (student.name.find(searchName) != string::npos) {
            cout << student.id << ", " << student.name << ", " << student.age << ", " << student.grade << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No student found with name containing \"" << searchName << "\"." << endl;
    }
}
void sortStudents(vector<Student>& students, const string& field, bool ascending) {
    if (field == "age") {
        sort(students.begin(), students.end(), [ascending](const Student& a, const Student& b) {
            return ascending ? a.age < b.age : a.age > b.age;
            });
    }
    else if (field == "grade") {
        sort(students.begin(), students.end(), [ascending](const Student& a, const Student& b) {
            return ascending ? a.grade < b.grade : a.grade > b.grade;
            });
    }
    else {
        cout << "Invalid sort field." << endl;
    }
}
void calculateGradeStats(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records to analyze.\n";
        return;
    }

    double total = 0;
    double highest = students[0].grade;
    double lowest = students[0].grade;
    int passCount = 0;

    for (const auto& student : students) {
        total += student.grade;

        if (student.grade > highest)
            highest = student.grade;

        if (student.grade < lowest)
            lowest = student.grade;

        if (student.grade >= 50)
            passCount++;
    }

    double average = total / students.size();

    cout << "\nGrade Statistics:\n";
    cout << "------------------\n";
    cout << "Average Grade: " << average << endl;
    cout << "Highest Grade: " << highest << endl;
    cout << "Lowest Grade : " << lowest << endl;
    cout << "Students Passed (>= 50): " << passCount << endl;
}

void saveResultsToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file to save results.\n";
        return;
    }

    // Write header
    file << "ID, Name, Age, Grade\n";

    // Write each student record
    for (const auto& student : students) {
        file << student.id << ", "
            << student.name << ", "
            << student.age << ", "
            << student.grade << "\n";
    }

    // Calculate statistics
    if (!students.empty()) {
        double total = 0;
        double highest = students[0].grade;
        double lowest = students[0].grade;
        int passCount = 0;

        for (const auto& student : students) {
            total += student.grade;
            if (student.grade > highest) highest = student.grade;
            if (student.grade < lowest) lowest = student.grade;
            if (student.grade >= 50) passCount++;
        }

        double average = total / students.size();

        // Write stats
        file << "\nGrade Statistics:\n";
        file << "------------------\n";
        file << "Average Grade: " << average << "\n";
        file << "Highest Grade: " << highest << "\n";
        file << "Lowest Grade : " << lowest << "\n";
        file << "Students Passed (>= 50): " << passCount << "\n";
    }

    file.close();
    cout << "\nResults saved to '" << filename << "' successfully.\n";
}



int main() {

    string filename;
    cout << "Enter filename:";
    cin >> filename;
    vector<Student> students = readStudentsFromFile(filename);

    if (students.empty()) {
        cout << "No records found or unable to read the file." << endl;
        return 1;
    }

    cout << "\nDisplaying Student Records:\n";
    for (const auto& student : students) {
        student.display();
    }
    string searchTerm;
    cout << "\nEnter student name to search: ";
    cin.ignore();            // Clear input buffer
    getline(cin, searchTerm);

    searchStudentByName(students, searchTerm);


    string field, order;

    cout << "\nSort by 'age' or 'grade': ";
    cin >> field;

    cout << "Order 'asc' for ascending or 'desc' for descending: ";
    cin >> order;

    bool ascending = (order == "asc");
    sortStudents(students, field, ascending);

    cout << "\nSorted Student Records:\n";
    for (const auto& student : students) {
        cout << student.id << ", " << student.name << ", " << student.age << ", " << student.grade << endl;
    }
    calculateGradeStats(students);
    saveResultsToFile(students, "results.txt");



    return 0;
}


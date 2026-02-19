#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    double grade;

public:
    Student(int id, const string& name, int age, double grade)
        : id(id), name(name), age(age), grade(grade) {
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    double getGrade() const { return grade; }

    void display() const {
        cout << id << ", " << name << ", " << age << ", " << grade << endl;
    }

    // Operator overloads for sorting
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

class DataAnalyzer {
private:
    vector<Student> students;

public:
    bool readFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not open file: " << filename << endl;
            return false;
        }

        students.clear();
        string line;
        getline(file, line); // Skip header

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string item;

            int id, age;
            string name;
            double grade;

            getline(ss, item, ','); id = stoi(item);
            getline(ss, item, ','); name = item;
            if (!name.empty() && name.front() == ' ') name.erase(0, 1);
            getline(ss, item, ','); age = stoi(item);
            getline(ss, item, ','); grade = stod(item);

            students.emplace_back(id, name, age, grade);
        }

        return true;
    }

    void displayAll() const {
        for (const auto& student : students) {
            student.display();
        }
    }

    void searchByName(const string& searchName) const {
        bool found = false;
        for (const auto& student : students) {
            if (student.getName().find(searchName) != string::npos) {
                student.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No student found with name containing '" << searchName << "'." << endl;
        }
    }

    void sortBy(const string& field, bool ascending = true) {
        if (field == "age") {
            sort(students.begin(), students.end(), [ascending](const Student& a, const Student& b) {
                return ascending ? a.getAge() < b.getAge() : a.getAge() > b.getAge();
                });
        }
        else if (field == "grade") {
            sort(students.begin(), students.end(), [ascending](const Student& a, const Student& b) {
                return ascending ? a.getGrade() < b.getGrade() : a.getGrade() > b.getGrade();
                });
        }
    }

    void displayStatistics() const {
        if (students.empty()) {
            cout << "No records to analyze.\n";
            return;
        }

        double total = 0, highest = students[0].getGrade(), lowest = students[0].getGrade();
        int passCount = 0;

        for (const auto& student : students) {
            double g = student.getGrade();
            total += g;
            if (g > highest) highest = g;
            if (g < lowest) lowest = g;
            if (g >= 50) passCount++;
        }

        double average = total / students.size();

        cout << "\nGrade Statistics:\n";
        cout << "------------------\n";
        cout << "Average Grade: " << average << endl;
        cout << "Highest Grade: " << highest << endl;
        cout << "Lowest Grade : " << lowest << endl;
        cout << "Students Passed (>= 50): " << passCount << endl;
    }

    void saveResults(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file to save results.\n";
            return;
        }

        file << "ID, Name, Age, Grade\n";
        for (const auto& student : students) {
            file << student.getId() << ", " << student.getName() << ", "
                << student.getAge() << ", " << student.getGrade() << "\n";
        }

        // Write stats
        if (!students.empty()) {
            double total = 0, highest = students[0].getGrade(), lowest = students[0].getGrade();
            int passCount = 0;

            for (const auto& student : students) {
                double g = student.getGrade();
                total += g;
                if (g > highest) highest = g;
                if (g < lowest) lowest = g;
                if (g >= 50) passCount++;
            }

            double average = total / students.size();

            file << "\nGrade Statistics:\n";
            file << "------------------\n";
            file << "Average Grade: " << average << "\n";
            file << "Highest Grade: " << highest << "\n";
            file << "Lowest Grade : " << lowest << "\n";
            file << "Students Passed (>= 50): " << passCount << "\n";
        }

        file.close();
        cout << "\nResults saved to '" << filename << "'.\n";
    }
};

int main() {
    DataAnalyzer analyzer;
    string filename;

    cout << "Enter filename:";
    cin >> filename;
    cin.ignore();

    if (!analyzer.readFile(filename)) return 1;

    cout << "\nAll Students:\n";
    analyzer.displayAll();

    string search;
    cout << "\nEnter student name to search: ";
    getline(cin, search);
    analyzer.searchByName(search);

    string field, order;
    cout << "\nSort by 'age' or 'grade': ";
    cin >> field;
    cout << "Order 'asc' or 'desc': ";
    cin >> order;

    analyzer.sortBy(field, order == "asc");
    cout << "\nSorted Students:\n";
    analyzer.displayAll();

    analyzer.displayStatistics();
    analyzer.saveResults("results.txt");

    return 0;
}

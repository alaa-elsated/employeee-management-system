
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
using namespace std;

class Employee {
protected:
    string name;
    int id;
    double baseSalary;
public:
    Employee(string n, int i, double b) : name(n), id(i), baseSalary(b) {}
    virtual ~Employee() = default;
    virtual double calculateSalary() const = 0;
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Base Salary: $" << baseSalary << endl;
    }
    virtual string toFileString() const = 0;
};

class FullTime : public Employee {
public:
    FullTime(string n, int i, double b) : Employee(n, i, b) {}
    double calculateSalary() const override {
        return baseSalary + 1000.0;
    }
    string toFileString() const override {
        return "FullTime," + to_string(id) + "," + name + "," + to_string(baseSalary);
    }
};

class PartTime : public Employee {
public:
    PartTime(string n, int i, double b) : Employee(n, i, b) {}
    double calculateSalary() const override {
        return baseSalary * 0.5;
    }
    string toFileString() const override {
        return "PartTime," + to_string(id) + "," + name + "," + to_string(baseSalary);
    }
};

class Contract : public Employee {
public:
    Contract(string n, int i, double b) : Employee(n, i, b) {}
    double calculateSalary() const override {
        return baseSalary;
    }
    string toFileString() const override {
        return "Contract," + to_string(id) + "," + name + "," + to_string(baseSalary);
    }
};

void saveToFile(const vector<unique_ptr<Employee>>& employees, const string& filename) {
    ofstream file(filename);
    for (const auto& e : employees) {
        file << e->toFileString() << endl;
    }
    file.close();
}

void displayAll(const vector<unique_ptr<Employee>>& employees) {
    for (const auto& e : employees) {
        e->display();
        cout << "Calculated Salary: $" << e->calculateSalary() << "\n\n";
    }
}

int main() {
    vector<unique_ptr<Employee>> employees;
    int num;

    cout << "How many employees would you like to enter? ";
    cin >> num;

    for (int i = 0; i < num; ++i) {
        cout << "\nEmployee " << (i + 1) << ":\n";

        string name, type;
        int id;
        double baseSalary;

        cout << "Name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Employee ID: ";
        cin >> id;

        cout << "Base Salary: $";
        cin >> baseSalary;

        cout << "Employment Type (FullTime / PartTime / Contract): ";
        cin >> type;

        if (type == "FullTime") {
            employees.push_back(make_unique<FullTime>(name, id, baseSalary));
        } else if (type == "PartTime") {
            employees.push_back(make_unique<PartTime>(name, id, baseSalary));
        } else if (type == "Contract") {
            employees.push_back(make_unique<Contract>(name, id, baseSalary));
        } else {
            cout << "Unknown employment type. Skipping this employee.\n";
        }
    }

    cout << "\n--- Employee Details ---\n";
    displayAll(employees);

    saveToFile(employees, "employees.txt");

    return 0;
}

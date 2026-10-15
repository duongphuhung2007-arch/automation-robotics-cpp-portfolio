#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int studentNumber{};
    double grade{};
};

class StudentStack {
public:
    void push(const Student& student) { students_.push_back(student); }

    Student pop() {
        if (empty()) return {};
        Student topStudent = students_.back();
        students_.pop_back();
        return topStudent;
    }

    const Student* top() const {
        return empty() ? nullptr : &students_.back();
    }

    bool empty() const { return students_.empty(); }
    std::size_t size() const { return students_.size(); }

private:
    std::vector<Student> students_;
};

int main() {
    StudentStack stack;
    int count = 0;

    std::cout << "How many students do you want to enter? ";
    std::cin >> count;
    std::cin.ignore();

    for (int i = 0; i < count; ++i) {
        Student student;
        std::cout << "Student " << i + 1 << " name: ";
        std::getline(std::cin, student.name);
        std::cout << "Student number: ";
        std::cin >> student.studentNumber;
        std::cout << "Grade: ";
        std::cin >> student.grade;
        std::cin.ignore();
        stack.push(student);
    }

    std::cout << "\nStack size: " << stack.size() << '\n';
    if (const Student* student = stack.top())
        std::cout << "Top student: " << student->name << '\n';

    if (!stack.empty()) {
        Student removed = stack.pop();
        std::cout << "Popped student: " << removed.name << '\n';
    }

    std::cout << "Stack size after pop: " << stack.size() << '\n';
    return 0;
}

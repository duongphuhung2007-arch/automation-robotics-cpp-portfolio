#include <iostream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int studentNumber{};
    double grade{};
};

class StudentQueue {
public:
    void enqueue(const Student& student) { students_.push_back(student); }

    Student dequeue() {
        if (empty()) return {};
        Student frontStudent = students_.front();
        students_.erase(students_.begin());
        return frontStudent;
    }

    const Student* front() const {
        return empty() ? nullptr : &students_.front();
    }

    const Student* back() const {
        return empty() ? nullptr : &students_.back();
    }

    bool empty() const { return students_.empty(); }
    std::size_t size() const { return students_.size(); }

private:
    std::vector<Student> students_;
};

int main() {
    StudentQueue queue;
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
        queue.enqueue(student);
    }

    std::cout << "\nQueue size: " << queue.size() << '\n';
    if (const Student* student = queue.front())
        std::cout << "Front student: " << student->name << '\n';
    if (const Student* student = queue.back())
        std::cout << "Last student: " << student->name << '\n';

    if (!queue.empty()) {
        Student removed = queue.dequeue();
        std::cout << "Dequeued student: " << removed.name << '\n';
    }

    std::cout << "Queue size after dequeue: " << queue.size() << '\n';
    return 0;
}

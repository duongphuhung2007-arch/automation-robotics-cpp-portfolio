#include <iostream>
#include <vector>

void printVector(const std::vector<int>& values) {
    std::cout << "Vector: ";
    for (int value : values) std::cout << value << ' ';
    std::cout << '\n';
}

int main() {
    std::vector<int> values;
    int size = 0;

    std::cout << "Enter the starting vector size: ";
    std::cin >> size;
    values.resize(size);

    std::cout << "Enter " << size << " values: ";
    for (int& value : values) std::cin >> value;

    int choice = 0;
    while (choice != 5) {
        printVector(values);
        std::cout << "\n1. Add to end\n"
                     "2. Remove from end\n"
                     "3. Insert at position\n"
                     "4. Remove a value\n"
                     "5. Exit\n"
                     "Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            int value;
            std::cout << "Value to add: ";
            std::cin >> value;
            values.push_back(value);
        } else if (choice == 2) {
            if (values.empty()) {
                std::cout << "Vector is already empty.\n";
            } else {
                values.pop_back();
            }
        } else if (choice == 3) {
            int value, position;
            std::cout << "Value to insert: ";
            std::cin >> value;
            std::cout << "Position (0 to " << values.size() << "): ";
            std::cin >> position;

            if (position < 0 || position > static_cast<int>(values.size())) {
                std::cout << "Invalid position.\n";
            } else {
                values.insert(values.begin() + position, value);
            }
        } else if (choice == 4) {
            int value;
            std::cout << "Value to remove: ";
            std::cin >> value;

            bool found = false;
            for (auto it = values.begin(); it != values.end(); ++it) {
                if (*it == value) {
                    values.erase(it);
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Value not found.\n";
        } else if (choice != 5) {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}

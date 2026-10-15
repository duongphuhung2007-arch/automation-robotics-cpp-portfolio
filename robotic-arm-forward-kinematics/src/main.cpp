#include <cmath>
#include <iostream>
#include <vector>

using Matrix3 = std::vector<std::vector<double>>;
using Vector3 = std::vector<double>;

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kMinimumZ = -80.0;

Matrix3 rotationX(double theta) {
    return {
        {1.0, 0.0, 0.0},
        {0.0, std::cos(theta), -std::sin(theta)},
        {0.0, std::sin(theta), std::cos(theta)}
    };
}

Matrix3 rotationZ(double theta) {
    return {
        {std::cos(theta), -std::sin(theta), 0.0},
        {std::sin(theta), std::cos(theta), 0.0},
        {0.0, 0.0, 1.0}
    };
}

Matrix3 identityMatrix() {
    return {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    };
}

Vector3 multiply(const Matrix3& matrix, const Vector3& vector) {
    Vector3 result(3, 0.0);
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            result[row] += matrix[row][col] * vector[col];
        }
    }
    return result;
}

Matrix3 multiply(const Matrix3& left, const Matrix3& right) {
    Matrix3 result(3, Vector3(3, 0.0));
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            for (int k = 0; k < 3; ++k) {
                result[row][col] += left[row][k] * right[k][col];
            }
        }
    }
    return result;
}

Vector3 add(const Vector3& a, const Vector3& b) {
    Vector3 result(3, 0.0);
    for (int i = 0; i < 3; ++i) {
        result[i] = a[i] + b[i];
    }
    return result;
}

double degreesToRadians(double degrees) {
    return degrees * kPi / 180.0;
}

double roundToHundredths(double value) {
    return std::round(value * 100.0) / 100.0;
}

bool validJointAngle(double angle) {
    return angle >= 0.0 && angle <= 180.0;
}

bool belowTable(const Vector3& position) {
    return position[2] < kMinimumZ;
}

Vector3 invalidPosition() {
    return {NAN, NAN, NAN};
}

Vector3 forwardKinematics(double waistAngle,
                          double shoulderAngle,
                          double elbowAngle,
                          double pitchAngle) {
    const Vector3 waistOffset = {0.0, 0.0, 0.0};
    const Vector3 shoulderOffset = {-25.0, -20.0, 11.0};
    const Vector3 elbowOffset = {0.0, 0.0, 103.0};
    const Vector3 pitchOffset = {0.0, 0.0, 125.0};
    const Vector3 rollOffset = {17.0, 0.0, 70.0};
    const Vector3 endEffectorOffset = {0.0, 0.0, 110.0};

    waistAngle = degreesToRadians(waistAngle - 90.0);
    shoulderAngle = degreesToRadians(shoulderAngle - 90.0);
    elbowAngle = degreesToRadians(-(elbowAngle - 90.0));
    pitchAngle = degreesToRadians(pitchAngle - 90.0);

    Vector3 position = {0.0, 0.0, 0.0};
    Matrix3 rotation = identityMatrix();

    rotation = multiply(rotation, rotationZ(waistAngle));
    position = add(position, multiply(rotation, waistOffset));
    if (belowTable(position)) return invalidPosition();

    rotation = multiply(rotation, rotationX(shoulderAngle));
    position = add(position, multiply(rotation, shoulderOffset));
    if (belowTable(position)) return invalidPosition();

    rotation = multiply(rotation, rotationX(elbowAngle));
    position = add(position, multiply(rotation, elbowOffset));
    if (belowTable(position)) return invalidPosition();

    rotation = multiply(rotation, rotationX(pitchAngle));
    position = add(position, multiply(rotation, pitchOffset));
    if (belowTable(position)) return invalidPosition();

    position = add(position, multiply(rotation, rollOffset));
    if (belowTable(position)) return invalidPosition();

    position = add(position, multiply(rotation, endEffectorOffset));
    if (belowTable(position)) return invalidPosition();

    for (double& coordinate : position) {
        coordinate = roundToHundredths(coordinate);
    }
    return position;
}
}  // namespace

int main() {
    int choice = 0;

    do {
        std::cout << "\n====== Forward Kinematics ======\n"
                  << "1. Enter joint angles\n"
                  << "2. Exit\n"
                  << "Choose: ";
        std::cin >> choice;

        if (choice == 1) {
            double waist = 0.0;
            double shoulder = 0.0;
            double elbow = 0.0;
            double pitch = 0.0;

            std::cout << "\nEnter angles in degrees (0 to 180).\n";
            std::cout << "Waist: ";
            std::cin >> waist;
            std::cout << "Shoulder: ";
            std::cin >> shoulder;
            std::cout << "Elbow: ";
            std::cin >> elbow;
            std::cout << "Pitch: ";
            std::cin >> pitch;

            if (!validJointAngle(waist) || !validJointAngle(shoulder) ||
                !validJointAngle(elbow) || !validJointAngle(pitch)) {
                std::cout << "Invalid input: each angle must be between 0 and 180 degrees.\n";
                continue;
            }

            const Vector3 result = forwardKinematics(waist, shoulder, elbow, pitch);
            if (std::isnan(result[0])) {
                std::cout << "Invalid position: the arm would move below the table boundary.\n";
            } else {
                std::cout << "\nEnd-effector position:\n"
                          << "X = " << result[0] << '\n'
                          << "Y = " << result[1] << '\n'
                          << "Z = " << result[2] << '\n';
            }
        } else if (choice == 2) {
            std::cout << "Program ended.\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    } while (choice != 2);

    return 0;
}

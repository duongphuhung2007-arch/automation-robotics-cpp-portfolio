#include <cmath>
#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

constexpr double EPS = 1e-12;

void printMatrix(const Matrix& m) {
    for (const auto& row : m) {
        std::cout << "[ ";
        for (double value : row) std::cout << value << ' ';
        std::cout << "]\n";
    }
}

Matrix readMatrix(int n) {
    Matrix m(n, Vector(n, 0.0));
    std::cout << "Enter a " << n << "x" << n << " matrix row by row:\n";
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c)
            std::cin >> m[r][c];
    return m;
}

double det2(const Matrix& m) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

double det3(const Matrix& m) {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
         - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
         + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

Matrix transpose(const Matrix& m) {
    Matrix t(m.size(), Vector(m.size(), 0.0));
    for (size_t r = 0; r < m.size(); ++r)
        for (size_t c = 0; c < m.size(); ++c)
            t[r][c] = m[c][r];
    return t;
}

bool inverse2(const Matrix& m, Matrix& inv) {
    const double d = det2(m);
    if (std::abs(d) < EPS) return false;
    inv = {{m[1][1] / d, -m[0][1] / d},
           {-m[1][0] / d, m[0][0] / d}};
    return true;
}

double minor3(const Matrix& m, int row, int col) {
    Vector values;
    for (int r = 0; r < 3; ++r)
        if (r != row)
            for (int c = 0; c < 3; ++c)
                if (c != col) values.push_back(m[r][c]);
    return values[0] * values[3] - values[1] * values[2];
}

bool inverse3(const Matrix& m, Matrix& inv) {
    const double d = det3(m);
    if (std::abs(d) < EPS) return false;

    Matrix cof(3, Vector(3, 0.0));
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            cof[r][c] = ((r + c) % 2 == 0 ? 1.0 : -1.0) * minor3(m, r, c);

    inv = transpose(cof);
    for (auto& row : inv)
        for (double& value : row)
            value /= d;
    return true;
}

bool solve(const Matrix& a, const Vector& b, Vector& x) {
    Matrix inv;
    bool ok = a.size() == 2 ? inverse2(a, inv) : inverse3(a, inv);
    if (!ok) return false;

    x.assign(a.size(), 0.0);
    for (size_t r = 0; r < a.size(); ++r)
        for (size_t c = 0; c < a.size(); ++c)
            x[r] += inv[r][c] * b[c];
    return true;
}

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n1. Inverse 2x2\n2. Inverse 3x3\n3. Transpose 2x2\n"
                     "4. Transpose 3x3\n5. Solve 2x2 system\n6. Solve 3x3 system\n0. Exit\nChoice: ";
        std::cin >> choice;
        if (choice == 0) break;

        int n = (choice == 1 || choice == 3 || choice == 5) ? 2 : 3;
        Matrix a = readMatrix(n);

        if (choice == 1 || choice == 2) {
            Matrix inv;
            bool ok = n == 2 ? inverse2(a, inv) : inverse3(a, inv);
            if (!ok) std::cout << "Matrix is singular.\n";
            else printMatrix(inv);
        } else if (choice == 3 || choice == 4) {
            printMatrix(transpose(a));
        } else if (choice == 5 || choice == 6) {
            Vector b(n), x;
            std::cout << "Enter vector b:\n";
            for (double& value : b) std::cin >> value;
            if (!solve(a, b, x)) std::cout << "No unique solution.\n";
            else {
                std::cout << "Solution: ";
                for (double value : x) std::cout << value << ' ';
                std::cout << '\n';
            }
        }
    }
    return 0;
}

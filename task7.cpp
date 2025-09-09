#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix multiplyNaive(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}


Matrix add(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix strassen(Matrix A, Matrix B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    if (n == 1) { // base case
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    // Divide A and B into 4 submatrices
    Matrix A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    Matrix B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Strassen’s 7 multiplications
    Matrix M1 = strassen(add(A11, A22), add(B11, B22));
    Matrix M2 = strassen(add(A21, A22), B11);
    Matrix M3 = strassen(A11, subtract(B12, B22));
    Matrix M4 = strassen(A22, subtract(B21, B11));
    Matrix M5 = strassen(add(A11, A12), B22);
    Matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    Matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    // Combine results
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    // Put back into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    return C;
}

void printMatrix(Matrix M) {
    for (int i = 0; i < M.size(); i++) {
        for (int j = 0; j < M.size(); j++) {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool compare(Matrix A, Matrix B) {
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A.size(); j++)
            if (A[i][j] != B[i][j]) return false;
    return true;
}


void test2x2() {
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};

    Matrix resultStrassen = strassen(A, B);
    Matrix resultNaive = multiplyNaive(A, B);

    cout << "Test 2x2: " << (compare(resultStrassen, resultNaive) ? "Passed" : "Failed") << endl;
}

void test4x4() {
    Matrix A = {{1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 16}};

    Matrix B = {{16, 15, 14, 13},
                {12, 11, 10, 9},
                {8, 7, 6, 5},
                {4, 3, 2, 1}};

    Matrix resultStrassen = strassen(A, B);
    Matrix resultNaive = multiplyNaive(A, B);

    cout << "Test 4x4: " << (compare(resultStrassen, resultNaive) ? "Passed" : "Failed") << endl;
}

void testRandom() {
    Matrix A = {{2, 1}, {0, 1}};
    Matrix B = {{1, 0}, {3, 2}};

    Matrix resultStrassen = strassen(A, B);
    Matrix resultNaive = multiplyNaive(A, B);

    cout << "Test Random: " << (compare(resultStrassen, resultNaive) ? "Passed" : "Failed") << endl;
}


int main() {
    test2x2();
    test4x4();
    testRandom();
    return 0;
}

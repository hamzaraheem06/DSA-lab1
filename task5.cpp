#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> generatePascal(int n) {
    vector<vector<int>> triangle;

    for (int row = 1; row <= n; row++) {
        vector<int> currentRow;
        int c = 1; // first value is always 1

        for (int i = 1; i <= row; i++) {
            currentRow.push_back(c);
            c = c * (row - i) / i; // nCr relation
        }

        triangle.push_back(currentRow);
    }

    return triangle;
}

bool compareVectors(vector<int> a, vector<int> b) {
    if (a.size() != b.size()) return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void testPascalN0() {
    vector<vector<int>> res0 = generatePascal(0);
    vector<int> expected0; // empty

    if (res0.empty() && expected0.empty()) {
        cout << "Test n=0 Passed" << endl;
    } else {
        cout << "Test n=0 Failed" << endl;
    }
}

void testPascalN1() {
    vector<vector<int>> res1 = generatePascal(1);
    vector<int> expected1;
    expected1.push_back(1);

    if (!res1.empty() && compareVectors(res1[0], expected1)) {
        cout << "Test n=1 Passed" << endl;
    } else {
        cout << "Test n=1 Failed" << endl;
    }
}

void testPascalN5() {
    vector<vector<int>> res5 = generatePascal(5);
    vector<int> expected5;
    expected5.push_back(1);
    expected5.push_back(4);
    expected5.push_back(6);
    expected5.push_back(4);
    expected5.push_back(1);

    if (!res5.empty() && compareVectors(res5[4], expected5)) {
        cout << "Test n=5 Passed" << endl;
    } else {
        cout << "Test n=5 Failed" << endl;
    }
}

int main() {
    testPascalN0();
    testPascalN1();
    testPascalN5();
    return 0;
}

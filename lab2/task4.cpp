#include <iostream>
using namespace std;

void printMatrix(int A[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << A[i][j] << " ";
        cout << endl;
    }
}

void deleteDiagonal(int A[5][5]) {
    for (int i = 0; i < 5; i++) A[i][i] = 0;
}

void removeRow(int A[5][5], int &n, int row) {
    for (int i = row; i < n - 1; i++) {
        for (int j = 0; j < n; j++) A[i][j] = A[i + 1][j];
    }
    n--;
}

void findMaxRow(int A[5][5], int n, int &maxRow) {
    int maxVal = A[0][0];
    maxRow = 0;
    for (int i = 0; i < n; i++) {
        int rowMax = A[i][0];
        for (int j = 0; j < n; j++) {
            if (A[i][j] > rowMax) rowMax = A[i][j];
        }
        if (rowMax > maxVal) {
            maxVal = rowMax;
            maxRow = i;
        }
    }
}

int main() {
    int A[5][5] = {
        {12, 5, 8, 3, 7},
        {1, 16, 4, 9, 13},
        {2, 10, 6, 11, 15},
        {100, 14, 18, 20, 19},
        {22, 21, 23, 24, 25}
    };
    int n = 5;
    cout << "Original matrix:" << endl;
    printMatrix(A);
    deleteDiagonal(A);
    int maxRow;
    findMaxRow(A, n, maxRow);
    removeRow(A, n, maxRow);
    cout << "Transformed matrix:" << endl;
    printMatrix(A);
    return 0;
}

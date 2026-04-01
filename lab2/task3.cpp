#include <iostream>
using namespace std;

void printMatrix(int A[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) cout << A[i][j] << " ";
        cout << endl;
    }
}

void swapRows(int A[5][5], int row1, int row2) {
    for (int i = 0; i < 5; i++)
        swap(A[row1][i], A[row2][i]);
}

void swapColumns(int A[5][5], int col1, int col2) {
    for (int i = 0; i < 5; i++) swap(A[i][col1], A[i][col2]);
}

void moveMaxToTopLeft(int A[5][5]) {
    int maxVal = A[0][0];
    int maxRow = 0, maxCol = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (A[i][j] > maxVal) {
                maxVal = A[i][j];
                maxRow = i;
                maxCol = j;
            }
        }
    }
    if (maxRow != 0) {
        swapRows(A, 0, maxRow);
        cout << "Matrix after swapping row: " << maxRow << " with row 0:" << endl;
        printMatrix(A);
    }
    if (maxCol != 0) {
        swapColumns(A, 0, maxCol);
        cout << "Matrix after swapping col: " << maxCol << " with col 0:" << endl;
        printMatrix(A);
    }
}

int main() {
    int A[5][5] = {
        {12, 5, 8, 3, 7},
        {1, 16, 4, 9, 13},
        {2, 10, 6, 110, 15},
        {17, 14, 18, 20, 19},
        {22, 21, 23, 24, 25}
    };
    cout << "Original matrix: " << endl;
    printMatrix(A);
    moveMaxToTopLeft(A);
    return 0;
}

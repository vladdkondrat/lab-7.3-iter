#include <iostream>
#include <iomanip>
using namespace std;

// Функція для введення елементів матриці з клавіатури
void InputMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }
}

// Функція для виведення матриці
void PrintMatrix(int** matrix, int rows, int cols) {
    cout << "\nMatrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl;
    }
}

// Функція для циклічного зміщення елементів матриці вправо або вниз
void ShiftMatrix(int** matrix, int rows, int cols, int shiftCount, bool shiftRight) {
    shiftCount %= shiftRight ? cols : rows;  // Зменшуємо зсув для уникнення надлишкового зсуву

    if (shiftRight) { // Зміщення вправо
        for (int i = 0; i < rows; i++) {
            int* tempRow = new int[cols];
            for (int j = 0; j < cols; j++) {
                tempRow[(j + shiftCount) % cols] = matrix[i][j];
            }
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = tempRow[j];
            }
            delete[] tempRow;
        }
    }
    else { // Зміщення вниз
        for (int j = 0; j < cols; j++) {
            int* tempCol = new int[rows];
            for (int i = 0; i < rows; i++) {
                tempCol[(i + shiftCount) % rows] = matrix[i][j];
            }
            for (int i = 0; i < rows; i++) {
                matrix[i][j] = tempCol[i];
            }
            delete[] tempCol;
        }
    }
}

// Функція для знаходження першого рядка з найбільшою кількістю нулів
int FindRowWithMostZeroes(int** matrix, int rows, int cols) {
    int maxZeroCount = 0;
    int rowIndexWithMostZeroes = -1;

    for (int i = 0; i < rows; i++) {
        int zeroCount = 0;
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroCount++;
            }
        }
        if (zeroCount > maxZeroCount) {
            maxZeroCount = zeroCount;
            rowIndexWithMostZeroes = i;
        }
    }
    return rowIndexWithMostZeroes;
}

// Основна функція
int main() {
    int rows, cols, shiftCount;
    bool shiftRight;

    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // Динамічне створення матриці
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }

    // Введення матриці
    InputMatrix(matrix, rows, cols);

    // Зміщення матриці
    cout << "Enter shift count: ";
    cin >> shiftCount;
    cout << "Enter shift direction (1 for right, 0 for down): ";
    cin >> shiftRight;
    ShiftMatrix(matrix, rows, cols, shiftCount, shiftRight);

    // Виведення зміщеної матриці
    PrintMatrix(matrix, rows, cols);

    // Знаходження рядка з найбільшою кількістю нулів
    int rowIndex = FindRowWithMostZeroes(matrix, rows, cols);
    if (rowIndex != -1) {
        cout << "First row with the most zeroes is row " << rowIndex << endl;
    }
    else {
        cout << "No zeroes found in the matrix." << endl;
    }

    // Звільнення пам'яті
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}

#include <stdio.h>

#define MAX_SIZE 10

// Function Declarations with Parameters
void matrixAdd(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]);
void matrixSubtract(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]);
void matrixMultiple(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]);

int main() {
    int matrix1[MAX_SIZE][MAX_SIZE] = {0};
    int matrix2[MAX_SIZE][MAX_SIZE] = {0};

    int rowCount1, rowCount2, columnCount1, columnCount2;

    printf("==================== MATRIX CALCULATOR ====================\n");

    // Input dimensions for Matrix 1
    printf("Enter the Row count of Matrix 1 (Max %d): ", MAX_SIZE);
    scanf("%d", &rowCount1);
    printf("Enter the Column count of Matrix 1 (Max %d): ", MAX_SIZE);
    scanf("%d", &columnCount1);

    printf("\n");

    // Input dimensions for Matrix 2
    printf("Enter the Row count of Matrix 2 (Max %d): ", MAX_SIZE);
    scanf("%d", &rowCount2);
    printf("Enter the Column count of Matrix 2 (Max %d): ", MAX_SIZE);
    scanf("%d", &columnCount2);

    printf("\n");

    // Validate matrix dimensions
    if (rowCount1 <= 0 || columnCount1 <= 0 || rowCount2 <= 0 || columnCount2 <= 0 ||
        rowCount1 > MAX_SIZE || columnCount1 > MAX_SIZE || rowCount2 > MAX_SIZE || columnCount2 > MAX_SIZE) {
        printf("\n[Error] Invalid dimensions! Rows and columns must be between 1 and %d.\n", MAX_SIZE);
        return 1;
    }

    // Input values for Matrix 1
    printf("--- Input Matrix 1 ---\n");
    for (int row = 0; row < rowCount1; row++) {
        for (int column = 0; column < columnCount1; column++) {
            printf("Matrix1[%d][%d]: ", row, column);
            scanf("%d", &matrix1[row][column]);
        }
    }

    // Print Matrix 1
    printf("\nValues of Matrix 1:\n");
    for (int row = 0; row < rowCount1; row++) {
        printf(" | ");
        for (int column = 0; column < columnCount1; column++) {
            printf("\t%d\t", matrix1[row][column]);
        }
        printf(" |\n");
    }

    printf("\n");

    // Input values for Matrix 2
    printf("--- Input Matrix 2 ---\n");
    for (int row = 0; row < rowCount2; row++) {
        for (int column = 0; column < columnCount2; column++) {
            printf("Matrix2[%d][%d]: ", row, column);
            scanf("%d", &matrix2[row][column]);
        }
    }

    // Print Matrix 2
    printf("\nValues of Matrix 2:\n");
    for (int row = 0; row < rowCount2; row++) {
        printf(" | ");
        for (int column = 0; column < columnCount2; column++) {
            printf("\t%d\t", matrix2[row][column]);
        }
        printf(" |\n");
    }

    printf("\n------------------------------------------------------------------------------------\n");

    // Dimensions validation for Matrix Addition and Subtraction
    if (rowCount1 == rowCount2 && columnCount1 == columnCount2) {
        matrixAdd(rowCount1, columnCount1, rowCount2, columnCount2, matrix1, matrix2);
        matrixSubtract(rowCount1, columnCount1, rowCount2, columnCount2, matrix1, matrix2);
    } else {
        printf("\n[Notice] Addition and Subtraction skipped: Matrices must be of the same dimensions.\n");
    }

    // Dimensions validation for Matrix Multiplication
    if (columnCount1 == rowCount2) {
        matrixMultiple(rowCount1, columnCount1, rowCount2, columnCount2, matrix1, matrix2);
    } else {
        printf("\n[Notice] Multiplication skipped: Columns of Matrix 1 must equal rows of Matrix 2.\n");
    }

    printf("\n====================================================================================\n");
    return 0;
}

// Matrix Addition Function Definition
void matrixAdd(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]) {
    int sumMatrix[MAX_SIZE][MAX_SIZE] = {0};

    for (int row = 0; row < row1; row++) {
        for (int column = 0; column < column1; column++) {
            sumMatrix[row][column] = matrix1[row][column] + matrix2[row][column];
        }
    }

    printf("\nResult of Matrix Addition:\n");
    for (int row = 0; row < row1; row++) {
        printf(" | ");
        for (int column = 0; column < column1; column++) {
            printf("\t%d\t", sumMatrix[row][column]);
        }
        printf(" |\n");
    }
}

// Matrix Subtraction Function Definition
void matrixSubtract(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]) {
    int subtractMatrix[MAX_SIZE][MAX_SIZE] = {0};

    for (int row = 0; row < row1; row++) {
        for (int column = 0; column < column1; column++) {
            subtractMatrix[row][column] = matrix1[row][column] - matrix2[row][column];
        }
    }

    printf("\nResult of Matrix Subtraction:\n");
    for (int row = 0; row < row1; row++) {
        printf(" | ");
        for (int column = 0; column < column1; column++) {
            printf("\t%d\t", subtractMatrix[row][column]);
        }
        printf(" |\n");
    }
}

// Matrix Multiplication Function Definition
void matrixMultiple(int row1, int column1, int row2, int column2, int matrix1[MAX_SIZE][MAX_SIZE], int matrix2[MAX_SIZE][MAX_SIZE]) {
    int multipleMatrix[MAX_SIZE][MAX_SIZE] = {0};

    for (int row = 0; row < row1; row++) {
        for (int column = 0; column < column2; column++) {
            for (int multiple = 0; multiple < column1; multiple++) {
                multipleMatrix[row][column] += matrix1[row][multiple] * matrix2[multiple][column];
            }
        }
    }

    printf("\nResult of Matrix Multiplication:\n");
    for (int row = 0; row < row1; row++) {
        printf(" | ");
        for (int column = 0; column < column2; column++) {
            printf("\t%d\t", multipleMatrix[row][column]);
        }
        printf(" |\n");
    }
}

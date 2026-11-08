#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Constants
const double BASE_SALARY = 50000.0;
const double DEDUCTION_PER_LEAVE = 100.0;

// Function Declarations
void displayMenu();
double calculateSalary(int years, int leaveDays);

int main() {
    char option;
    static int calculationCount = 0;

    do {
        displayMenu();

        int workedYears;
        printf("Select the range number (1-4): ");
        if (scanf("%d", &workedYears) != 1) {
            printf("\n[Error] Invalid input format. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (workedYears < 1 || workedYears > 4) {
            printf("\n[Error] Invalid range selection! Please choose between 1 and 4.\n\n");
            continue;
        }

        int leaveDays;
        printf("Enter the leave days: ");
        if (scanf("%d", &leaveDays) != 1 || leaveDays < 0) {
            printf("\n[Error] Invalid leave days entered.\n");
            while (getchar() != '\n');
            continue;
        }

        double finalSalary = calculateSalary(workedYears, leaveDays);
        calculationCount++;

        printf("\n--------------------------------------------------------------\n");
        printf("Final Calculated Salary : Rs. %.2lf\n", finalSalary);
        printf("Total calculations performed in session : %d\n", calculationCount);
        printf("--------------------------------------------------------------\n\n");

        printf("Do you want to calculate another salary? (y/n): ");
        scanf(" %c", &option);
        option = tolower(option);
        printf("\n");

    } while (option == 'y');

    printf("................... System Exiting ...................\n");
    printf("................... Thank You! .......................\n");
    return 0;
}

// Function definition for printing system details and menu
void displayMenu() {
    printf("-------- Salary Management System --------\n\n");
    printf("Base Salary                   => Rs. %.2f\n", BASE_SALARY);
    printf("Deduction Amount per Leave Day => Rs. %.2lf\n\n", DEDUCTION_PER_LEAVE);
    printf("---------------------------------------------------\n");
    printf("RangeNo | Increment Percentage\n");
    printf("---------------------------------------------------\n");
    printf("1       | 2.5%%\n");
    printf("2       | 5.0%%\n");
    printf("3       | 7.5%%\n");
    printf("4       | 10.0%%\n");
    printf("---------------------------------------------------\n\n");
}

// Function definition for computing final salary securely
double calculateSalary(int years, int leaveDays) {
    double incrementRate = 0.0;

    switch (years) {
        case 1:
            incrementRate = 0.025;
            break;
        case 2:
            incrementRate = 0.050;
            break;
        case 3:
            incrementRate = 0.075;
            break;
        case 4:
            incrementRate = 0.100;
            break;
        default:
            incrementRate = 0.0;
            break;
    }

    double increment = BASE_SALARY * incrementRate;
    double deduction = leaveDays * DEDUCTION_PER_LEAVE;
    double finalSalary = BASE_SALARY + increment - deduction;

    return finalSalary;
}

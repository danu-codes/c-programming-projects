#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define TOTAL_WORKERS 5

// Function Declarations
void inputDetails();
void salaryCalculation(int employeeID, char gender, int serviceYear, char charCode, const char* month, int salesYear, double saleAmount);
void salaryDisplay(int employeeID, char charCode, const char* month, int salesYear, double basicSalary, double commission, double bonus, double totalSalary);

int main() {
    printf("\n------------------- Employee Salary Calculation System -------------------\n");
    inputDetails();
    return 0;
}

// Input Details Function Definition
void inputDetails() {
    int inputCount = 0;

    while (inputCount < TOTAL_WORKERS) {
        int employeeID, serviceYear, salesYear;
        char gender, charCode;
        char month[10];
        double saleAmount;

        printf("\n--- Entering Details for Employee %d of %d ---\n", inputCount + 1, TOTAL_WORKERS);
        
        printf("Enter the Employee ID: ");
        scanf("%d", &employeeID);

        // Gender Validation
        bool genderCheck = false;
        do {
            printf("Enter the Employee Gender (M/F): ");
            scanf(" %c", &gender);
            gender = toupper(gender);
            if (gender == 'M' || gender == 'F') {
                genderCheck = true;
            } else {
                printf("[Error] Invalid gender! Please enter M or F.\n");
            }
        } while (!genderCheck);

        printf("Enter the Employee Service Years: ");
        scanf("%d", &serviceYear);

        // Staff Title & Basic Salary Assignment
        double basicSalary = 0.0;
        bool validStaff = false;
        do {
            printf("Enter the Employee Staff Title (S-Senior, J-Junior, T-Trainee): ");
            scanf(" %c", &charCode);
            charCode = toupper(charCode);

            if (charCode == 'S') {
                basicSalary = 60000.0;
                validStaff = true;
            } else if (charCode == 'J') {
                basicSalary = 40000.0;
                validStaff = true;
            } else if (charCode == 'T') {
                basicSalary = 18000.0;
                validStaff = true;
            } else {
                printf("[Error] Invalid staff code! Please enter S, J, or T.\n");
            }
        } while (!validStaff);

        printf("Enter the Month to Calculate Gross Salary (Ex: JAN, DEC): ");
        scanf("%s", month);
        for (int i = 0; month[i]; i++) {
            month[i] = toupper(month[i]);
        }

        printf("Enter the Current Year: ");
        scanf("%d", &salesYear);

        printf("Enter the Employee Sales Amount: ");
        scanf("%lf", &saleAmount);

        salaryCalculation(employeeID, gender, serviceYear, charCode, month, salesYear, saleAmount);

        inputCount++;
    }
    printf("\n[Success] All worker salaries have been calculated successfully!\n");
}

// Salary Calculation Function Definition
void salaryCalculation(int employeeID, char gender, int serviceYear, char charCode, const char* month, int salesYear, double saleAmount) {
    double commissionOnSales = 0.0;
    double commissionOnService = 0.0;
    double commissionOnStaffTitle = 0.0;
    double bonusCommission = 0.0;
    double yearEndBonus = 0.0;
    double basicSalary = 0.0;

    if (charCode == 'S') basicSalary = 60000.0;
    else if (charCode == 'J') basicSalary = 40000.0;
    else if (charCode == 'T') basicSalary = 18000.0;

    // Commission on Sales Calculations
    if (saleAmount <= 25000) {
        commissionOnSales = 0.03 * saleAmount;
    } else if (saleAmount <= 50000) {
        commissionOnSales = 0.05 * saleAmount;
    } else if (saleAmount <= 100000) {
        commissionOnSales = 0.07 * saleAmount;
    } else if (saleAmount <= 150000) {
        commissionOnSales = 0.09 * saleAmount;
        if (saleAmount > 125000) {
            bonusCommission = 0.04 * saleAmount;
        }
    } else {
        commissionOnSales = 0.14 * saleAmount;
    }

    // Commission on Service Calculation
    if (serviceYear >= 1 && serviceYear <= 9) {
        commissionOnService = (1.5 / 1000.0) * saleAmount;
    } else if (serviceYear >= 10) {
        commissionOnService = 0.015 * saleAmount;
    }

    // Commission on Staff Title Calculation
    if (charCode == 'J') {
        commissionOnStaffTitle = 0.003 * saleAmount;
    } else if (charCode == 'S') {
        commissionOnStaffTitle = 0.005 * saleAmount;
    }

    double totalCommission = commissionOnSales + commissionOnService + commissionOnStaffTitle + bonusCommission;
    double totalSalary = totalCommission + basicSalary;

    // December Month Bonus Calculation
    if (strcmp(month, "DEC") == 0) {
        if (basicSalary < 10000) {
            yearEndBonus += 0.02 * basicSalary;
        }
        if (gender == 'M') {
            yearEndBonus += 0.05 * basicSalary;
        } else if (gender == 'F') {
            yearEndBonus += 0.10 * basicSalary;
        }
        totalSalary += yearEndBonus;
    }

    salaryDisplay(employeeID, charCode, month, salesYear, basicSalary, totalCommission, yearEndBonus, totalSalary);
}

// Salary Display Function Definition
void salaryDisplay(int employeeID, char charCode, const char* month, int salesYear, double basicSalary, double commission, double bonus, double totalSalary) {
    int monthIndex = 0;
    const char *monthWords[] = {"January", "February", "March", "April", "May", "June", 
                                "July", "August", "September", "October", "November", "December"};
    const char *monthCodes[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
                                "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

    for (int i = 0; i < 12; i++) {
        if (strcmp(month, monthCodes[i]) == 0) {
            monthIndex = i;
            break;
        }
    }

    const char* staffTitleWord = "";
    if (charCode == 'S') {
        staffTitleWord = "Senior sales representative";
    } else if (charCode == 'J') {
        staffTitleWord = "Junior sales representative";
    } else if (charCode == 'T') {
        staffTitleWord = "Sales trainee";
    }

    printf("\n==========================================================================\n");
    printf("                       Sooriya Holdings (Pvt) Ltd.                        \n");
    printf("                       Pay Slip for %s - %d                         \n", monthWords[monthIndex], salesYear);
    printf("==========================================================================\n");
    printf("Employee No. : %d\n", employeeID);
    printf("Staff Title  : %s\n", staffTitleWord);
    printf("--------------------------------------------------------------------------\n");
    printf("Basic Salary : Rs. %.2lf\n", basicSalary);
    printf("Commissions  : Rs. %.2lf\n", commission);

    if (strcmp(month, "DEC") == 0) {
        printf("Bonus        : Rs. %.2lf\n", bonus);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Gross Salary : Rs. %.2lf\n", totalSalary);
    printf("==========================================================================\n");
}

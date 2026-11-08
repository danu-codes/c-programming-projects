#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTRACTORS 50
#define MAX_PROPERTIES 100

// Structure for Contractor Details
typedef struct {
    int contractorId;
    char contractorName[50];
    char contractorNumber[15];
} Contractor;

// Structure for Property Details
typedef struct {
    int propertyId;
    char propertyAddress[100];
    int numberOfRooms;
    double areaOfProperty;
    double pricePerSquareMeter;
    char propertyStatus; // 'S' for Sold, 'R' for Rented, 'A' for Available
    int assignedContractorId;
} Property;

// Global Data Storage
Contractor contractors[MAX_CONTRACTORS];
Property properties[MAX_PROPERTIES];

int contractorCount = 0;
int propertyCount = 0;

// Function Declarations
void displayMenu();
void addContractor();
void addProperty();
void updateStatus();
void generateReportOfSale();
void generateReportOfRent();
int findContractorIndex(int id);
int findPropertyIndex(int id);

int main() {
    displayMenu();
    return 0;
}

// Display Main Menu Interface
void displayMenu() {
    int choice = 0;
    do {
        printf("\n\t\t\t---------------------***( REAL ESTATE MENU )***----------------------\n");
        printf("\t\t\t+  1. Add a Contractor\t\t\t\t\t\t     +\n");
        printf("\t\t\t|  2. Add a Property & Assign Contractor\t\t\t     |\n");
        printf("\t\t\t+  3. Update the Status of a Property\t\t\t\t     +\n");
        printf("\t\t\t|  4. Generate Report of Sold Properties\t\t\t     |\n");
        printf("\t\t\t+  5. Generate Report of Rented Properties\t\t\t     +\n");
        printf("\t\t\t|  6. Exit System\t\t\t\t\t\t     |\n");
        printf("\t\t\t---------------------------------------------------------------------\n");

        printf("\nEnter your selection (1-6): ");
        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input format. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addContractor();
                break;
            case 2:
                addProperty();
                break;
            case 3:
                updateStatus();
                break;
            case 4:
                generateReportOfSale();
                break;
            case 5:
                generateReportOfRent();
                break;
            case 6:
                printf("\n................... System Exiting ...................\n");
                printf("................... Thank You! .......................\n");
                break;
            default:
                printf("\n[Error] Invalid Selection! Please choose a valid option between 1 and 6.\n");
                break;
        }
    } while (choice != 6);
}

// Helper function to find contractor index by ID
int findContractorIndex(int id) {
    for (int i = 0; i < contractorCount; i++) {
        if (contractors[i].contractorId == id) {
            return i;
        }
    }
    return -1;
}

// Helper function to find property index by ID
int findPropertyIndex(int id) {
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].propertyId == id) {
            return i;
        }
    }
    return -1;
}

// Add Contractor Function
void addContractor() {
    char option;
    while (contractorCount < MAX_CONTRACTORS) {
        printf("\n------------------------- Add Contractor Details -------------------------\n");
        int id;
        printf("Enter the ID of Contractor: ");
        scanf("%d", &id);

        if (findContractorIndex(id) != -1) {
            printf("\n[Error] Contractor ID %d already exists! Please use a unique ID.\n", id);
            continue;
        }

        contractors[contractorCount].contractorId = id;
        getchar(); // Clear newline buffer

        printf("Enter the Name of Contractor: ");
        fgets(contractors[contractorCount].contractorName, sizeof(contractors[contractorCount].contractorName), stdin);
        contractors[contractorCount].contractorName[strcspn(contractors[contractorCount].contractorName, "\n")] = 0; // Remove trailing newline

        // Validate Contact Number
        int validNumber = 0;
        do {
            printf("Enter the Contact Number (Format: 07XXXXXXXX): ");
            scanf("%s", contractors[contractorCount].contractorNumber);

            int len = strlen(contractors[contractorCount].contractorNumber);
            if (len != 10) {
                printf("\n[Error] Contact number must be exactly 10 digits.\n");
            } else if (contractors[contractorCount].contractorNumber[0] != '0') {
                printf("\n[Error] Contact number must start with '0'.\n");
            } else {
                validNumber = 1;
            }
        } while (!validNumber);

        contractorCount++;
        printf("\n[Success] Contractor details successfully added! Total Contractors: %d\n", contractorCount);

        if (contractorCount == MAX_CONTRACTORS) {
            printf("\n[Notice] Maximum contractor storage limit reached.\n");
            return;
        }

        printf("\nDo you want to add another contractor? (y/n): ");
        scanf(" %c", &option);
        if (tolower(option) == 'n') {
            break;
        }
    }
}

// Add Property Function
void addProperty() {
    char option;
    while (propertyCount < MAX_PROPERTIES) {
        if (contractorCount == 0) {
            printf("\n[Error] No contractors registered in the system yet. Please add a contractor first!\n");
            return;
        }

        printf("\n------------------------- Add Property Details -------------------------\n");
        int id;
        printf("Enter the ID of Property: ");
        scanf("%d", &id);

        if (findPropertyIndex(id) != -1) {
            printf("\n[Error] Property ID %d already exists! Please use a unique ID.\n", id);
            continue;
        }

        properties[propertyCount].propertyId = id;
        getchar(); // Clear newline buffer

        printf("Enter the Address of Property: ");
        fgets(properties[propertyCount].propertyAddress, sizeof(properties[propertyCount].propertyAddress), stdin);
        properties[propertyCount].propertyAddress[strcspn(properties[propertyCount].propertyAddress, "\n")] = 0;

        printf("Enter the Number of Rooms: ");
        scanf("%d", &properties[propertyCount].numberOfRooms);

        printf("Enter the Area of Property (in Square Meters): ");
        scanf("%lf", &properties[propertyCount].areaOfProperty);

        printf("Enter the Price Per Square Meter: ");
        scanf("%lf", &properties[propertyCount].pricePerSquareMeter);

        // Assign Contractor
        int assignedId, contractorIdx;
        do {
            printf("Enter Contractor ID to assign to this property: ");
            scanf("%d", &assignedId);

            contractorIdx = findContractorIndex(assignedId);
            if (contractorIdx == -1) {
                printf("\n[Error] No contractor found with ID %d. Please try again.\n", assignedId);
            } else {
                properties[propertyCount].assignedContractorId = assignedId;
                break;
            }
        } while (1);

        properties[propertyCount].propertyStatus = 'A'; // Default status: Available
        propertyCount++;

        printf("\n[Success] Property details successfully added! Total Properties: %d\n", propertyCount);

        if (propertyCount == MAX_PROPERTIES) {
            printf("\n[Notice] Maximum property storage limit reached.\n");
            return;
        }

        printf("\nDo you want to add another property? (y/n): ");
        scanf(" %c", &option);
        if (tolower(option) == 'n') {
            break;
        }
    }
}

// Update Property Status Function
void updateStatus() {
    if (propertyCount == 0) {
        printf("\n[Error] No property records available to update.\n");
        return;
    }

    int propId;
    printf("\n------------------------- Update Property Status -------------------------\n");
    printf("Enter the Property ID: ");
    scanf("%d", &propId);

    int idx = findPropertyIndex(propId);
    if (idx == -1) {
        printf("\n[Error] Property ID %d not found!\n", propId);
        return;
    }

    char statusInput;
    printf("Enter new status for Property %d ('S' for Sold, 'R' for Rented): ", propId);
    scanf(" %c", &statusInput);
    statusInput = toupper(statusInput);

    if (statusInput == 'S' || statusInput == 'R') {
        properties[idx].propertyStatus = statusInput;
        printf("\n[Success] Property ID %d status updated successfully to: %s\n", 
               propId, (statusInput == 'S') ? "Sold" : "Rented");
    } else {
        printf("\n[Error] Invalid status code entered. Use 'S' or 'R'.\n");
    }
}

// Generate Report for Sold Properties
void generateReportOfSale() {
    if (propertyCount == 0) {
        printf("\n[Error] No property records available.\n");
        return;
    }

    int soldCount = 0;
    printf("\n----------------------------- Sold Properties Report -----------------------------\n");
    
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].propertyStatus == 'S') {
            soldCount++;
            double calculatedPrice = properties[i].areaOfProperty * properties[i].pricePerSquareMeter;
            int cIndex = findContractorIndex(properties[i].assignedContractorId);

            printf("\nProperty ID       : %d\n", properties[i].propertyId);
            printf("  Address         : %s\n", properties[i].propertyAddress);
            printf("  Total Price     : Rs. %.2lf\n", calculatedPrice);
            
            if (cIndex != -1) {
                printf("  Assigned Contractor Details:\n");
                printf("    - ID          : %d\n", contractors[cIndex].contractorId);
                printf("    - Name        : %s\n", contractors[cIndex].contractorName);
                printf("    - Contact     : %s\n", contractors[cIndex].contractorNumber);
            }
            printf("----------------------------------------------------------------------------------\n");
        }
    }

    if (soldCount == 0) {
        printf("\n[Notice] No properties have been marked as sold yet.\n");
    }
    printf("---------------------------------- End of Report ---------------------------------\n");
}

// Generate Report for Rented Properties
void generateReportOfRent() {
    if (propertyCount == 0) {
        printf("\n[Error] No property records available.\n");
        return;
    }

    int rentedCount = 0;
    printf("\n----------------------------- Rented Properties Report -----------------------------\n");
    
    for (int i = 0; i < propertyCount; i++) {
        if (properties[i].propertyStatus == 'R') {
            rentedCount++;
            double calculatedPrice = properties[i].areaOfProperty * properties[i].pricePerSquareMeter;
            int cIndex = findContractorIndex(properties[i].assignedContractorId);

            printf("\nProperty ID       : %d\n", properties[i].propertyId);
            printf("  Address         : %s\n", properties[i].propertyAddress);
            printf("  Calculated Rent : Rs. %.2lf\n", calculatedPrice);
            
            if (cIndex != -1) {
                printf("  Assigned Contractor Details:\n");
                printf("    - ID          : %d\n", contractors[cIndex].contractorId);
                printf("    - Name        : %s\n", contractors[cIndex].contractorName);
                printf("    - Contact     : %s\n", contractors[cIndex].contractorNumber);
            }
            printf("----------------------------------------------------------------------------------\n");
        }
    }

    if (rentedCount == 0) {
        printf("\n[Notice] No properties have been marked as rented yet.\n");
    }
    printf("---------------------------------- End of Report ---------------------------------\n");
}

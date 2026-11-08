#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 100

// Product Structure Definition
typedef struct {
    int id;
    int quantity;
    char name[50];
    char category[30];
    double price;
    double discount;
    double discountedPrice;
} Product;

// Global Data Storage
Product inventory[MAX_PRODUCTS];
int productCount = 0;

// Function Declarations
void productMenu();
void addProduct();
void updateProducts();
void deleteProduct();
void checkQuantity();
void generateReport();
void discountedReport();
int findProductIndex(int id);

int main() {
    productMenu();
    return 0;
}

// Product Menu Interface
void productMenu() {
    int select = 0;
    do {
        printf("\n=================== INVENTORY MANAGEMENT SYSTEM ===================\n");
        printf("1. Add Products\n");
        printf("2. Update Product Details\n");
        printf("3. Delete Product\n");
        printf("4. Check Product Quantity\n");
        printf("5. Generate Inventory Reports\n");
        printf("6. Generate Discounted Inventory Reports\n");
        printf("7. Exit System\n");
        printf("===================================================================\n");

        printf("Enter your selection (1-7): ");
        if (scanf("%d", &select) != 1) {
            printf("\n[Error] Invalid input format. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (select) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProducts();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                checkQuantity();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                discountedReport();
                break;
            case 7:
                printf("\n................... System Exiting ...................\n");
                printf("................... Thank You! .......................\n");
                break;
            default:
                printf("\n[Error] Invalid Selection! Please choose an option between 1 and 7.\n");
                break;
        }
    } while (select != 7);
}

// Helper function to find product index by ID
int findProductIndex(int id) {
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Add Product Function
void addProduct() {
    char option;
    while (productCount < MAX_PRODUCTS) {
        printf("\n------------------------- Add Product Details -------------------------\n");
        int id;
        printf("Enter the ID of Product: ");
        scanf("%d", &id);

        if (findProductIndex(id) != -1) {
            printf("\n[Error] Product ID %d already exists! Please use a unique ID.\n", id);
            continue;
        }

        inventory[productCount].id = id;
        getchar(); // Clear newline buffer

        printf("Enter the Name of Product: ");
        fgets(inventory[productCount].name, sizeof(inventory[productCount].name), stdin);
        inventory[productCount].name[strcspn(inventory[productCount].name, "\n")] = 0; // Remove trailing newline

        printf("Enter the Category of Product: ");
        fgets(inventory[productCount].category, sizeof(inventory[productCount].category), stdin);
        inventory[productCount].category[strcspn(inventory[productCount].category, "\n")] = 0;

        printf("Enter the Quantity of Product: ");
        scanf("%d", &inventory[productCount].quantity);

        printf("Enter the Price of Product: ");
        scanf("%lf", &inventory[productCount].price);

        do {
            printf("Enter the Discount (0 - 100) of Product: ");
            scanf("%lf", &inventory[productCount].discount);
            if (inventory[productCount].discount < 0 || inventory[productCount].discount > 100) {
                printf("[Error] Discount must be between 0 and 100.\n");
            }
        } while (inventory[productCount].discount < 0 || inventory[productCount].discount > 100);

        productCount++;
        printf("\n[Success] Product details successfully added! Total products: %d\n", productCount);

        if (productCount == MAX_PRODUCTS) {
            printf("\n[Notice] Maximum inventory storage limit reached.\n");
            return;
        }

        printf("\nDo you want to add another product? (y/n): ");
        scanf(" %c", &option);
        if (tolower(option) == 'n') {
            break;
        }
    }
}

// Update Product Function
void updateProducts() {
    if (productCount == 0) {
        printf("\n[Error] No products available in inventory to update.\n");
        return;
    }

    int pId;
    printf("\n------------------------- Update Product Details -------------------------\n");
    printf("Enter the Product ID to Update: ");
    scanf("%d", &pId);

    int index = findProductIndex(pId);
    if (index == -1) {
        printf("\n[Error] Product ID %d not found!\n", pId);
        return;
    }

    printf("Enter the new quantity for Product %d: ", pId);
    scanf("%d", &inventory[index].quantity);

    do {
        printf("Enter the new discount (0-100) for Product %d: ", pId);
        scanf("%lf", &inventory[index].discount);
        if (inventory[index].discount < 0 || inventory[index].discount > 100) {
            printf("[Error] Discount must be between 0 and 100.\n");
        }
    } while (inventory[index].discount < 0 || inventory[index].discount > 100);

    printf("\n[Success] Product ID %d details updated successfully!\n", pId);
    printf("  - New Quantity : %d\n", inventory[index].quantity);
    printf("  - New Discount : %.2lf%%\n", inventory[index].discount);
}

// Delete Product Function
void deleteProduct() {
    if (productCount == 0) {
        printf("\n[Error] No products available in inventory to delete.\n");
        return;
    }

    int deleteId;
    printf("\n------------------------- Delete Product -------------------------\n");
    printf("Enter the Product ID to Delete: ");
    scanf("%d", &deleteId);

    int index = findProductIndex(deleteId);
    if (index == -1) {
        printf("\n[Error] Product ID %d not found!\n", deleteId);
        return;
    }

    // Shift elements to the left
    for (int i = index; i < productCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }

    productCount--;
    printf("\n[Success] Product ID %d deleted successfully!\n", deleteId);
}

// Check Quantity Function
void checkQuantity() {
    if (productCount == 0) {
        printf("\n[Error] No products available in inventory.\n");
        return;
    }

    int pId;
    printf("\n------------------------- Check Product Quantity -------------------------\n");
    printf("Enter the Product ID to check quantity: ");
    scanf("%d", &pId);

    int index = findProductIndex(pId);
    if (index == -1) {
        printf("\n[Error] Product ID %d not found!\n", pId);
        return;
    }

    printf("\nProduct ID       : %d\n", inventory[index].id);
    printf("Product Name     : %s\n", inventory[index].name);
    printf("Product Quantity : %d units\n", inventory[index].quantity);
}

// Generate Standard Report Function
void generateReport() {
    if (productCount == 0) {
        printf("\n[Error] No products available to generate report.\n");
        return;
    }

    printf("\n========================= INVENTORY REPORT =========================\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product ID       : %d\n", inventory[i].id);
        printf("Product Name     : %s\n", inventory[i].name);
        printf("Category         : %s\n", inventory[i].category);
        printf("Quantity         : %d\n", inventory[i].quantity);
        printf("Price            : $%.2lf\n", inventory[i].price);
        printf("Discount         : %.2lf%%\n", inventory[i].discount);
        printf("--------------------------------------------------------------------\n");
    }
    printf("******************* End of Inventory Reports *******************\n");
}

// Generate Discounted Report Function
void discountedReport() {
    if (productCount == 0) {
        printf("\n[Error] No products available to generate discounted report.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].discount == 0) {
            inventory[i].discountedPrice = inventory[i].price;
        } else {
            inventory[i].discountedPrice = inventory[i].price - ((inventory[i].price * inventory[i].discount) / 100.0);
        }
    }

    printf("\n===================== DISCOUNTED PRICE REPORT =====================\n");
    for (int i = 0; i < productCount; i++) {
        printf("Product ID       : %d\n", inventory[i].id);
        printf("Product Name     : %s\n", inventory[i].name);
        printf("Category         : %s\n", inventory[i].category);
        printf("Quantity         : %d\n", inventory[i].quantity);
        printf("Original Price   : $%.2lf\n", inventory[i].price);
        printf("Discounted Price : $%.2lf (%.2lf%% off)\n", inventory[i].discountedPrice, inventory[i].discount);
        printf("--------------------------------------------------------------------\n");
    }
    printf("******************* End of Discounted Price Report *******************\n");
}

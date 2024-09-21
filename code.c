#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

// Struct declaration
typedef struct {
    char product_code[MAX];
    char product_name[MAX];
    int rate;
    int quantity;
    char weight[MAX];
    char description[30];
} ITEM;

ITEM item;

// Function to check if a product with the given code is available
int isCodeAvailable(char code[]) {
    FILE *file = fopen("Record.txt", "r");
    if (!file) {
        return 0; // If file doesn't exist
    }
    while (fread(&item, sizeof(item), 1, file)) {
        if (strcmp(code, item.product_code) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to check if a product with a given classification is available
int isCodeAvailableclass(char class[]) {
    FILE *file = fopen("Record.txt", "r");
    if (!file) {
        return 0; // If file doesn't exist
    }
    while (fread(&item, sizeof(item), 1, file)) {
        if (strcmp(class, item.weight) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to check if the product is available in the required quantity
int isProductAvailable(int quantity) {
    FILE *file = fopen("Record.txt", "r");
    if (!file) {
        return 0; // If file doesn't exist
    }
    while (fread(&item, sizeof(item), 1, file)) {
        if (item.quantity >= quantity) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// Function to get a positive integer input
int get_int() {
    int input;
    char ch;
    while (scanf("%d", &input) != 1 || input <= 0) {
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("Must be a positive integer. Enter a positive integer value: ");
    }
    return input;
}

// Function to add a product
void addProduct() {
    FILE *file = fopen("Record.txt", "ab");
    char code[MAX];
    printf("Enter \"end\" to exit\n\nEnter Product Code: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0) {
        return;
    }
    if (isCodeAvailable(code)) {
        printf("* Product is already there.\n");
        return;
    }
    strcpy(item.product_code, code);
    printf("Enter Product Name: ");
    scanf("%s", item.product_name);
    printf("Enter Product Rate: ");
    item.rate = get_int();
    printf("Enter Quantity: ");
    item.quantity = get_int();
    printf("Enter Classification: ");
    scanf("%s", item.weight);
    printf("Enter Product Description: ");
    scanf(" %29[^\n]", item.description);
    fwrite(&item, sizeof(item), 1, file);
    fclose(file);
}

// Function to display all products
void display() {
    FILE *file = fopen("Record.txt", "rb");
    if (file == NULL) {
        printf("No Product is inserted.\n");
        return;
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("CODE\t||\tNAME\t||\tRATE\t||\tQUANTITY\t||\tCLASS\t||\tDESCRIPTION\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    while (fread(&item, sizeof(item), 1, file)) {
        printf("%s\t||\t%s\t||\t%d\t||\t%d\t\t||\t%s\t||\t%s\n", item.product_code, item.product_name, item.rate, item.quantity, item.weight, item.description);
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

// Function to search for a product by code
void searchcode() {
    FILE *file;
    char code[MAX];
    printf("Enter \"end\" to go back to menu.\n\nEnter the Product Code to search: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0) {
        return;
    }
    if (!isCodeAvailable(code)) {
        printf("* Product code not found.\n");
        return;
    }
    printf("Product Information\n");
    file = fopen("Record.txt", "rb");
    while (fread(&item, sizeof(item), 1, file)) {
        if (strcmp(item.product_code, code) == 0) {
            printf("Product Code:        %s\n", item.product_code);
            printf("Name of Product:     %s\n", item.product_name);
            printf("Rate of Product (RS): %d\n", item.rate);
            printf("Product Weight:      %s\n", item.weight);
            printf("Product Description: %s\n", item.description);
            break;
        }
    }
    fclose(file);
}

// Function to search for a product by classification
void searchclass() {
    FILE *file;
    char classification[MAX];
    printf("Enter \"end\" to go back to menu.\n\nEnter the Classification to search: ");
    scanf("%s", classification);
    if (strcmp(classification, "end") == 0) {
        return;
    }
    if (!isCodeAvailableclass(classification)) {
        printf("* Product with this classification not found.\n");
        return;
    }
    printf("Product Information\n");
    file = fopen("Record.txt", "rb");
    printf("------------------------------------------------------------------------------------------------------\n");
    printf("CODE\t||\tNAME\t||\tRATE\t||\tQUANTITY\t||\tCLASS\t||\tDESCRIPTION\n");
    printf("------------------------------------------------------------------------------------------------------\n");
    while (fread(&item, sizeof(item), 1, file)) {
        if (strcmp(item.weight, classification) == 0) {
            printf("%s\t||\t%s\t||\t%d\t||\t%d\t\t||\t%s\t||\t%s\n", item.product_code, item.product_name, item.rate, item.quantity, item.weight, item.description);
        }
    }
    printf("------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

// Function to delete a product record
void deleteRecord() {
    FILE *file1, *file2;
    char code[MAX];
    display();
    printf("Enter the Product Code to delete: ");
    scanf("%s", code);
    if (!isCodeAvailable(code)) {
        printf("* Product not available.\n");
        return;
    }
    file1 = fopen("Record.txt", "rb");
    file2 = fopen("tempfile.txt", "wb");
    while (fread(&item, sizeof(item), 1, file1)) {
        if (strcmp(item.product_code, code) != 0) {
            fwrite(&item, sizeof(item), 1, file2);
        }
    }
    fclose(file1);
    fclose(file2);
    file1 = fopen("Record.txt", "wb");
    file2 = fopen("tempfile.txt", "rb");
    while (fread(&item, sizeof(item), 1, file2)) {
        fwrite(&item, sizeof(item), 1, file1);
    }
    fclose(file1);
    fclose(file2);
    printf("* Product deleted successfully!\n");
}

// Function to update a product
void updateProduct() {
    FILE *file1, *file2;
    char code[MAX];
    printf("Enter the Product Code to update the record: ");
    scanf("%s", code);
    if (!isCodeAvailable(code)) {
        printf("* No product found for update.\n");
        return;
    }
    file1 = fopen("Record.txt", "rb");
    file2 = fopen("tempfile.txt", "wb");
    while (fread(&item, sizeof(item), 1, file1)) {
        if (strcmp(item.product_code, code) == 0) {
            printf("Updating data for the previous product %s\n", code);
            printf("Enter Product Name: ");
            scanf("%s", item.product_name);
            printf("Enter Product Rate: ");
            item.rate = get_int();
            printf("Enter Quantity: ");
            item.quantity = get_int();
            printf("Enter Classification: ");
            scanf("%s", item.weight);
            printf("Enter Product Description: ");
            scanf(" %29[^\n]", item.description);
            fwrite(&item, sizeof(item), 1, file2);
        } else {
            fwrite(&item, sizeof(item), 1, file2);
        }
    }
    fclose(file1);
    fclose(file2);
    file1 = fopen("Record.txt", "wb");
    file2 = fopen("tempfile.txt", "rb");
    while (fread(&item, sizeof(item), 1, file2)) {
        fwrite(&item, sizeof(item), 1, file1);
    }
    fclose(file1);
    fclose(file2);
    printf("* Product updated successfully!\n");
}

// Function to sell a product
void saleProduct() {
    FILE *file1, *file2;
    char code[MAX];
    int quantity;
    printf("Enter the Product Code: ");
    scanf("%s", code);
    if (!isCodeAvailable(code)) {
        printf("* No product found for sale.\n");
        return;
    }
    file1 = fopen("Record.txt", "rb");
    file2 = fopen("tempfile.txt", "wb");
    while (fread(&item, sizeof(item), 1, file1)) {
        if (strcmp(item.product_code, code) == 0) {
            printf("Enter the quantity you need: ");
            quantity = get_int();
            if (item.quantity >= quantity) {
                printf("Available quantity is %d. You need %d.\n", item.quantity, quantity);
                item.quantity -= quantity;
                fwrite(&item, sizeof(item), 1, file2);
                printf("Sold product successfully!\n");
            } else {
                printf("The required quantity is unavailable.\n");
                fwrite(&item, sizeof(item), 1, file2);
            }
        } else {
            fwrite(&item, sizeof(item), 1, file2);
        }
    }
    fclose(file1);
    fclose(file2);
    file1 = fopen("Record.txt", "wb");
    file2 = fopen("tempfile.txt", "rb");
    while (fread(&item, sizeof(item), 1, file2)) {
        fwrite(&item, sizeof(item), 1, file1);
    }
    fclose(file1);
    fclose(file2);
}

// Main menu function
void menu() {
    int option;
    while (1) {
        printf("\n\t\t\tWELCOME TO INVENTORY MANAGEMENT SYSTEM\n");
        printf("\n\t\t\t1. Add Product\n");
        printf("\t\t\t2. Display All Products\n");
        printf("\t\t\t3. Search Product by Code\n");
        printf("\t\t\t4. Search Product by Classification\n");
        printf("\t\t\t5. Delete Product\n");
        printf("\t\t\t6. Update Product\n");
        printf("\t\t\t7. Sell Product\n");
        printf("\t\t\t8. Exit\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &option);
        switch (option) {
            case 1: addProduct(); break;
            case 2: display(); break;
            case 3: searchcode(); break;
            case 4: searchclass(); break;
            case 5: deleteRecord(); break;
            case 6: updateProduct(); break;
            case 7: saleProduct(); break;
            case 8: exit(0); break;
            default: printf("Invalid Option.\n"); break;
        }
    }
}

int main() {
    menu();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// Define color macros
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define YELLOW "\033[33m"
#define LIGHT_YELLOW "\033[1;93m"
#define LIGHT_GREEN "\033[92m"
#define LIGHT_RED "\033[91m"

// All Global Variables

char loggedInCustomerName[50];
char loggedInCustomerUsername[50];

// All Function Prototypes

void showAllItems();

// Customer Menu

void cafeDetails() {
    int cafeId, staffCount, ac, capacity;
    float openingTime, closingTime;
    char cafeName[50];

    FILE *file = fopen("cafe_Details.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    printf("\n\t=========================================== Cafe Details ===========================================\n");
    printf("\t| %-8s | %-20s | %-13s | %-13s | %-12s | %-3s | %-9s |\n", "Cafe ID", "Cafe Name", "Opening Time", "Closing Time", "Staff Count", "AC", "Capacity");

    while (fscanf(file, "%d %[^\n]", &cafeId, cafeName) == 2) {
        if (fscanf(file, "%d %f %f %d %d", &capacity, &openingTime, &closingTime, &staffCount, &ac) == 5) {
            printf("\t| %-8d | %-20s | %-13.2f | %-13.2f | %-12d | %-3s | %-9d |\n", cafeId, cafeName, openingTime, closingTime, staffCount, ac ? "Yes" : "No", capacity);
        }
    }

    printf("\t====================================================================================================\n");

    fclose(file);
}

void placeOrder() {
    int id, quantity, type, cafe, orderId, itemQuantity;
    float price;
    char name[50];
    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};
    char confirm;

    // Read the last order ID from the order.txt file
    int newOrderId = 100; // Default order ID
    FILE *orderFile = fopen("order.txt", "r");
    if (orderFile != NULL) {
        int tempOrderId;
        while (fscanf(orderFile, "%d", &tempOrderId) == 1) {
            newOrderId = tempOrderId;
        }
        fclose(orderFile);
        newOrderId++; // Increment to get the next order ID
    }

    printf("\n\tEnter the ID of the item to order: ");
    scanf("%d", &id);

    FILE *file = fopen("item.txt", "r+");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\tError opening temporary file!\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fscanf(file, "%d %49s %d %f %d %d\n", &orderId, name, &quantity, &price, &type, &cafe) != EOF) {
        if (orderId == id) {
            found = 1;
            printf("\tYou selected - %s\n", name);
            printf("\tType: %s\n", types[type]);
            printf("\tCafe: %s\n", cafes[cafe]);
            printf("\tAvailability: %d\n", quantity);

            printf("\tEnter the quantity: ");
            scanf("%d", &itemQuantity);

            if (itemQuantity > quantity) {
                printf("\tInsufficient quantity available!\n");
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }

            printf("\tTotal price: %.2f\n", itemQuantity * price);

            printf("\tPress y to confirm or n to cancel: ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                char timeStr[64];
                strftime(timeStr, sizeof(timeStr), "%c", tm);

                orderFile = fopen("order.txt", "a");
                if (orderFile != NULL) {
                    fprintf(orderFile, "%03d %d %s %s %d %.2f %s\n", newOrderId, orderId, loggedInCustomerName, name, itemQuantity, itemQuantity * price, timeStr);
                    fclose(orderFile);
                }

                // Reduce the quantity and write to temp file
                quantity -= itemQuantity;
                fprintf(tempFile, "%d %s %d %.2f %d %d\n", orderId, name, quantity, price, type, cafe);

                // Print the receipt
                printf(YELLOW"\t\t\t\t\t============================================\n"RESET);
                printf(YELLOW"\t\t\t\t\t                 Invoice                    \n"RESET);
                printf(YELLOW"\t\t\t\t\t============================================\n"RESET);
                printf("\t\t\t\t\tOrder ID: %03d\n", newOrderId);
                printf("\t\t\t\t\t============================================\n");
                printf(LIGHT_YELLOW"\t\t\t\t\tCustomer Name: %s\n"RESET, loggedInCustomerName);
                printf("\t\t\t\t\t============================================\n");
                printf("\t\t\t\t\tItem Name: %s\n", name);
                printf("\t\t\t\t\tQuantity: %d\n", itemQuantity);
                printf("\t\t\t\t\tPrice per Item: %.2f\n", price);
                printf("\t\t\t\t\tTotal Price: %.2f\n", itemQuantity * price);
                printf("\t\t\t\t\tOrder Time: %s\n", timeStr);
                printf("\t\t\t\t\t============================================\n");
                printf(YELLOW"\t\t\t\t\tThanks for ordering with Cafe de BUP\n"RESET);
                printf(YELLOW"\t\t\t\t\t============================================\n"RESET);

                printf(LIGHT_GREEN "\tOrder placed successfully!\n" RESET);
                printf("\tPress any key to continue...");
                _getch(); // Wait for any key press
            } else {
                printf("\tOrder cancelled.\n");
                printf("\tPress any key to continue...");
                _getch(); // Wait for any key press
                // Write the original record to temp file
                fprintf(tempFile, "%d %s %d %.2f %d %d\n", orderId, name, quantity, price, type, cafe);
            }
        } else {
            // Write the original record to temp file
            fprintf(tempFile, "%d %s %d %.2f %d %d\n", orderId, name, quantity, price, type, cafe);
        }
    }

    if (!found) {
        printf("\tItem with ID %d not found!\n", id);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated temp file
    remove("item.txt");
    rename("temp.txt", "item.txt");
}

void rateItem() {
    int itemId, rating, itemIdFromFile, userRating, quantity, type, cafe;
    char user[50], line[100], temp[100], itemName[50];
    float price;
    FILE *ratingFile, *tempFile, *itemFile;

    printf("\n\tEnter the ID of the item you want to rate: ");
    scanf("%d", &itemId);

    // Open item.txt to find the item name
    itemFile = fopen("item.txt", "r");
    if (itemFile == NULL) {
        printf("\tError opening item file!\n");
        return;
    }

    int itemFound = 0;
    while (fscanf(itemFile, "%d %49s %d %f %d %d\n", &itemIdFromFile, itemName, &quantity, &price, &type, &cafe) != EOF) {
        if (itemIdFromFile == itemId) {
            itemFound = 1;
            break;
        }
    }
    fclose(itemFile);

    if (!itemFound) {
        printf("\tItem with ID %d not found!\n", itemId);
        return;
    }

    // Print the selected item name in yellow
        printf("\tYou selected - \033[1;33m%s\033[0m\n", itemName);

    ratingFile = fopen("rating.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (ratingFile != NULL && tempFile != NULL) {
        while (fgets(line, sizeof(line), ratingFile)) {
            sscanf(line, "%d %49s %d", &itemIdFromFile, user, &userRating);
            if (strcmp(user, loggedInCustomerUsername) == 0 && itemId == itemIdFromFile) {
                continue;  // Skip the line if the user has already rated this item
            }
            fputs(line, tempFile);  // Write the line to the temp file
        }
        fclose(ratingFile);
    }

    printf("\n\tEnter your rating (1-5): ");
    printf("\n\t==================== Rate an Item ====================\n");
    printf("\n\t1. Not up to the mark");
    printf("\n\t2. Below average");
    printf("\n\t3. Average");
    printf("\n\t4. Good");
    printf("\n\t5. Excellent");
    printf("\n\t======================================================\n");
    printf("\nYour choice: ");
    scanf("%d", &rating);

    if (rating < 1 || rating > 5) {
        printf("\nInvalid rating. Please enter a number between 1 and 5.\n");
        fclose(tempFile);
        return;
    }

    fprintf(tempFile, "%d %s %d\n", itemId, loggedInCustomerUsername, rating);  // Write the new rating to the temp file
    printf(LIGHT_GREEN "Thank you for rating the item" RESET "\n");

    fclose(tempFile);

    // Replace the original rating file with the temp file
    remove("rating.txt");
    rename("temp.txt", "rating.txt");
}

void compareItem() {
    char itemName[50];
    int id, quantity, type, cafe, ratingId, rating, ratingCount;
    float price, totalRating;
    char name[50], username[50];
    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};
    int found = 0;
    int count = 0;

    printf("\n\tEnter the name of the item to compare: ");
    scanf(" %49s", itemName);

    FILE *file = fopen("item.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    // First pass: count the items with the same name
    while (fscanf(file, "%d %49s %d %f %d %d\n", &id, name, &quantity, &price, &type, &cafe) != EOF) {
        if (strcmp(name, itemName) == 0) {
            count++;
        }
    }

    if (count <= 1) {
        printf("\tThe item is not available in other cafes.\n");
        fclose(file);
        return;
    }

    // Reset the file pointer to the beginning of the file
    rewind(file);

    printf("\033[1;33m"); // Set the text color to yellow
    printf("\n\t===================================== Comparing Items =====================================\n");
    printf("\t%-10s %-15s %-10s %-10s %-10s %-15s %-10s\n", "ID", "Name", "Quantity", "Price", "Type", "Cafe", "Rating");
    printf("\t--------------------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset the text color to default

    // Second pass: print the items with the same name
    while (fscanf(file, "%d %49s %d %f %d %d\n", &id, name, &quantity, &price, &type, &cafe) != EOF) {
        if (strcmp(name, itemName) == 0) {
            totalRating = 0;
            ratingCount = 0;

            FILE *ratingFile = fopen("rating.txt", "r");
            if (ratingFile != NULL) {
                while (fscanf(ratingFile, "%d %49s %d\n", &ratingId, username, &rating) != EOF) {
                    if (id == ratingId) {
                        totalRating += rating;
                        ratingCount++;
                    }
                }
                fclose(ratingFile);
            }

            printf("\t%-10d %-15s %-10d %-10.2f %-10s %-15s ", id, name, quantity, price, types[type], cafes[cafe]);
            if (ratingCount > 0) {
                printf("%-10.2f\n", totalRating / ratingCount);
            } else {
                printf("Not rated\n");
            }

            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("\tNo items named %s found.\n", itemName);
    }

    printf("\033[1;33m"); // Set the text color to yellow
    printf("\t--------------------------------------------------------------------------------------\n");
    printf("\033[0m"); // Reset the text color to default
}

void displayCustomerPage() {
    system("cls");
    int choice;

    while (1) {
        printf("\033[1;33m"); // Set the text color to yellow
        printf("\n\t============================\n");
        printf("\t       Customer Panel       \n");
        printf("\t============================\n");
        printf("\t1. Show All Items\n");
        printf("\t2. Compare an Item\n");
        printf("\t3. Place Order\n");
        printf("\t4. Rate an Item\n");
        printf("\t5. Cafe Details\n");
        printf("\t6. Logout\n");
        printf("\t============================\n");
        printf("\033[0m"); // Reset the text color to default
        printf("\n\tPlease enter your choice: ");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showAllItems();
                // Add a pause here so the user can see the items before the menu is displayed again
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 2:
                compareItem();
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 3:
                placeOrder();
                break;
            case 4:
                rateItem(); // No arguments needed
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 5:
                cafeDetails();
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 6:
                return; // Logout
            default:
                printf("\tInvalid choice. Please try again.\n");
        }
        system("cls"); // Clear the console
    }
}

// Admin Menu

void todaysStatistics() {
    int orderId, foodId, itemQuantity, totalOrders[6] = {0};
    float totalPrice, totalProfit[6] = {0.0};
    char customerName[50], customerUsername[50], itemName[50], orderTime[64];
    char *cafes[] = {"Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};

    FILE *orderFile = fopen("order.txt", "r");
    if (orderFile == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    while (fscanf(orderFile, "%d %d %49s %49s %49s %d %f %63[^\n]", &orderId, &foodId, customerName, customerUsername, itemName, &itemQuantity, &totalPrice, orderTime) != EOF) {
        for (int i = 0; i < 6; i++) {
            if (strcmp(itemName, cafes[i]) == 0) {
                totalOrders[i]++;
                totalProfit[i] += totalPrice;
            }
        }
    }

    printf("\n\t============================================= Today's Statistics =============================================\n");
    printf("\t%-15s %-15s %-15s\n", "Cafe", "Total Orders", "Total Profit");
    printf("\t==============================================================================================================\n");

    for (int i = 0; i < 6; i++) {
        if (totalOrders[i] == 0) {
            printf("\t%-15s %-15s %-15s\n", cafes[i], "No data", "No data");
        } else {
            printf("\t%-15s %-15d %-15.2f\n", cafes[i], totalOrders[i], totalProfit[i]);
        }
    }

    printf("\t==============================================================================================================\n");

    fclose(orderFile);
}

void orderHistory() {
    int orderId, foodId, itemQuantity;
    float totalPrice;
    char customerName[50], customerUsername[50], itemName[50], orderTime[64];

    FILE *orderFile = fopen("order.txt", "r");
    if (orderFile == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    printf("\n\t============================================= Order History =============================================\n");
    printf("\t%-10s %-10s %-15s %-15s %-15s %-10s %-10s \t%-20s\n", "Order ID", "Food ID", "Name", "Username", "Item Name", "Quantity", "Total Price", "Order Time");
    printf("\t=========================================================================================================\n");

    while (fscanf(orderFile, "%d %d %49s %49s %49s %d %f %63[^\n]", &orderId, &foodId, customerName, customerUsername, itemName, &itemQuantity, &totalPrice, orderTime) != EOF) {
        printf("\t%-10d %-10d %-15s %-15s %-15s %-10d %-10.2f %-20s\n", orderId, foodId, customerName, customerUsername, itemName, itemQuantity, totalPrice, orderTime);
    }

    printf("\t=========================================================================================================\n");

    fclose(orderFile);
}

void showAllItems() {
    system("cls");
    int id, quantity, type, cafe, ratingId, rating, ratingCount;
    float price, totalRating;
    char name[50], username[50];
    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};

    FILE *file = fopen("item.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    printf(YELLOW); // Set the text color to yellow
    printf("\n\t===================================== All Items =====================================\n");
    printf("\t%-10s %-15s %-10s %-10s %-10s %-15s %-10s\n", "ID", "Name", "Quantity", "Price", "Type", "Cafe", "Rating");
    printf("\t--------------------------------------------------------------------------------------\n");
    printf(RESET); // Reset the text color to default

    while (fscanf(file, "%d %49s %d %f %d %d\n", &id, name, &quantity, &price, &type, &cafe) != EOF) {
        totalRating = 0;
        ratingCount = 0;

        FILE *ratingFile = fopen("rating.txt", "r");
        if (ratingFile != NULL) {
            while (fscanf(ratingFile, "%d %49s %d\n", &ratingId, username, &rating) != EOF) {
                if (id == ratingId) {
                    totalRating += rating;
                    ratingCount++;
                }
            }
            fclose(ratingFile);
        }

        printf("\t%-10d %-15s %-10d %-10.2f %-10s %-15s ", id, name, quantity, price, types[type], cafes[cafe]);
        if (ratingCount > 0) {
            printf("%-10.2f\n", totalRating / ratingCount);
        } else {
            printf("Not rated\n");
        }
    }

    printf(YELLOW); // Set the text color to yellow
    printf("\t--------------------------------------------------------------------------------------\n");
    printf(RESET); // Reset the text color to default

    fclose(file);
}

void deleteFoodItem() {
    int id, existingId, existingQuantity, existingType, existingCafe;
    float existingPrice;
    char existingName[50];
    char confirm;

    printf("\n\tEnter the item ID of the item you want to delete: ");
    scanf("%d", &id);

    FILE *file = fopen("item.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\tError creating temporary file!\n");
        fclose(file);
        return;
    }

    int itemFound = 0;
    while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
        if (id == existingId) {
            itemFound = 1;
            printf("\n\tItem details:\n");
            printf("\tID: %d\n", existingId);
            printf("\tName: %s\n", existingName);
            printf("\tQuantity: %d\n", existingQuantity);
            printf("\tPrice: %.2f\n", existingPrice);
            printf("\tType: %d\n", existingType);
            printf("\tCafe: %d\n", existingCafe);

            printf("\n\tPress y to confirm deletion or n to cancel: ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y') {
                printf("\tItem deleted successfully!\n");
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                system("cls"); // Clear the console
                continue; // Skip writing this item to the temp file
            } else {
                printf("\tDeletion cancelled.\n");
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                system("cls"); // Clear the console
            }
        }
        fprintf(tempFile, "%d %s %d %.2f %d %d\n", existingId, existingName, existingQuantity, existingPrice, existingType, existingCafe);
    }

    if (!itemFound) {
        printf("\tItem with ID %d not found!\n", id);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated temp file
    remove("item.txt");
    rename("temp.txt", "item.txt");
}

void addFoodItem() {
    int id, quantity, type, cafe, existingId, existingCafe;
    float price, existingPrice;
    char name[50], existingName[50];
    int existingQuantity, existingType;

    printf("\n\tEnter the item ID: ");
    scanf("%d", &id);

    FILE *file = fopen("item.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
        if (id == existingId) {
            fclose(file);
            printf("\tItem ID already exists. Please enter a different item ID.\n");
            return;
        }
    }

    fclose(file);

    printf("\tEnter the item name: ");
    scanf(" %49s", name); // Read up to 49 characters or until a whitespace is encountered

    printf("\tEnter the quantity: ");
    scanf("%d", &quantity);

    printf("\tEnter the price: ");
    scanf("%f", &price);

    printf("\tEnter the type (1. Meal, 2. Snack, 3. Beverage): ");
    scanf("%d", &type);

    printf("\tEnter the Cafe name (1. Vista, 2. Amitie, 3. Staff, 4. AD, 5. MIST Cafe, 6. MIST Snacks): ");
    scanf("%d", &cafe);

    file = fopen("item.txt", "a");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    fprintf(file, "%d %s %d %.2f %d %d\n", id, name, quantity, price, type, cafe);

    fclose(file);

    printf("\tItem added successfully!\n");
    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
    system("cls"); // Clear the console
}

// Display User/Admin Panel

void displayAdminPage() {
    int choice;

    while (1) {
        printf(BOLD YELLOW"\t\t\t\t\t ============================================\n"RESET);
        printf(BOLD YELLOW"\t\t\t\t\t|                                           |\n"RESET);
        printf(BOLD YELLOW"\t\t\t\t\t|            Admin/Staff Panel              |\n"RESET);
        printf(BOLD YELLOW"\t\t\t\t\t|                                           |\n"RESET);
        printf(BOLD YELLOW"\t\t\t\t\t ============================================\n\n"RESET);

        printf("\t1. Add Food Item\n");
        printf("\t2. Delete Food Item\n");
        printf("\t3. Show All Items\n");
        printf("\t4. Today's Statistics\n");
        printf("\t5. Order History\n");
        printf("\t6. Logout\n");
        printf("\t=========================\n");
        printf("\n\tPlease enter your choice: ");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addFoodItem();
                break;
            case 2:
                deleteFoodItem();
                break;
            case 3:
                showAllItems();
                printf("\n\tPress any key to continue...");
                getch(); // waits for the user to press a key
                break;
            case 4:
                todaysStatistics(); // To be Implemented
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 5:
                orderHistory();
                printf("\n\tPress any key to continue...");
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 6:
                return; // Logout
            default:
                printf("\tInvalid choice. Please try again.\n");
        }
        system("cls"); // Clear the console
    }
}

// Login/ Reg

void adminLogin() {
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    printf("\n\tEnter your username: ");
    scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

    printf("\tEnter your password: ");
    scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
        if (strcmp(username, existingUsername) == 0 && strcmp(password, existingPassword) == 0) {
            fclose(file);
            if (isAdmin == 0) {
                printf(LIGHT_RED BOLD "\tInvalid username or password. Please try again.\n" RESET);
                return;
            } else {
                printf(LIGHT_GREEN BOLD "\tLogin successful!\n");
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                system("cls"); // Clear the console
                displayAdminPage();
                return;
            }
        }
    }

    fclose(file);
    printf(LIGHT_RED BOLD "\tInvalid username or password. Please try again.\n" RESET);
}

void customerLogin() {
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    printf("\n\tEnter your username: ");
    scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

    printf("\tEnter your password: ");
    scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

    FILE *file = fopen("credentials.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
        if (strcmp(username, existingUsername) == 0 && strcmp(password, existingPassword) == 0) {
            fclose(file);
            if (isAdmin == 1) {
                printf("\tAdmins cannot log in as customers!\n");
            } else {
                printf(LIGHT_GREEN BOLD "\tLogin successful!\n");
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                system("cls"); // Clear the console

                // Store the logged-in customer's details in global variables
                strcpy(loggedInCustomerName, existingName);
                strcpy(loggedInCustomerUsername, existingUsername);

                displayCustomerPage(); // Show the customer page
            }
            return;
        }
    }

    fclose(file);
    printf(LIGHT_RED BOLD "\tInvalid username or password. Please try again.\n" RESET);
}

void customerRegistration() {
    char name[50];
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    printf("\n\tEnter your name: ");
    scanf(" %49[^\n]", name); // Read up to 49 characters or until a newline is encountered

    printf("\tEnter your username: ");
    scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

    // Check if username already exists
    FILE *file = fopen("credentials.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
            if (strcmp(username, existingUsername) == 0) {
                printf(LIGHT_RED BOLD "\tUsername already exists!\n" RESET);
                fclose(file);
                return;
            }
        }
        fclose(file);
    }

    printf("\tEnter your password: ");
    scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

    file = fopen("credentials.txt", "a");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }

    fprintf(file, "%s %s %s 0\n", name, username, password); // Add a 0 to the end of the line
    fclose(file);

    printf("\tRegistration successful!\n");
    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
    system("cls"); // Clear the console
}

// Home Screen Part

void printHeader() {
    printf("\033[1;36m"); // Set text color to cyan
    printf("\n\n\t\t\t=========================\n");
    printf("\033[1;33m");
    printf("\t\t\t      Cafe de BUP\n");
    printf("\033[0m");
    printf("\t\t\t     Version: 1.0\n");
    printf("\033[1;36m");
    printf("\t\t\t=========================\n\n");
    printf("\033[0m"); // Reset text color
}

void printMenu() {
    printf("\033[1;33m"); // Set text color to yellow
    printf("\t=========================\n");
    printf("\t1. Customer Login\n");
    printf("\t2. Customer Registration\n");
    printf("\t3. Admin/Staff Login\n");
    printf("\t4. Exit\n");
    printf("\t=========================\n");
    printf("\033[0m"); // Reset text color
    printf("\n\tPlease enter your choice: ");
}

// Main Function

int main() {
    int choice;

    while (1) {
        system("cls"); // Clear the console
        printHeader();
        printMenu();

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                customerLogin();
                break;
            case 2:
                customerRegistration();
                break;
            case 3:
                adminLogin();
                break;
            case 4:
                printf("\033[1;32m\n\tThank you for using Cafe de BUP. Goodbye!\033[0m\n");
                return 0;
            default:
                printf("\n\tInvalid choice. Please try again.\n");
                break;
        }

        printf("\n\tPress any key to continue...");
        getch(); // Wait for user input
    }

    return 0;
}
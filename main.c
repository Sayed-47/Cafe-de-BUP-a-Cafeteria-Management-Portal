#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

// Define color macros
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define YELLOW "\033[33m"
#define BOLD_YELLOW "\033[1;33m"
#define BOLD_GREEN BOLD "\033[32m"
#define LIGHT_CYAN "\033[1;36m"
#define LIGHT_YELLOW "\033[1;93m"
#define LIGHT_GREEN "\033[92m"
#define LIGHT_RED "\033[91m"
#define LIGHT_BLACK "\033[90m"
#define LIGHT_BLUE "\033[94m"
#define LIGHT_MAGENTA "\033[95m"
#define LIGHT_WHITE "\033[97m"


// Global variables
char loggedInCustomerName[50];
char loggedInCustomerUsername[50];
int errorFlag = 0; // Flag to indicate if an error occurred
char errorMessage[100]; // Buffer to store the error message

// Global variables to hold username and customer name
char globalUsername[50];
char globalCustomerName[50];
int isLoggedIn = 0;

// Global variables to store logged-in admin details
char loggedInAdminName[50];
char loggedInAdminUsername[50];
int isAdminLoggedIn = 0;

// Function declarations
void printHeader();
void printMenu();
void showAllItems();
void searchCompareItems();
void placeOrder();
void rateItem();
void cafeDetails();
void addFoodItem();
void editFoodItem();
void deleteFoodItem();
void orderHistory();
void displayCustomerPage();
void displayAdminPage();
void changePassword();
void adminLogin();
void customerLogin();
void customerRegistration();

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// All Headers

void displayPasswordInstructions() {
    printf(LIGHT_YELLOW "\n\t===============================================================\n" RESET);
    printf(LIGHT_YELLOW "\t| Password Must Contain:                                       |\n" RESET);
    printf("\t| * Length: 6-20 characters                                    |\n");
    printf("\t| * 1 Uppercase letter (A-Z)                                   |\n");
    printf("\t| * 1 Lowercase letter (a-z)                                   |\n");
    printf("\t| * 1 Digit (0-9)                                              |\n");
    printf("\t| * 1 Special character (@*#)                                  |\n");
    printf(LIGHT_YELLOW "\t===============================================================\n" RESET);
}

void printHeader() {
    printf(LIGHT_CYAN); // Set text color to cyan
    printf("\n\n\t\t\t=========================\n");
    printf(LIGHT_YELLOW);
    printf("\t\t\t      Cafe de BUP\n");
    printf(RESET);
    printf("\t\t\t     Version: 1.0\n");
    printf(LIGHT_CYAN);
    printf("\t\t\t=========================\n\n");
    printf(RESET); // Reset text color
}

void printMenu() {
    printf(LIGHT_YELLOW); // Set text color to yellow
    printf("\t=========================\n");
    printf("\t1. Customer Login\n");
    printf("\t2. Customer Registration\n");
    printf("\t3. Admin/Staff Login\n");
    printf("\t4. Exit\n");
    printf("\t=========================\n");
    printf(RESET); // Reset text color
    printf(LIGHT_CYAN "\n\tPlease enter your choice: " RESET);
}

void displayInstructions() {
    printf(LIGHT_YELLOW "\n\t===============================================================\n" RESET);
    printf(LIGHT_YELLOW "\t| Username Instructions:       | Password Must Contain:       |\n" RESET);
    printf("\t| * No special characters      | * Length: 6-20 characters    |\n");
    printf("\t| * Can contain A-Z, a-z, 0-9  | * 1 Uppercase letter (A-Z)   |\n");
    printf("\t| * Cannot start with a digit  | * 1 Lowercase letter (a-z)   |\n");
    printf("\t|                              | * 1 Digit (0-9)              |\n");
    printf("\t|                              | * 1 Special character (@*#)  |\n");
    printf(LIGHT_YELLOW "\t===============================================================\n" RESET);
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
        printf("\t2. Search/Compare an Item\n");
        printf("\t3. Place Order\n");
        printf("\t4. Rate an Item\n");
        printf("\t5. Cafe Details\n");
        printf("\t6. Change Password\n"); // New option for changing password
        printf("\t7. Logout\n"); // Shifted logout option
        printf("\t============================\n");
        printf("\033[0m"); // Reset the text color to default
        printf(LIGHT_CYAN "\n\tPlease enter your choice: " RESET);

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showAllItems();
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 2:
                searchCompareItems();
                break;
            case 3:
                placeOrder();
                break;
            case 4:
                rateItem(); // No arguments needed
                break;
            case 5:
                cafeDetails();
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 6:
                changePassword(); // Call the change password function
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To consume the newline character left over by scanf
                getchar(); // To capture the next character the user enters
                break;
            case 7:
                printf("\033[92m\n\tLogged Out!\033[0m\n"); // Light green color for "Logged Out"
                Sleep(1500); // Wait for 1500 milliseconds
                system("cls"); // Clear the console
                printHeader(); // Show the main page
                printMenu();
                return; // Logout
            default:
                printf(LIGHT_RED "\tInvalid choice. Please try again.\n" RESET);
        }
        system("cls"); // Clear the console
    }
}

void displayAdminPage() {
    int choice;

    while (1) {
        printf(BOLD_YELLOW); // Set the text color to bold yellow
        printf("\n\t============================\n");
        printf("\t       Admin/Staff Panel       \n");
        printf("\t============================\n");
        printf("\t1. Add Food Item\n");
        printf("\t2. Edit Food Item\n");
        printf("\t3. Delete Food Item\n");
        printf("\t4. Show All Items\n");
        printf("\t5. Search/Compare Items\n"); // Updated option for searchCompareItems
        printf("\t6. Order History\n");
        printf("\t7. Change Password\n"); // New option for changing password
        printf("\t8. Logout\n"); // Option for logout
        printf("\t============================\n");
        printf(RESET); // Reset the text color to default
        printf(LIGHT_CYAN "\n\tPlease enter your choice: " RESET);

        scanf("%d", &choice);
        clearInputBuffer(); // Clear the input buffer
        switch (choice) {
            case 1:
                addFoodItem();
                break;
            case 2:
                editFoodItem(); // Function to edit food item
                break;
            case 3:
                deleteFoodItem();
                break;
            case 4:
                showAllItems();
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getch(); // waits for the user to press a key
                break;
            case 5:
                searchCompareItems(); // Call the new function
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getch(); // waits for the user to press a key
                break;
            case 6:
                orderHistory();
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To capture the next character the user enters
                break;
            case 7:
                changePassword(); // Call the change password function
                break;
            case 8:
                printf(LIGHT_GREEN BOLD"\n\tLogged out!\n" RESET);
                Sleep(1500); // Wait for 1.5 seconds
                system("cls"); // Clear the console
                return; // Logout
            default:
                printf(LIGHT_RED BOLD"\n\tInvalid choice. Please try again.\n" RESET);
                Sleep(1500); // Wait for 1.5 seconds
        }
        system("cls"); // Clear the console
    }
}
// Customer Menu

int isValidPassword(const char *password) {
    int length = strlen(password);
    if (length < 6 || length > 20) return 0;

    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (islower(password[i])) hasLower = 1;
        if (isdigit(password[i])) hasDigit = 1;
        if (strchr("~`!@#$%^&*()+=_-{}[]\\|:;\"'?/<>,.", password[i])) hasSpecial = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

void changePassword() {
    extern char globalUsername[50]; // Assuming this variable is declared elsewhere
    extern char loggedInAdminUsername[50]; // Assuming this variable is declared elsewhere
    extern int isAdminLoggedIn; // Assuming this variable is declared elsewhere

    char currentPassword[50];
    char newPassword[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    system("cls"); // Clear the console
    printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
    printf("\t\t\t    Change Password\n");
    printf("\t\t\t=========================\n" RESET);

    FILE *file = fopen("credentials.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (file == NULL || tempFile == NULL) {
        printf("\tError opening file!\n");
        printf("\n\tPress any key to continue...");
        getch(); // waits for the user to press a key
        return;
    }

    int userFound = 0;
    while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
        if ((isAdminLoggedIn && strcmp(loggedInAdminUsername, existingUsername) == 0) ||
            (!isAdminLoggedIn && strcmp(globalUsername, existingUsername) == 0)) {
            userFound = 1;
            printf(LIGHT_CYAN "\tEnter your current password: " RESET);
            scanf(" %49s", currentPassword); // Read up to 49 characters or until a whitespace is encountered

            if (strcmp(currentPassword, existingPassword) != 0) {
                printf(LIGHT_RED "\n\tIncorrect current password!\n" RESET);
                printf("\n\tPress any key to continue...");
                getch(); // waits for the user to press a key
                fclose(file);
                fclose(tempFile);
                remove("temp.txt");
                return;
            }

            displayPasswordInstructions(); // Show password instructions

            while (1) {
                printf(LIGHT_CYAN "\n\tEnter your new password: " RESET);
                scanf(" %49s", newPassword); // Read up to 49 characters or until a whitespace is encountered

                if (!isValidPassword(newPassword)) {
                    printf(LIGHT_RED "\n\tInvalid password!\n" RESET);
                    printf("\n\t1. Re-Type Password\n");
                    printf("\t2. Home\n");
                    int choice;
                    printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
                    scanf("%d", &choice);
                    if (choice == 2) {
                        system("cls"); // Clear the console
                        fclose(file);
                        fclose(tempFile);
                        remove("temp.txt");
                        return; // Go back to home
                    }
                    system("cls"); // Clear the console
                    printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
                    printf("\t\t\t    Change Password\n");
                    printf("\t\t\t=========================\n\n" RESET);
                    printf(LIGHT_CYAN "\tEnter your current password: %s\n" RESET, currentPassword);
                    displayPasswordInstructions(); // Show password instructions again
                    continue;
                }

                break;
            }
            fprintf(tempFile, "%s %s %s %d\n", existingName, existingUsername, newPassword, isAdmin); // Write updated password
        } else {
            fprintf(tempFile, "%s %s %s %d\n", existingName, existingUsername, existingPassword, isAdmin); // Write unchanged data
        }
    }

    fclose(file);
    fclose(tempFile);

    if (userFound) {
        remove("credentials.txt");
        rename("temp.txt", "credentials.txt");
        printf(LIGHT_GREEN "\n\tPassword changed successfully!\n" RESET);
    } else {
        remove("temp.txt");
        printf(LIGHT_RED "\n\tUsername not found!\n" RESET);
    }

    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
    system("cls"); // Clear the console
}

void cafeDetails() {
    int cafeId, staffCount, ac, capacity;
    float openingTime, closingTime;
    char cafeName[50];

    FILE *file = fopen("cafe_Details.txt", "r");
    if (file == NULL) {
        printf("\tError opening file!\n");
        return;
    }
    
    printf("\n\t====================================================================================================\n");
    printf("\t %s                                        Cafe Details                                            %s \n", BOLD_YELLOW, RESET);
    printf("\t====================================================================================================\n");
    printf("\t| %s%-8s%s | %s%-20s%s | %s%-13s%s | %s%-13s%s | %s%-12s%s | %s%-3s%s | %s%-9s%s |\n", YELLOW, "Cafe ID", RESET, YELLOW, "Cafe Name", RESET, YELLOW, "Opening Time", RESET, YELLOW, "Closing Time", RESET, YELLOW, "Staff Count", RESET, YELLOW, "AC", RESET, YELLOW, "Capacity", RESET);
    printf("\t----------------------------------------------------------------------------------------------------\n");
    
    while (fscanf(file, "%d %[^\n]", &cafeId, cafeName) == 2) {
        if (fscanf(file, "%d %f %f %d %d", &capacity, &openingTime, &closingTime, &staffCount, &ac) == 5) {
            printf("\t| %-8d | %-20s | %-13.2f | %-13.2f | %-12d | %-3s | %-9d |\n", cafeId, cafeName, openingTime, closingTime, staffCount, ac ? "Yes" : "No", capacity);
        }
    }
    
    printf("\t====================================================================================================\n");
    fclose(file);
}

void placeOrder() {
    FILE *file;
    int itemId, itemIdFromFile, quantity, itemQuantity, type, cafe;
    char itemName[50], selectedItemName[50];
    float price, totalPrice;
    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};
    int orderId = 0;
    char line[256];
    char confirm, orderMore;
    char customerName[50];
    char billDate[100];
    float pay, change;

    // Check if the user is already logged in
    if (!isLoggedIn) {
        printf(LIGHT_RED "You need to log in first.\n" RESET);
        return;
    }

    do {
        // Loop until a valid item ID is entered
        while (1) {
            // Ask for item ID
            printf(LIGHT_CYAN "\n\tEnter item ID: " RESET);
            scanf("%d", &itemId);

            // Open item.txt to find the item details
            file = fopen("item.txt", "r");
            if (file == NULL) {
                printf(LIGHT_RED "\n\tError opening item file!\n" RESET);
                return;
            }

            int itemFound = 0;
            while (fscanf(file, "%d %49s %d %f %d %d\n", &itemIdFromFile, itemName, &itemQuantity, &price, &type, &cafe) != EOF) {
                if (itemIdFromFile == itemId) {
                    itemFound = 1;
                    strcpy(selectedItemName, itemName); // Store the selected item name
                    break;
                }
            }
            fclose(file);

            if (itemFound) {
                break; // Exit the loop if a valid item ID is found
            } else {
                printf(LIGHT_RED "\n\tItem with ID %d not found!\n" RESET, itemId);
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To consume the newline character left by previous scanf
                getchar(); // To wait for the user to press any key
            }
        }

        // Show item details
        printf("\n\tYou selected - \033[1;33m%s\033[0m\n", selectedItemName);
        printf("\n\t%-10s %-15s %-10s %-10s %-10s %-15s\n", "ID", "Name", "Quantity", "Price", "Type", "Cafe");
        printf("\t%-10d %-15s %-10d %-10.2f %-10s %-15s\n", itemId, selectedItemName, itemQuantity, price, types[type], cafes[cafe]);

        // Loop until a valid quantity is entered
        while (1) {
            // Ask for quantity
            printf(LIGHT_CYAN "\n\tEnter quantity: " RESET);
            scanf("%d", &quantity);

            if (quantity > itemQuantity) {
                printf(LIGHT_RED "\n\tNot enough units available. Available quantity: %d\n" RESET, itemQuantity);
                printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
                getchar(); // To consume the newline character left by previous scanf
                getchar(); // To wait for the user to press any key
            } else {
                break; // Exit the loop if a valid quantity is entered
            }
        }

        // Calculate total price
        totalPrice = price * quantity;

        // Display per item price and total price
        printf("\n\tPer item price: %.2f\n", price);
        printf("\tTotal price: %.2f\n", totalPrice);

        // Ask for confirmation
        printf(LIGHT_YELLOW "\n\tDo you want to confirm the order? (Y/n): " RESET);
        scanf(" %c", &confirm);

        if (confirm != 'Y' && confirm != 'y') {
            printf(LIGHT_RED "\n\tOrder cancelled.\n" RESET);
        } else {
            // Get the current time
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            strftime(billDate, sizeof(billDate), "%I.%M %p %d-%m-%y", &tm);

            // Read the last order ID from order.txt
            file = fopen("order.txt", "r");
            if (file != NULL) {
                while (fgets(line, sizeof(line), file)) {
                    sscanf(line, "%d", &orderId);
                }
                fclose(file);
            }
            orderId++;

            // Open the file to store order data
            file = fopen("order.txt", "a");
            if (file == NULL) {
                printf(LIGHT_YELLOW "\tError opening file!\n" RESET);
                exit(1);
            }

            // Write order data to the file in a single line
            fprintf(file, "%d %d %s %s %s %d %.2f %.2f %s\n", orderId, itemId, globalCustomerName, globalUsername, selectedItemName, quantity, price, totalPrice, billDate);

            // Close the file
            fclose(file);

            // Update the item quantity in item.txt
            file = fopen("item.txt", "r");
            if (file == NULL) {
                printf(LIGHT_RED "\tError opening item file!\n" RESET);
                return;
            }

            FILE *tempFile = fopen("temp.txt", "w");
            if (tempFile == NULL) {
                printf(LIGHT_RED "\tError opening temporary file!\n" RESET);
                fclose(file);
                return;
            }

            while (fscanf(file, "%d %49s %d %f %d %d\n", &itemIdFromFile, itemName, &itemQuantity, &price, &type, &cafe) != EOF) {
                if (itemIdFromFile == itemId) {
                    itemQuantity -= quantity;
                }
                fprintf(tempFile, "%d %s %d %.2f %d %d\n", itemIdFromFile, itemName, itemQuantity, price, type, cafe);
            }

            fclose(file);
            fclose(tempFile);

            // Replace the original item.txt with the updated temp.txt
            remove("item.txt");
            rename("temp.txt", "item.txt");

            // Display order placed successfully message
            printf(LIGHT_GREEN "\n\tOrder placed successfully!\n" RESET);

            // Sleep for 1500 milliseconds
            Sleep(1500);

            // Clear the console
            system("cls");

            // Prepare invoice data
            strcpy(customerName, globalCustomerName);
            pay = totalPrice; // Assuming full payment for simplicity
            change = 0.0f; // Assuming no change for simplicity

            // Display the invoice
            printf(LIGHT_YELLOW"\n\t\t\t\t=================================================\n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t                    Invoice                \n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf("\n");
            printf("\t\t\t\tCustomer Name: %s\n", customerName);
            printf("\t\t\t\tBill Date: %s\n\n", billDate);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t%-30s %-10s %-10s\n", "Item Name", "Quantity", "Price"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf("\t\t\t\t%-30s %-10d %-10.2f\n", selectedItemName, quantity, totalPrice);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf("\t\t\t\tTotal Amount: \t\t\t\t%.2f\n", totalPrice);
            printf("\t\t\t\tPaid Amount: \t\t\t\t%.2f\n", pay);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t-------------------------------------------------\n"RESET);
            printf("\t\t\t\tChange: \t\t\t\t%.2f\n", change);
            printf(LIGHT_YELLOW"\t\t\t\t=================================================\n"RESET);
            printf("\n");
            printf(LIGHT_YELLOW"\t\t\t\t\t  Thanks for staying with us!  \n"RESET);
            printf(LIGHT_YELLOW"\t\t\t\t=================================================\n"RESET);

            // Prompt to press any key to continue
            printf(LIGHT_YELLOW"\n\tPress any key to continue..." RESET);
            getchar(); // To consume the newline character left by previous scanf
            getchar(); // To wait for the user to press any key
        }

        // Ask if the user wants to order another item
        printf(LIGHT_YELLOW "\n\tDo you want to order another item? (Y/n): " RESET);
        scanf(" %c", &orderMore);

    } while (orderMore == 'Y' || orderMore == 'y');
}

void rateItem() {
    int itemId, rating, itemIdFromFile, userRating, quantity, type, cafe;
    char user[50], line[100], temp[100], itemName[50];
    float price;
    FILE *ratingFile, *tempFile, *itemFile;

    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};

    while (1) {
        printf(LIGHT_CYAN "\n\tEnter the ID of the item you want to rate: " RESET);
        scanf("%d", &itemId);

        // Open item.txt to find the item details
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
            printf(LIGHT_RED "\tItem with ID %d not found!\n" RESET, itemId);
            continue;
        }

        // Find the current rating from rating.txt
        ratingFile = fopen("rating.txt", "r");
        int currentRating = 0;
        if (ratingFile != NULL) {
            while (fgets(line, sizeof(line), ratingFile)) {
                sscanf(line, "%d %49s %d", &itemIdFromFile, user, &userRating);
                if (itemIdFromFile == itemId) {
                    currentRating = userRating;
                    break;
                }
            }
            fclose(ratingFile);
        }

        // Print the selected item details and current rating in a tabular format
        printf("\n\tYou selected - %s%s%s\n", YELLOW, itemName, RESET);
        printf(LIGHT_YELLOW "\n\t%-10s %-15s %-10s %-10s %-10s %-15s %-10s\n" RESET, "ID", "Name", "Quantity", "Price", "Type", "Cafe", "Rating");
        printf(LIGHT_YELLOW "\t--------------------------------------------------------------------------------------\n" RESET);
        printf("\t%-10d %-15s %-10d %-10.2f %-10s %-15s %-10d\n", itemId, itemName, quantity, price, types[type], cafes[cafe], currentRating);

        tempFile = fopen("temp.txt", "w");
        ratingFile = fopen("rating.txt", "r");

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

        printf(LIGHT_YELLOW "\n\tRate an Item\n" RESET);
        printf("\t1. Not up to the mark");
        printf("\n\t2. Below average");
        printf("\n\t3. Average");
        printf("\n\t4. Good");
        printf("\n\t5. Excellent\n");
        printf(LIGHT_CYAN "\n\nYour choice: " RESET);
        scanf("%d", &rating);

        if (rating < 1 || rating > 5) {
            printf("\nInvalid rating. Please enter a number between 1 and 5.\n");
            fclose(tempFile);
            continue;
        }

        fprintf(tempFile, "%d %s %d\n", itemId, loggedInCustomerUsername, rating);  // Write the new rating to the temp file
        printf("%s\nThank you for your rating!%s\n", LIGHT_GREEN, RESET);

        fclose(tempFile);

        // Replace the original rating file with the temp file
        remove("rating.txt");
        rename("temp.txt", "rating.txt");

        printf(LIGHT_YELLOW "\nWould you like to rate another item? (y/n): " RESET);
        char choice;
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void searchCompareItems() {
    char itemName[50];
    int id, quantity, type, cafe, ratingId, rating, ratingCount;
    float price, totalRating;
    char name[50], username[50];
    char *types[] = {"", "Meal", "Snack", "Beverage"};
    char *cafes[] = {"", "Vista", "Amitie", "Staff", "AD", "MIST Cafe", "MIST Snacks"};
    int found, itemCount;
    char choice;

    do {
        found = 0;
        itemCount = 0;

        printf(LIGHT_CYAN "\n\tEnter the name of the item to search/compare: " RESET);
        scanf(" %49s", itemName);

        // Convert the search term to lowercase
        toLowerCase(itemName);

        FILE *file = fopen("item.txt", "r");
        if (file == NULL) {
            printf("\tError opening file!\n");
            return;
        }

        // Read through the file and count items with the specified name
        while (fscanf(file, "%d %49s %d %f %d %d\n", &id, name, &quantity, &price, &type, &cafe) != EOF) {
            char lowerName[50];
            strcpy(lowerName, name);
            toLowerCase(lowerName);

            if (strcmp(lowerName, itemName) == 0) {
                itemCount++;
            }
        }

        fclose(file);

        if (itemCount == 0) {
            printf(LIGHT_RED "\n\tNo items named %s found.\n" RESET, itemName);
        } else {
            printf(LIGHT_GREEN "\n\t%d item(s) found.\n" RESET, itemCount);
            printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
            while (getchar() != '\n'); // Clear the input buffer
            getchar(); // Wait for the user to press a key

            // Clear the screen
            system("cls");

            file = fopen("item.txt", "r");
            if (file == NULL) {
                printf("\tError opening file!\n");
                return;
            }

            // Read through the file and display items with the specified name
            while (fscanf(file, "%d %49s %d %f %d %d\n", &id, name, &quantity, &price, &type, &cafe) != EOF) {
                char lowerName[50];
                strcpy(lowerName, name);
                toLowerCase(lowerName);

                if (strcmp(lowerName, itemName) == 0) {
                    if (!found) {
                        printf("\033[1;33m"); // Set the text color to yellow
                        printf("\n\t=========================================================================================\n");
                        printf("\t\t\t\t\tSearch/Compare Item");
                        printf("\n\t=========================================================================================\n");
                        printf("\t%-10s %-15s %-10s %-10s %-10s %-15s %-10s\n", "ID", "Name", "Quantity", "Price", "Type", "Cafe", "Rating");
                        printf("\t--------------------------------------------------------------------------------------\n");
                        printf("\033[0m"); // Reset the text color to default
                        found = 1;
                    }

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
            }

            fclose(file);

            if (found) {
                printf("\033[1;33m"); // Set the text color to yellow
                printf("\t--------------------------------------------------------------------------------------\n");
                printf("\033[0m"); // Reset the text color to default
            }
        }

        printf(LIGHT_CYAN "\n\tDo you want to search/compare another item? (Y/N): " RESET);
        while (getchar() != '\n'); // Clear the input buffer again to handle any extra characters
        choice = getchar();
        while (getchar() != '\n'); // Clear the input buffer again to handle any extra characters

    } while (choice == 'Y' || choice == 'y');
}

// Admin Menu

void orderHistory() {
    int orderId, foodId, itemQuantity;
    float pricePerItem, totalPrice;
    char customerName[50], customerUsername[50], itemName[50], orderTime[64];

    system("cls"); // Clear the terminal

    FILE *orderFile = fopen("order.txt", "r");
    if (orderFile == NULL) {
        printf(LIGHT_RED BOLD "\tError opening file!\n" RESET);
        return;
    }

    printf(BOLD_YELLOW "\t=================================================================================================================================\n" RESET);
    printf(BOLD_YELLOW "\t\t\t\t\t                      Order History                      \n" RESET);
    printf(BOLD_YELLOW "\t=================================================================================================================================\n" RESET);
    printf(BOLD_YELLOW "\t%-10s %-10s %-15s %-15s %-15s %-10s %-10s \t%-10s \t%-20s\n" RESET, "Order ID", "Food ID", "Name", "Username", "Item Name", "Quantity", "Price/Item", "Total Price", "Order Time");
    printf(LIGHT_YELLOW "\t=================================================================================================================================\n" RESET);
    
    while (fscanf(orderFile, "%d %d %49s %49s %49s %d %f %f %63[^\n]", &orderId, &foodId, customerName, customerUsername, itemName, &itemQuantity, &pricePerItem, &totalPrice, orderTime) != EOF) {
        printf("\t%-10d %-10d %-15s %-15s %-15s %-10d %-10.2f \t%-10.2f \t%-20s\n", orderId, foodId, customerName, customerUsername, itemName, itemQuantity, pricePerItem, totalPrice, orderTime);
    }
    
    printf(LIGHT_YELLOW "\t=================================================================================================================================\n" RESET);

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
        printf(LIGHT_YELLOW "\tError opening file!\n" RESET);
        return;
    }

    printf(LIGHT_YELLOW); // Set the text color to light yellow
    printf("\n\t=====================================================================================\n");
    printf("\t\t\t\t\tAll Items List\n");
    printf("\t=====================================================================================\n");
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

    printf(LIGHT_YELLOW); // Set the text color to light yellow
    printf("\t--------------------------------------------------------------------------------------\n");
    printf(RESET); // Reset the text color to default

    fclose(file);
}

void deleteFoodItem() {
    char deleteAnother = 'y';

    while (deleteAnother == 'y' || deleteAnother == 'Y') {
        int id, existingId, existingQuantity, existingType, existingCafe;
        float existingPrice;
        char existingName[50];
        char confirm;

        printf(LIGHT_CYAN "\n\tEnter the item ID of the item you want to delete: " RESET);
        if (scanf("%d", &id) != 1) {
            printf(LIGHT_RED "\n\tInvalid input. Please enter a valid item ID.\n" RESET);
            clearInputBuffer();
            continue;
        }

        FILE *file = fopen("item.txt", "r");
        if (file == NULL) {
            printf(LIGHT_RED "\tError opening file!\n" RESET);
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf(LIGHT_RED "\tError creating temporary file!\n" RESET);
            fclose(file);
            return;
        }

        int itemFound = 0;
        while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
            if (id == existingId) {
                itemFound = 1;
                printf(LIGHT_YELLOW "\n\tItem details:\n" RESET);
                printf("\tID: %d\n" , existingId);
                printf("\tName: %s\n" , existingName);
                printf("\tQuantity: %d\n", existingQuantity);
                printf("\tPrice: %.2f\n", existingPrice);
                printf("\tType: %d\n" , existingType);
                printf("\tCafe: %d\n" , existingCafe);

                printf(LIGHT_YELLOW "\n\tDo you confirm the deletion?(y/n): " RESET);
                scanf(" %c", &confirm);

                if (confirm == 'y' || confirm == 'Y') {
                    printf(LIGHT_GREEN "\n\tItem deleted successfully!\n" RESET);
                    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                    system("cls"); // Clear the console
                    continue; // Skip writing this item to the temp file
                } else {
                    printf(LIGHT_RED "\n\tDeletion cancelled.\n" RESET);
                    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                    system("cls"); // Clear the console
                }
            }
            fprintf(tempFile, "%d %s %d %.2f %d %d\n", existingId, existingName, existingQuantity, existingPrice, existingType, existingCafe);
        }

        if (!itemFound) {
            printf(LIGHT_RED "\n\tItem with ID %d not found!\n" RESET, id);
        }

        fclose(file);
        fclose(tempFile);

        // Replace the original file with the updated temp file
        remove("item.txt");
        rename("temp.txt", "item.txt");

        printf(LIGHT_YELLOW "\n\tDo you want to delete another item? (y/n): " RESET);
        clearInputBuffer();
        deleteAnother = getchar();
    }
}

void editFoodItem() {
    int id, quantity, type, cafe, existingId, existingCafe;
    float price, existingPrice;
    char name[50], existingName[50];
    int existingQuantity, existingType;
    FILE *file, *tempFile;
    char editAnother = 'y';

    while (editAnother == 'y' || editAnother == 'Y') {
        printf(LIGHT_YELLOW "\n\tEnter the item ID to edit: " RESET);
        if (scanf("%d", &id) != 1) {
            printf(LIGHT_RED "\n\tInvalid input. Please enter a valid item ID.\n" RESET);
            clearInputBuffer();
            continue;
        }

        file = fopen("item.txt", "r");
        if (file == NULL) {
            printf(LIGHT_RED "\n\tError opening file!\n" RESET);
            return;
        }

        int idExists = 0;
        while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
            if (id == existingId) {
                idExists = 1;
                break;
            }
        }
        fclose(file);

        if (!idExists) {
            printf(LIGHT_RED "\n\tItem ID does not exist. Please enter a valid item ID.\n" RESET);
            continue;
        }

        printf("\n\tExisting Information:\n");
        printf("\tID: %d\n", existingId);
        printf(LIGHT_YELLOW "\tName: %s\n" RESET, existingName);
        printf("\tQuantity: %d\n", existingQuantity);
        printf("\tPrice: %.2f\n", existingPrice);
        printf("\tType: %d\n", existingType);
        printf("\tCafe: %d\n", existingCafe);

        int choice;
        while (1) {
            printf(LIGHT_YELLOW "\n\tWhich attribute do you want to change?\n" RESET);
            printf(LIGHT_YELLOW "\t1. Quantity\n" RESET);
            printf(LIGHT_YELLOW "\t2. Price\n" RESET);
            printf(LIGHT_YELLOW "\t3. Type\n" RESET);
            printf(LIGHT_YELLOW "\t4. Cafe\n" RESET);
            printf(LIGHT_YELLOW "\tEnter your choice: " RESET);
            if (scanf("%d", &choice) != 1) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid choice.\n" RESET);
                clearInputBuffer();
                continue;
            }

            switch (choice) {
                case 1:
                    printf(LIGHT_YELLOW "\tEnter new quantity: " RESET);
                    if (scanf("%d", &quantity) != 1) {
                        printf(LIGHT_RED "\n\tInvalid input. Please enter a valid quantity.\n" RESET);
                        clearInputBuffer();
                        continue;
                    }
                    existingQuantity = quantity;
                    break;
                case 2:
                    printf(LIGHT_YELLOW "\tEnter new price: " RESET);
                    if (scanf("%f", &price) != 1) {
                        printf(LIGHT_RED "\n\tInvalid input. Please enter a valid price.\n" RESET);
                        clearInputBuffer();
                        continue;
                    }
                    existingPrice = price;
                    break;
                case 3:
                    printf(LIGHT_YELLOW "\tEnter new type (1. Meal, 2. Snack, 3. Beverage): " RESET);
                    if (scanf("%d", &type) != 1 || type < 1 || type > 3) {
                        printf(LIGHT_RED "\n\tInvalid input. Please enter a valid type (1, 2, or 3).\n" RESET);
                        clearInputBuffer();
                        continue;
                    }
                    existingType = type;
                    break;
                case 4:
                    printf(LIGHT_YELLOW "\tEnter new Cafe name (1. Vista, 2. Amitie, 3. Staff, 4. AD, 5. MIST Cafe, 6. MIST Snacks): " RESET);
                    if (scanf("%d", &cafe) != 1 || cafe < 1 || cafe > 6) {
                        printf(LIGHT_RED "\n\tInvalid input. Please enter a valid Cafe name (1 to 6).\n" RESET);
                        clearInputBuffer();
                        continue;
                    }
                    existingCafe = cafe;
                    break;
                default:
                    printf(LIGHT_RED "\n\tInvalid choice. Please try again.\n" RESET);
                    continue;
            }
            break;
        }

        file = fopen("item.txt", "r");
        tempFile = fopen("temp.txt", "w");
        if (file == NULL || tempFile == NULL) {
            printf(LIGHT_RED "\n\tError opening file!\n" RESET);
            return;
        }

        while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
            if (existingId == id) {
                fprintf(tempFile, "%d %s %d %.2f %d %d\n", existingId, existingName, existingQuantity, existingPrice, existingType, existingCafe);
            } else {
                fprintf(tempFile, "%d %s %d %.2f %d %d\n", existingId, existingName, existingQuantity, existingPrice, existingType, existingCafe);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("item.txt");
        rename("temp.txt", "item.txt");

        printf("\n" LIGHT_GREEN BOLD "\tItem edited successfully!\n" RESET);
        Sleep(1500);

        printf(LIGHT_YELLOW "\n\tDo you want to edit another item? (y/n): " RESET);
        clearInputBuffer();
        editAnother = getchar();
    }
}

void addFoodItem() {
    char addAnother = 'y';

    while (addAnother == 'y' || addAnother == 'Y') {
        int id, quantity, type, cafe, existingId, existingCafe;
        float price, existingPrice;
        char name[50], existingName[50];
        int existingQuantity, existingType;
        FILE *file;

        while (1) {
            printf(LIGHT_CYAN "\n\tEnter the item ID: " RESET);
            if (scanf("%d", &id) != 1) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid item ID.\n" RESET);
                clearInputBuffer();
                continue;
            }

            file = fopen("item.txt", "r");
            if (file == NULL) {
                printf(LIGHT_RED "\n\tError opening file!\n" RESET);
                return;
            }

            int idExists = 0;
            while (fscanf(file, "%d %49s %d %f %d %d\n", &existingId, existingName, &existingQuantity, &existingPrice, &existingType, &existingCafe) != EOF) {
                if (id == existingId) {
                    idExists = 1;
                    break;
                }
            }
            fclose(file);

            if (idExists) {
                printf(LIGHT_RED "\n\tItem ID already exists. Please enter a different item ID.\n" RESET);
                continue;
            }

            break;
        }

        printf(LIGHT_CYAN "\tEnter the item name: " RESET);
        scanf(" %49s", name);

        while (1) {
            printf(LIGHT_CYAN "\tEnter the quantity: " RESET);
            if (scanf("%d", &quantity) != 1) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid quantity.\n" RESET);
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (1) {
            printf(LIGHT_CYAN "\tEnter the price: " RESET);
            if (scanf("%f", &price) != 1) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid price.\n" RESET);
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (1) {
            printf(LIGHT_CYAN "\tEnter the type (1. Meal, 2. Snack, 3. Beverage): " RESET);
            if (scanf("%d", &type) != 1 || type < 1 || type > 3) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid type (1, 2, or 3).\n" RESET);
                clearInputBuffer();
                continue;
            }
            break;
        }

        while (1) {
            printf(LIGHT_CYAN "\tEnter the Cafe name (1. Vista, 2. Amitie, 3. Staff, 4. AD, 5. MIST Cafe, 6. MIST Snacks): " RESET);
            if (scanf("%d", &cafe) != 1 || cafe < 1 || cafe > 6) {
                printf(LIGHT_RED "\n\tInvalid input. Please enter a valid Cafe name (1 to 6).\n" RESET);
                clearInputBuffer();
                continue;
            }
            break;
        }

        file = fopen("item.txt", "a");
        if (file == NULL) {
            printf(LIGHT_RED "\n\tError opening file!\n" RESET);
            return;
        }

        fprintf(file, "%d %s %d %.2f %d %d\n", id, name, quantity, price, type, cafe);
        fclose(file);

        printf("\n" LIGHT_GREEN BOLD "\tItem added successfully!\n" RESET);
        Sleep(1500);

        printf(LIGHT_YELLOW "\n\tDo you want to add another item? (y/n): " RESET);
        clearInputBuffer();
        addAnother = getchar();
    }
}

// Function definitions

int isValidUsername(const char *username) {
    int length = strlen(username);

    // Check if the username starts with a digit
    if (isdigit(username[0])) return 0;

    // Check for special characters and validate allowed characters
    for (int i = 0; i < length; i++) {
        if (!isalnum(username[i])) return 0; // Not alphanumeric
    }

    return 1; // Valid username
}

void customerLogin() {
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    system("cls"); // Clear the console
    printf(LIGHT_YELLOW "\n\n\t\t\t==================\n");
    printf("\t\t\t  Customer Login\n");
    printf("\t\t\t==================\n\n" RESET);

    while (1) {
        printf(LIGHT_CYAN "\n\tEnter your username: " RESET);
        scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

        printf(LIGHT_CYAN "\tEnter your password: " RESET);
        scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

        FILE *file = fopen("credentials.txt", "r");
        if (file == NULL) {
            printf("\n\tError opening file!\n");
            printf("\n\tPress any key to continue...");
            getch(); // waits for the user to press a key
            return;
        }

        int validCredentials = 0;
        while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
            if (strcmp(username, existingUsername) == 0 && strcmp(password, existingPassword) == 0 && isAdmin == 0) {
                validCredentials = 1;
                break;
            }
        }
        fclose(file);

        if (validCredentials) {
            // Store the username and customer name globally
            strcpy(globalUsername, existingUsername);
            strcpy(globalCustomerName, existingName);
            isLoggedIn = 1;

            printf(LIGHT_GREEN "\n\tLogin successful!\n" RESET);
            Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
            system("cls"); // Clear the console
            displayCustomerPage(); // Call the customer page function
            return;
        } else {
            printf(LIGHT_RED "\n\tInvalid username or password!\n" RESET);
            printf("\n\t1. Re-Type Credentials\n");
            printf("\t2. Home\n");
            int choice;
            printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
            scanf("%d", &choice);
            if (choice == 2) {
                system("cls"); // Clear the console
                return; // Go back to home
            }
            system("cls"); // Clear the console
            printf(LIGHT_YELLOW "\n\n\t\t\t==================\n");
            printf("\t\t\t  Customer Login\n");
            printf("\t\t\t==================\n\n" RESET);
        }
    }
}

void customerRegistration() {
    char name[50];
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    system("cls"); // Clear the console
    printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
    printf("\t\t\t  Customer Registration\n");
    printf("\t\t\t=========================\n" RESET);

    displayInstructions();

    printf(LIGHT_CYAN "\n\tEnter your name: " RESET);
    scanf(" %49[^\n]", name); // Read up to 49 characters or until a newline is encountered

    while (1) {
        printf(LIGHT_CYAN "\tEnter your username: " RESET);
        scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

        if (!isValidUsername(username)) {
            printf(LIGHT_RED "\n\tInvalid username!\n" RESET);
            printf("\n\t1. Re-Type Username\n");
            printf("\t2. Home\n");
            int choice;
            printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
            scanf("%d", &choice);
            if (choice == 2) {
                system("cls"); // Clear the console
                return; // Go back to home
            }
            system("cls"); // Clear the console
            printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
            printf("\t\t\t  Customer Registration\n");
            printf("\t\t\t=========================\n\n" RESET);
            displayInstructions();
            printf(LIGHT_CYAN "\n\tEnter your name: %s\n" RESET, name);
            continue;
        }

        // Check if username already exists
        FILE *file = fopen("credentials.txt", "r");
        if (file != NULL) {
            int usernameExists = 0;
            while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
                if (strcmp(username, existingUsername) == 0) {
                    printf(LIGHT_RED "\n\n\tUsername already exists!\n" RESET);
                    printf("\n\t1. Re-Type Username\n");
                    printf("\t2. Home\n");
                    int choice;
                    printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
                    scanf("%d", &choice);
                    if (choice == 2) {
                        system("cls"); // Clear the console
                        return; // Go back to home
                    }
                    usernameExists = 1;
                    system("cls"); // Clear the console
                    printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
                    printf("\t\t\t  Customer Registration\n");
                    printf("\t\t\t=========================\n\n" RESET);
                    displayInstructions();
                    printf(LIGHT_CYAN "\n\tEnter your name: %s\n" RESET, name);
                    break;
                }
            }
            fclose(file);
            if (usernameExists) continue;
        }

        break;
    }

    while (1) {
        printf(LIGHT_CYAN "\tEnter your password: " RESET);
        scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

        if (!isValidPassword(password)) {
            printf(LIGHT_RED "\n\tInvalid password!\n" RESET);
            printf("\n\t1. Re-Type Password\n");
            printf("\t2. Home\n");
            int choice;
            printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
            scanf("%d", &choice);
            if (choice == 2) {
                system("cls"); // Clear the console
                return; // Go back to home
            }
            system("cls"); // Clear the console
            printf(LIGHT_YELLOW "\n\n\t\t\t=========================\n");
            printf("\t\t\t  Customer Registration\n");
            printf("\t\t\t=========================\n\n" RESET);
            displayInstructions();
            printf(LIGHT_CYAN "\n\tEnter your name: %s\n" RESET, name);
            printf(LIGHT_CYAN "\tEnter your username: %s\n" RESET, username);
            continue;
        }

        break;
    }

    FILE *file = fopen("credentials.txt", "a");
    if (file == NULL) {
        printf("\tError opening file!\n");
        printf("\n\tPress any key to continue...");
        getch(); // waits for the user to press a key
        return;
    }

    fprintf(file, "%s %s %s 0\n", name, username, password); // Add a 0 to the end of the line
    fclose(file);

    printf(LIGHT_GREEN "\n\tRegistration successful!\n" RESET);
    Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
    system("cls"); // Clear the console
}

void adminLogin() {
    char username[50];
    char password[50];
    char existingName[50];
    char existingUsername[50];
    char existingPassword[50];
    int isAdmin;

    system("cls"); // Clear the console
    printf(LIGHT_YELLOW "\n\n\t\t\t=====================\n");
    printf("\t\t\t  Admin/Staff Login\n");
    printf("\t\t\t=====================\n\n" RESET);

    while (1) {
        printf(LIGHT_CYAN "\n\tEnter your username: " RESET);
        scanf(" %49s", username); // Read up to 49 characters or until a whitespace is encountered

        printf(LIGHT_CYAN "\tEnter your password: " RESET);
        scanf(" %49s", password); // Read up to 49 characters or until a whitespace is encountered

        FILE *file = fopen("credentials.txt", "r");
        if (file == NULL) {
            printf("\n\tError opening file!\n");
            printf(LIGHT_YELLOW "\n\tPress any key to continue..." RESET);
            getch(); // waits for the user to press a key
            return;
        }

        int validCredentials = 0;
        while (fscanf(file, "%49s %49s %49s %d\n", existingName, existingUsername, existingPassword, &isAdmin) != EOF) {
            if (strcmp(username, existingUsername) == 0 && strcmp(password, existingPassword) == 0) {
                validCredentials = 1;
                break;
            }
        }
        fclose(file);

        if (validCredentials) {
            if (isAdmin == 1) {
                // Store the admin's name and username in global variables
                strcpy(loggedInAdminName, existingName);
                strcpy(loggedInAdminUsername, existingUsername);
                isAdminLoggedIn = 1;

                printf(LIGHT_GREEN "\n\tLogin successful!\n" RESET);
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                system("cls"); // Clear the console
                displayAdminPage(); // Call the admin page function
                return;
            } else {
                printf(LIGHT_RED "\n\tInvalid username or password!\n" RESET);
            }
        } else {
            printf(LIGHT_RED "\n\tInvalid username or password!\n" RESET);
        }

        printf("\n\t1. Re-Type Credentials\n");
        printf("\t2. Home\n");
        int choice;
        printf(LIGHT_CYAN "\n\tEnter your choice: " RESET);
        scanf("%d", &choice);
        if (choice == 2) {
            system("cls"); // Clear the console
            return; // Go back to home
        }
        system("cls"); // Clear the console
        printf(LIGHT_YELLOW "\n\n\t\t\t=====================\n");
        printf("\t\t\t  Admin/Staff Login\n");
        printf("\t\t\t=====================\n\n" RESET);
    }
}

int main() {
    int choice;

    while (1) {
        //system("cls"); // Clear the console
        printHeader();
        printMenu();

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer(); // Clear the input buffer
            printf(LIGHT_RED "\n\tInvalid choice. Please try again.\n" RESET);
            Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
            continue;
        }

        clearInputBuffer(); // Clear the input buffer
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
                printf(LIGHT_GREEN "\n\tThank you for using Cafe de BUP.\n" RESET);
                return 0;
            default:
                printf(LIGHT_RED "\n\tInvalid choice. Please try again.\n" RESET);
                Sleep(1500); // Pause for 1500 milliseconds, or 1.5 seconds
                break;
        }
    }

    return 0;
}
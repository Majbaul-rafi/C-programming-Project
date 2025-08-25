#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

typedef struct
{
    int bookingId;
    char name[50];
    char phone[20];
    char carModel[30];
    char service[100];
    float cost;
} Customer;

Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

int loginSystem();
void saveData();
void loadData();
void addBooking();
void viewBookings();
void searchBooking();
void updateBooking();
void deleteBooking();
void generateBill();
void costEstimator();

int loginSystem()
{
    char uid[20], pass[20];

    printf("\n===== LOGIN =====\n");
    printf("User ID: ");
    scanf("%s", uid);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(uid,"admin") == 0 && strcmp(pass,"1234") == 0)
    {
        printf("Login successful!\n");
        return 1;
    }
    else
    {
        printf("Invalid ID or PASSWORD! Exiting...\n");
        return 0;
    }
}

void saveData()
{
    FILE *file = fopen("carwash.txt", "w");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < customerCount; i++)
    {
        fprintf(file, "%d|%s|%s|%s|%s|%.2f\n",
                customers[i].bookingId,
                customers[i].name,
                customers[i].phone,
                customers[i].carModel,
                customers[i].service,
                customers[i].cost);
    }
    fclose(file);
}

void loadData()
{
    FILE *file = fopen("carwash.txt", "r");
    if (!file) return;

    while (fscanf(file, "%d|%49[^|]|%19[^|]|%29[^|]|%99[^|]|%f\n",
                  &customers[customerCount].bookingId,
                  customers[customerCount].name,
                  customers[customerCount].phone,
                  customers[customerCount].carModel,
                  customers[customerCount].service,
                  &customers[customerCount].cost) == 6)
    {
        customerCount++;
    }
    fclose(file);
}

void addBooking()
{
    if (customerCount >= MAX_CUSTOMERS)
    {
        printf("No more bookings can be added.\n");
        return;
    }

    Customer c;
    char extraserv[200] = "";//extra customer service
    int selected[9] = {0};
    float extraCost = 0;

    while (1)
    {
        printf("Enter Booking ID: ");
        scanf("%d", &c.bookingId);
        getchar();

        int duplicate = 0;
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].bookingId == c.bookingId)
            {
                duplicate = 1;
                break;
            }
        }
        if (duplicate)
            printf("This Booking ID already exists! Enter a different ID.\n");
        else
            break;
    }

    printf("Enter Name: ");
    fgets(c.name, sizeof(c.name), stdin);
    c.name[strcspn(c.name, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(c.phone, sizeof(c.phone), stdin);
    c.phone[strcspn(c.phone, "\n")] = '\0';

    printf("Enter Car Model: ");
    fgets(c.carModel, sizeof(c.carModel), stdin);
    c.carModel[strcspn(c.carModel, "\n")] = '\0';

    printf("Enter Service (Basic/Premium/Deluxe): ");
    fgets(c.service, sizeof(c.service), stdin);
    c.service[strcspn(c.service, "\n")] = '\0';

    // base cost
    if (strcmp(c.service, "Basic") == 0)
        c.cost = 3000;
    else if (strcmp(c.service, "Premium") == 0)
    c.cost = 5000;
    else if (strcmp(c.service, "Deluxe") == 0)
     c.cost = 8000;
    else
    c.cost = 3000;

    struct service
    {
        char name[30];
        float cost;
    } extras[] =
    {
        {"Basic wash", 3000}, {"Premium wash", 5000}, {"Deluxe wash", 8000},
        {"Engine Repair", 5000}, {"Brake Repair", 3000}, {"Paint Job", 2000},
        {"Tire Replacement", 4000}, {"Battery Replacement", 3500}, {"Oil Change", 1500}
    };
    int n = 9, choice;

    printf("\n--- Extra Services ---\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s - %.2f tk\n", i+1, extras[i].name, extras[i].cost);
    printf("0. Done\n");

    while (1)
    {
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        if (choice < 1 || choice > n) continue;
        if (selected[choice-1])
        {
            printf("Already selected!\n");
            continue;
        }
        selected[choice-1] = 1;
        extraCost += extras[choice-1].cost;
        if (extraserv[0])
        strcat(extraserv, ", ");
        strcat(extraserv, extras[choice-1].name);
    }
    getchar();

    if (extraserv[0])
    {
        strcat(c.service, " + ");
        strcat(c.service, extraserv);
    }

    c.cost += extraCost;

    customers[customerCount++] = c;
    saveData();
    printf("Booking added successfully!\n");
}

void viewBookings()
{
    if (customerCount == 0)
    {
        printf("No bookings found.\n");
        return;
    }
    for (int i = 0; i < customerCount; i++)
    {
        printf("\nBooking ID: %d\n", customers[i].bookingId);
        printf("Name: %s\n", customers[i].name);
        printf("Phone: %s\n", customers[i].phone);
        printf("Car Model: %s\n", customers[i].carModel);
        printf("Service: %s\n", customers[i].service);
        printf("Cost: %.2f\n", customers[i].cost);
    }
}

void searchBooking()
{
    char search[50];
    int found = 0;

    printf("Enter Booking ID or part of Name to search: ");
    getchar();
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    for (int i = 0; i < customerCount; i++)
    {
        char idStr[10];
        sprintf(idStr, "%d", customers[i].bookingId);

        if (strcmp(search, idStr) == 0 || strstr(customers[i].name,search) != NULL)
        {
            printf("\nBooking found!\n");
            printf("ID: %d\nName: %s\nCar: %s\nService: %s\nCost: %.2f\n",
                   customers[i].bookingId, customers[i].name,
                   customers[i].carModel, customers[i].service, customers[i].cost);
            found = 1;
        }
    }

    if (!found)
        printf("No booking found.\n");
}
void updateBooking()
{
    int id,i;
    printf("Enter Booking ID to update: ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].bookingId == id)
        {
            printf("Enter New Name: ");
            fgets(customers[i].name, sizeof(customers[i].name), stdin);
            customers[i].name[strcspn(customers[i].name, "\n")] = '\0';

            printf("Enter New Phone: ");
            fgets(customers[i].phone, sizeof(customers[i].phone), stdin);
            customers[i].phone[strcspn(customers[i].phone, "\n")] = '\0';

            printf("Enter New Car Model: ");
            fgets(customers[i].carModel, sizeof(customers[i].carModel), stdin);
            customers[i].carModel[strcspn(customers[i].carModel, "\n")] = '\0';

            printf("Enter New Service: ");
            fgets(customers[i].service, sizeof(customers[i].service), stdin);
            customers[i].service[strcspn(customers[i].service, "\n")] = '\0';

            if (strcmp(customers[i].service, "Basic") == 0)
                customers[i].cost = 3000;
            else if
            (strcmp(customers[i].service, "Premium") == 0)
                customers[i].cost = 5000;
            else if
            (strcmp(customers[i].service, "Deluxe") == 0)
                customers[i].cost = 8000;
            else
                customers[i].cost = 3000;

            saveData();
            printf("Booking updated!\n");
            return;
        }
    }
    printf("Booking not found.\n");
}

void deleteBooking()
{
    int id;
    printf("Enter Booking ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].bookingId == id)
        {
            for (int j = i; j < customerCount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            saveData();
            printf("Booking deleted!\n");
            return;
        }
    }
    printf("Booking not found.\n");
}

void generateBill()
{
    int id;
    printf("Enter Booking ID to generate bill: ");
    scanf("%d", &id);
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].bookingId == id)
        {
            printf("\n--- BILL ---\n");
            printf("Name: %s\n", customers[i].name);
            printf("Car Model: %s\n", customers[i].carModel);
            printf("Service: %s\n", customers[i].service);
            printf("Total: %.2f\n", customers[i].cost);
            return;
        }
    }
    printf("Booking not found.\n");
}

void costEstimator()
{
    struct service
    {
        char name[30];
        float cost;
    } extras[] =
    {
        {"Basic wash", 3000}, {"Premium wash", 5000}, {"Deluxe wash", 8000},
        {"Engine Repair", 5000}, {"Brake Repair", 3000}, {"Paint Job", 2000},
        {"Tire Replacement", 4000}, {"Battery Replacement", 3500}, {"Oil Change", 1500}
    };
    int n = 9, choice;
    char serv[200] = "";
    int selected[9] = {0};
    float total = 0;

    printf("\n--- Cost Estimator ---\n");
    for (int i = 0; i < n; i++)
        printf("%d. %s - %.2f tk\n", i+1, extras[i].name, extras[i].cost);
    printf("0. Done\n");

    while (1)
    {
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 0) break;
        if (choice < 1 || choice > n) continue;
        if (selected[choice-1])
        {
            printf("Already selected!\n");
            continue;
        }
        selected[choice-1] = 1;
        total += extras[choice-1].cost;
        if (serv[0])
            strcat(serv, ", ");
        strcat(serv, extras[choice-1].name);
    }
    getchar();

    printf("Selected services: %s\n", serv);
    printf("Estimated total cost: %.2f tk\n", total);
}

int main()
{
    int choice;

    if (!loginSystem())
    return 0;
    loadData();

    while (1)
    {
        printf("\n--- Car Wash Booking System ---\n");
        printf("1. Add Booking\n");
        printf("2. View All Bookings\n");
        printf("3. Search Booking\n");
        printf("4. Update Booking\n");
        printf("5. Delete Booking\n");
        printf("6. Generate Bill\n");
        printf("7. Cost Estimator\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addBooking();
            break;
        case 2:
            viewBookings();
            break;
        case 3:
            searchBooking();
            break;
        case 4:
            updateBooking();
            break;
        case 5:
            deleteBooking();
            break;
        case 6:
            generateBill();
            break;
        case 7:
            costEstimator();
            break;
        case 8:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}

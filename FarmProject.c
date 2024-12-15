#include <stdio.h>
#include <string.h>

// Farm struct
typedef struct {
    char name[50];
    int cows;
    int chickens;
    float income;
} Farm;

void updateLivestock(Farm *farm);  //Passing a pointer to a struct 
                                   //is efficient and allows for direct modification 
void displayFarmDetails(Farm *farm);

int main() {
    // lets say we have 5 farms 
    Farm farms[5] = {
        {"Farm 1", 20, 20, 1000.0},
        {"Farm 2", 30, 15, 1200.0},
        {"Farm 3", 25, 10, 800.0},
        {"Farm 4", 10, 40, 1500.0},
        {"Farm 5", 50, 25, 2000.0}
    };

    int choice;
    while (1) { //infinite loop until the user decides to break
        printf("\nCity Farms Management System\n");
        printf("1. Choose a farm\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 2) {
            printf("Exiting...\n");
            break;
        } else if (choice == 1) {
            int farmIndex;
            printf("Select a farm (1-5): ");
            scanf("%d", &farmIndex); //ask for farm,scan the input into the farm_index

            if (farmIndex < 1 || farmIndex > 5) {
                printf("Invalid farm selection.\n");
                continue;
            }

            Farm *selectedFarm = &farms[farmIndex - 1]; //selectedfarm is a pointer to specific farm in Farm struct

            displayFarmDetails(selectedFarm);

            updateLivestock(selectedFarm);
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// this function is accesing the fields of the struct using farm pointer and displaying it.
void displayFarmDetails(Farm *farm) { 
    printf("\nFarm: %s\n", farm->name); //farm is a pointer  "->" acceses the firls of the struct the farm pointer is pointing to
    printf("Cows: %d\n", farm->cows); 
    printf("Chickens: %d\n", farm->chickens);
    printf("Income: $%.2f\n", farm->income);
}

// this function can update livestock(how many chicken/cows died,bought etc)
void updateLivestock(Farm *farm) {
    char response[10];
    int count;

    printf("Did any chickens die? (yes/no): ");
    scanf("%s", response);
    if (strcmp(response, "yes") == 0) { 
        printf("How many chickens died? ");
        scanf("%d", &count);
        if (count <= farm->chickens) {
            farm->chickens -= count;
        } else {
            printf("not possib;e.\n");
        }
    }

    printf("Did any cows die? (yes/no): ");
    scanf("%s", response);
    if (strcmp(response, "yes") == 0) {
        printf("How many cows died? ");
        scanf("%d", &count);
        if (count <= farm->cows) {
            farm->cows -= count;
        } else {
            printf("not possible.\n");
        }
    }

    char response_buy[10];
    int sold_cows;
    int sold_chickens;

    printf("Do you want to buy chickens or cows? (yes/no): ");
    scanf("%s", response_buy);
    if (strcmp(response_buy, "yes") == 0) {
        // Buying cows
        printf("How many cows do you want to buy? ");
        scanf("%d", &sold_cows);
        if (sold_cows > 0) {
            farm->cows += sold_cows;          // Increase cows in stock
            farm->income -= sold_cows * 50;  // reducing the cost of the cows
            printf("Bought %d cows.\n", sold_cows);
        } else {
            printf("not possible.\n");
        }

        printf("How many chickens do you want to buy? ");
        scanf("%d", &sold_chickens);
        if (sold_chickens > 0) {
            farm->chickens += sold_chickens;          // Increase chickens in stock
            farm->income -= sold_chickens * 20;       // reducing the codt of those chickens
            printf("Bought %d chickens.\n", sold_chickens);
        } else {
            printf("not poosible.\n");
        }
    }
}


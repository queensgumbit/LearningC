#include <stdio.h>
#include <string.h>


typedef struct Cow {
    char name[50];
    int liters_produced;
    int gr_eaten;
    struct Cow *next;



};

typedef struct Chicken{
    char name[50];
    int eggs_layed;
    int gr_eaten;
    struct Chicken *next
};

typedef struct {
    char name[50];
    int chickens;
    int cows;
    float income;
    struct Chicken *chickens;  
    struct Cow *cows;
} Farm;
 

 Farm farms[5] = {
        {"Farm 1", 20, 20, 1000.0},
        {"Farm 2", 30, 15, 1200.0},
        {"Farm 3", 25, 10, 800.0},
        {"Farm 4", 10, 40, 1500.0},
        {"Farm 5", 50, 25, 2000.0}
    };

struct Chicken* add_chicken(struct Farm *farm, char *name);
struct Cow* add_cow(struct Farm *farm, char *name);
struct Chicken* remove_chicken(struct Farm *farm, char *name);
struct Cow* remove_cow(struct Farm *farm, char *name);
void milk_cow(struct Cow *cow, int liters);
void collect_eggs(struct Chicken *chicken, int eggs);
void display_farm(struct Farm *farm);




//Passing a pointer to a struct 
                                   //is efficient and allows for direct modification 
void displayFarmDetails(Farm *farm);

int main() {

    //unit testing

   struct Cow *jon_cow = add_cow("Jon");
   milk_cow(jon_cow, 5);
   struct Cow *len_cow = add_cow("Len");
   milk_cow(jon_cow, 10);
   jon_cow = kill_cow("Jon");
   printf("Deceased cow %s produced: %d liters\n", jon_cow->name, jon_cow->liters);
    

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

            
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

void kill_chicken(struct Farm *farm, char *name) {
    struct Chicken *current = farm->chickens; //to start at the head of the list
    struct Chicken *previous = NULL;          // to keep track of the previous node

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) { // strcmp checks if the names match
            if (previous == NULL) {
                
                *farm->chickens = current->next;
            } else {
                previous->next = current->next;
            }

            printf("Removed chicken: %s\n", current->name);
            free(current); //free the memory of the removed chicken
            return;        
        }
        previous = current;
        current = current->next; //move to the next
    }

    printf("Chicken named '%s' not found.\n", name);
}

void kill_cow(struct Farm *farm, char *name){
    struct Cow *current = farm->cows;
    struct Cow *previous = NULL;
    while(current != NULL){
        if(strcmp(current->name,name)==0){
            if(previous ==NULL){
                *farm->chickens = current->next;
            }
            else{
                previous->next = current->next;
            }
            printf("removed cow: %s\n",current->name);
            free(current);
            return;
        }
        previous = current;
        current = current ->next;
    }
}

void kill_chickens(struct Farm *farm, int num) {
    if (num > farm->chickens) {
        printf("Not enough chickens to remove.\n");
        return;
    }
    farm->chickens -= num;
    printf("%d chickens removed from the farm.\n", num);
}

void kill_cows(struct Farm *farm, int num) {
    if (num > farm->cows) {
        printf("Not enough cows to remove.\n");
        return;
    }
    farm->cows -= num;
    printf("%d cows removed from the farm.\n", num);
}


struct Cow* add_cow(struct Farm *farm, char *name) {
    struct Cow *new_cow = (struct Cow*)malloc(sizeof(struct Cow));
    if (new_cow == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(new_cow->name, name);
    new_cow->liters_produced = 0;
    new_cow->gr_eaten = 0;
    new_cow->next = farm->cows;  
    farm->cows = new_cow;
    farm->cows++;  
    return new_cow;
}

struct Chicken* add_chicken(struct Farm *farm, char *name) {
    struct Chicken *new_chicken = (struct Chicken*)malloc(sizeof(struct Chicken));
    if (new_chicken == NULL) {
        printf("memory allocation failed.\n");
        return NULL;
    }
    strcpy(new_chicken->name, name);
    new_chicken->eggs_layed = 0;
    new_chicken->gr_eaten = 0;
    new_chicken->next = farm->chickens;  
    farm->chickens = new_chicken;
    farm->chickens++;  
    return new_chicken;
}

void displayFarmDetails(Farm *farm) { 
    printf("\nFarm: %s\n", farm->name); //farm is a pointer  "->" acceses the firls of the struct the farm pointer is pointing to
    printf("Cows: %d\n", farm->cows); 
    printf("Chickens: %d\n", farm->chickens);
    printf("Income: $%.2f\n", farm->income);
}

 


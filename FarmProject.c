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
    // farm for testing
    Farm testFarm = {"Test Farm", 0, 0, 0.0, NULL, NULL};

    printf("testing start\n");

    // test: adding cows
    struct Cow* cow1 = add_cow(&testFarm, "Jon");
    struct Cow* cow2 = add_cow(&testFarm, "Sharon");
    if (cow1 && cow2) {
        printf("Cows added: %s, %s\n", cow1->name, cow2->name); //after adding to the struct we acces the name using pointer
    } else {
        printf("Failed to add cows.\n");
    }

    // test: adding chickens
    printf("\n** Testing Add Chicken **\n");
    struct Chicken* chicken1 = add_chicken(&testFarm, "Ella");
    struct Chicken* chicken2 = add_chicken(&testFarm, "Karin");
    if (chicken1 && chicken2) {
        printf("Chickens added: %s, %s\n", chicken1->name, chicken2->name); //same as with the cows
    } else {
        printf("Failed to add chickens.\n");
    }

    // test: milk cow
    printf("\n** Testing Milk Cow **\n");
    milk_cow(cow1, 5);  // Cow jon produces 5 liters
    milk_cow(cow2, 3); // Cow sharon produces 3 liters
    printf("%s produced %d liters.\n", cow1->name, cow1->liters_produced); //accesing the values inside the struct COW.
    printf("%s produced %d liters.\n", cow2->name, cow2->liters_produced);

    // Test collect eggs
    printf("\n** Testing Collect Eggs **\n");
    collect_eggs(chicken1, 3);  //chicken Ella lays 3 eggs
    collect_eggs(chicken2, 5);  //chicken Karin lays 5 eggs
    printf("%s laid %d eggs.\n", chicken1->name, chicken1->eggs_layed); //same as with the cows-above
    printf("%s laid %d eggs.\n", chicken2->name, chicken2->eggs_layed);

    // removing cows
    kill_cow(&testFarm, "Jon");
    struct Cow* currentCow = testFarm.cows; //accesing the cows in the farm
    printf("Remaining cows:\n");
    while (currentCow != NULL) {
        printf("Cow name: %s\n", currentCow->name);
        currentCow = currentCow->next; //we do this to make the pointer to the next item in the struct
    }

    // removing chickens
    kill_chicken(&testFarm, "Karin");
    struct Chicken* currentChicken = testFarm.chickens;
    printf("remaining chickens:\n");
    while (currentChicken != NULL) {
        printf("chticken name: %s\n", currentChicken->name);
        currentChicken = currentChicken->next;
    }

    // displaying all the changes
    printf("\n** Final Farm Details **\n");
    display_farm(&testFarm);

    printf(" end of testing \n");

    return 0;
}

void kill_chicken( Farm *farm, char *name) {
    struct Chicken *current = farm->chickens; //to start at the head of the list
    struct Chicken *previous = NULL;          // To keep track of the previous node

    // Traverse the list to find the chicken
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) { // If names match
            if (previous == NULL) {
                // Removing the head node
                *farm->chickens = current->next;
            } else {
                // Skip the current node
                previous->next = current->next;
            }

            printf("Removed chicken: %s\n", current->name);
            free(current); // Free the removed chicken
            return;        // Exit the function
        }
        previous = current;
        current = current->next; // Move to the next node
    }

    printf("Chicken named '%s' not found.\n", name);
}

void kill_cow( Farm *farm, char *name){
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

void kill_chickens( Farm *farm, int num) {
    if (num > farm->chickens) {
        printf("Not enough chickens to remove.\n");
        return;
        struct Chicken *current = farm->cows;
    while (num > 0 && current != NULL) {
        chicken_now = current;           // storing teh chicken to remove
        current = current->next;        // moving to the next
        free(chicken_now);              // free the memory
        farm->cows-=num;       
        ;
    }
    printf("%d cows removed from the farm.\n", num);
    
    }
    printf("%d chickens removed from the farm.\n", num);
}

void kill_cows( Farm *farm, int num) {
    if (num > farm->cows) {
        printf("Not enough cows to remove.\n");
        return;
    }
    struct Cow *current = farm->cows;
    while (num > 0 && current != NULL) {
        cow_now = current;           // storng the cow to remove
        current = current->next;    // moving to the next
        free(cow_now);              // free the memory
        farm->cows-=num;       
        ;
    }
    printf("%d cows removed from the farm.\n", num);
    
}


struct Cow* add_cow( Farm *farm, char *name) {
    struct Cow *new_cow = (struct Cow*)malloc(sizeof(struct Cow));
    if (new_cow == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    strcpy(new_cow->name, name);
    new_cow->liters_produced = 0;
    new_cow->gr_eaten = 0;
    farm->cows++;  // Increment count
    new_cow->next = farm->cows  // Maintain linked list
    farm->cows = new_cow;  // Update head of the list
    return new_cow;
}

struct Chicken* add_chicken( Farm *farm, char *name) {
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



void milk_cow( Farm *farm,struct Cow *next, char *name, int liters){
     struct Cow *current = farm->cows;
while (current != NULL) {
    if (strcmp(current->name, name) == 0) {//if the names match
        current->liters_produced += liters;
        return;
    }
    current = current->next;
}
printf("Cow named '%s' not found.\n", name);
}


void collected_eggs(Farm *farm,struct Chicken *next, char *name,int eggs ){
    struct Chicken *current = farm->chickens;
while(current != NULL){
    if(strcmp(current->name,name)==0){//if the names match
       current->eggs_layed +=eggs;
       return;
}
   current = current->next;
}

printf("chicken names '%s' not found.\n",name);
}

void displayFarmDetails(Farm *farm) { 
    printf("\nFarm: %s\n", farm->name); //farm is a pointer  "->" acceses the firls of the struct the farm pointer is pointing to
    printf("Cows: %d\n", farm->cows); 
    printf("Chickens: %d\n", farm->chickens);
    printf("Income: $%.2f\n", farm->income);
}

 


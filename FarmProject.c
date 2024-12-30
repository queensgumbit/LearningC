#include <stdio.h>
#include <string.h>


typedef struct Cow {
    char name[50];
    int liters_produced;
    int gr_eaten;
    struct Cow *next;//pointer to the next cow
    struct Cow *prev;//pointer to the previous cow



};

typedef struct Chicken{
    char name[50];
    int eggs_layed;
    int gr_eaten;
    struct Chicken *next;//pointer to the next chicken
    struct Chicken *prev;//pointer to the previous chicken
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
    struct Chicken *current = farm->chickens;

    //while current exists(not null),search for the chicken by name.(strcmp checks if input is equall)
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {  // chicken found
            //updating the previous node to be the next-if its not null
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                // if null-no previous node
                farm->chickens = current->next;
            }

            // Update the next node's `prev` pointer (if it exists)
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            //free memory for the deleted cow
            free(current);
            farm->chickens--;  // -1 to chickens count
            printf("Removed chicken: %s\n", name);
            return;
        }
        current = current->next;  //moving to the next cow
    }

    printf("chicken named '%s' not found.\n", name);
}

void kill_cow(Farm *farm, char *name) {
    struct Cow *current = farm->cows;

    //while current exists(not null),search for the cow by name.(strcmp checks if input is equall)
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {  // Cow found
            //updating the previous node to be the next-if its not null
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                // if null-no previous node
                farm->cows = current->next;
            }

            // Update the next node's `prev` pointer (if it exists)
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            //free memory for the deleted cow
            free(current);
            farm->cows--;  // -1 to cows count
            printf("Removed cow: %s\n", name);
            return;
        }
        current = current->next;  //moving to the next cow
    }

    printf("Cow named '%s' not found.\n", name);
}

void kill_chickens(Farm *farm, int num) {
    if (num > farm->chickens) {
        printf("Not enough chickens to remove.\n");
        return;
    }

    struct Chicken *current = farm->next; 
    struct Chicken *chicken_now;

    while (num > 0 && current != NULL) {
        chicken_now = current;           //storing the chicken to remove
        current = current->next;         //moving the current to next->moving to the next chicken
        
        if (chicken_now->prev != NULL) {
            chicken_now->prev->next = chicken_now->next; //updating the previous node the next pointer
        }
        if (chicken_now->next != NULL) {
            chicken_now->next->prev = chicken_now->prev; // Update the next node's prev pointer
        }
//need to sort out how to acces the head of the list: chicken_first
        if (farm->chickens_first == chicken_now) {
            farm->chickens_first = current; // update the first chicken in the list
        }

        free(chicken_now);                // free the memory
        farm->chickens--;                 // -1 to count of chickens
        num--;                            // -1 to the number of chickens to remove
    }

    printf("%d chickens removed from the farm.\n  ", num);
}

void kill_cows(Farm *farm, int num) {
    if (num > farm->cows) {
        printf("Not enough cows to remove.\n ");
        return;
    }
//same as with chickens - need to sort out how to acces the head of the list: cow_first

    struct Cow *current = farm->cows_first; 
    struct Cow *cow_now;

    while (num > 0 && current != NULL) {
        cow_now = current;            // storing the cow to remove
        current = current->next;      // moving to the next cow

        if (cow_now->prev != NULL) {
            cow_now->prev->next = cow_now->next; 
        }
        if (cow_now->next != NULL) {
            cow_now->next->prev = cow_now->prev; /
        }

        if (farm->cow_first == cow_now) {
            farm->cow_first = current;
        }

        free(cow_now);                // free memory
        farm->cows--;                 // -1 to count of cows
        num--;                        //-1 to the number of cows to remove(till num!>0 meaning till num==0)
    }

    printf("%d cows removed from the farm.\n  ", num);
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
    new_cow->next = farm->cows;  // point to the current first node(of the list)
    new_cow->prev = NULL;        //no prevoius node.
    //if the list is not empty, update the current head's `prev` pointer.(meaning theres a new head and the new_cow is the prev)
    if (farm->cows != NULL) {
        farm->cows->prev = new_cow;
    }

    // update the head of the cows list to new_cow
    farm->cows = new_cow;
    farm->cows++;  //+1 to cows count

    return new_cow;
}

struct Chicken* add_chicken( Farm *farm, char *name) {
    struct Chicken *new_chicken = (struct Chicken*)malloc(sizeof(struct Chicken));
    if (new_chicken == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
     strcpy(new_chicken->name, name);
    new_chicken->eggs_layed = 0;
    new_chicken->gr_eaten = 0;
    new_chicken->next = farm->cows;  // point to the current first node(of the list)
    new_chicken->prev = NULL;        //no prevoius node.
    //if the list is not empty, update the current head's `prev` pointer.(meaning theres a new head and the new_cow is the prev)
    if (farm->cows != NULL) {
        farm->cows->prev = new_chicken;
    }

    // update the head of the cows list to new_cow
    farm->cows = new_chicken;
    farm->cows++;  //+1 to cows count

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

 


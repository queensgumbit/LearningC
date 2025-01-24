#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _LIST_ENTRY {
  struct _LIST_ENTRY *Flink;
  struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, PRLIST_ENTRY;

typedef struct Cow {
     struct Cow *next;
    struct Cow *prev; 
    char name[50];
    int liters_produced;
    int gr_eaten;
   
} Cow;

typedef struct Chicken {
    struct Chicken *next; 
    struct Chicken *prev; 
    char name[50];
    int eggs_layed;
    int gr_eaten;
    
} Chicken;

typedef struct {
    Cow *cow_list;         
    Chicken *chicken_list; 
    char name[50];
    int cow_count;
    int chicken_count;
    float income;
    
} Farm;

Cow* add_cow(Farm *farm, const char *name);
Chicken* add_chicken(Farm *farm, const char *name);
void remove_cow(Farm *farm, const char *name);
void remove_chicken(Farm *farm, const char *name);
void milk_cow(Cow *cow, int liters);
void collect_eggs(Chicken *chicken, int eggs);
void display_farm(Farm *farm);

// add cow to a farm
Cow* add_cow(Farm *farm, const char *name) {
    Cow *new_cow = (Cow *)malloc(sizeof(Cow));
    if (!new_cow) {
        printf("Memory allocation failed for cow.\n");
        return NULL;
    }

    strcpy(new_cow->name, name);
    new_cow->liters_produced = 0;
    new_cow->gr_eaten = 0;
    new_cow->next = farm->cow_list;
    new_cow->prev = NULL;

    if (farm->cow_list != NULL) {
        farm->cow_list->prev = new_cow;
    }
    farm->cow_list = new_cow;
    farm->cow_count++;
    return new_cow;
}

//add a chicken to the farm
Chicken* add_chicken(Farm *farm, const char *name) {
    Chicken *new_chicken = (Chicken *)malloc(sizeof(Chicken));
    if (!new_chicken) {
        printf("Memory allocation failed for chicken.\n");
        return NULL;
    }

    strcpy(new_chicken->name, name);
    new_chicken->eggs_layed = 0;
    new_chicken->gr_eaten = 0;
    new_chicken->next = farm->chicken_list;
    new_chicken->prev = NULL;

    if (farm->chicken_list != NULL) {
        farm->chicken_list->prev = new_chicken;
    }
    farm->chicken_list = new_chicken;
    farm->chicken_count++;
    return new_chicken;
}

//remove a cow from the farm(by name)
void remove_cow(Farm *farm, const char *name) {
    Cow *current = farm->cow_list;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                farm->cow_list = current->next; //update head if its the first node
            }

            if (current->next) {
                current->next->prev = current->prev;
            }

            free(current);
            farm->cow_count--;
            printf("Cow '%s' removed from the farm.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Cow '%s' not found.\n", name);
}

// Remove a chicken from the farm by name
void remove_chicken(Farm *farm, const char *name) {
    Chicken *current = farm->chicken_list;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                farm->chicken_list = current->next; 
            }

            if (current->next) {
                current->next->prev = current->prev;
            }

            free(current);
            farm->chicken_count--;
            printf("Chicken '%s' removed from the farm.\n", name);
            return;
        }
        current = current->next;
    }
    printf("Chicken '%s' not found.\n", name);
}

void milk_cow(Cow *cow, int liters) {
    if (cow) {
        cow->liters_produced += liters;
        printf("Cow '%s' milked for %d liters.\n", cow->name, liters);
    }
}

void collect_eggs(Chicken *chicken, int eggs) {
    if (chicken) {
        chicken->eggs_layed += eggs;
        printf("Chicken '%s' laid %d eggs.\n", chicken->name, eggs);
    }
}

void display_farm(Farm *farm) {
    printf("\nFarm: %s\n", farm->name);
    printf("Cows (%d):\n", farm->cow_count);
    Cow *current_cow = farm->cow_list;
    while (current_cow != NULL) {
        printf("  - %s: %d liters produced, %d grams eaten\n", current_cow->name, current_cow->liters_produced, current_cow->gr_eaten);
        current_cow = current_cow->next;
    }

    printf("Chickens (%d):\n", farm->chicken_count);
    Chicken *current_chicken = farm->chicken_list;
    while (current_chicken != NULL) {
        printf("  - %s: %d eggs laid, %d grams eaten\n", current_chicken->name, current_chicken->eggs_layed, current_chicken->gr_eaten);
        current_chicken = current_chicken->next;
    }

    printf("Income: $%.2f\n", farm->income);
}

int main() {
    Farm testFarm = {"Test Farm", 0, 0, 0.0, NULL, NULL};

    add_cow(&testFarm, "Sharon");
    add_cow(&testFarm, "Karin");

    add_chicken(&testFarm, "Ella");
    add_chicken(&testFarm, "Yasmin");

    milk_cow(testFarm.cow_list, 5);
    milk_cow(testFarm.cow_list->next, 3);

    collect_eggs(testFarm.chicken_list, 6);
    collect_eggs(testFarm.chicken_list->next, 4);

    display_farm(&testFarm);

    remove_cow(&testFarm, "Sharon");
    remove_chicken(&testFarm, "Karin");

    display_farm(&testFarm);

    return 0;
}
